#include "stm32f0xx.h"

#include <cstdint>
#include <cstdio>

#include "hw/Clock.hpp"
#include "hw/Timebase.hpp"
#include "hw/BoardPins.hpp"
#include "hw/Gpio.hpp"
#include "hw/Uart.hpp"

#include "app/MotorDriver.hpp"
#include "app/Lights.hpp"
#include "sensors/UltrasonicSensor.hpp"

#include "app/AutonomyController.hpp"
#include "app/Parameters.hpp"
#include "app/Command.hpp"

static MotorDriver motor;
static Lights lights;

static UltrasonicSensor usFront(
    BoardPins::US_TRIG_PORT, BoardPins::US_TRIG_PIN,
    BoardPins::US_ECHO_PORT, BoardPins::US_ECHO_PIN);

static UltrasonicSensor usRear(
    BoardPins::US_REAR_TRIG_PORT, BoardPins::US_REAR_TRIG_PIN,
    BoardPins::US_REAR_ECHO_PORT, BoardPins::US_REAR_ECHO_PIN);

static uint8_t speedPct = 40;

static volatile bool sensorShotReq = false;
static bool sensorsEnabled = false;
static bool sensorBusy = false;
static uint32_t nextSensorTickMs = 0;

static uint32_t loopMs = 0;
static constexpr uint32_t SENSOR_PERIOD_MS = 200;

static void setSpeed(uint8_t pct)
{
    if (pct > 100) pct = 100;
    speedPct = pct;
    motor.setSpeedPercent(speedPct);

    char buf[24];
    std::snprintf(buf, sizeof(buf), "SPD=%u\n", (unsigned)speedPct);
    Uart::write(buf);
}

static void stopAll()
{
    motor.stop();
    Uart::write("M=STOP\n");
}

static void sendDistances()
{
    uint32_t f = 0, r = 0;
    const bool okF = usFront.measureOnce(f);
    const bool okR = usRear.measureOnce(r);

    char buf[64];
    std::snprintf(buf, sizeof(buf),
                  "D F=%ld R=%ld\n",
                  okF ? (long)f : -1L,
                  okR ? (long)r : -1L);
    Uart::write(buf);
}

static Parameters params;
static AutonomyController autonomy;

static bool autoAllowed = false;
static bool autoActive  = false;

static uint32_t lastManualDriveMs = 0;

static constexpr uint32_t AUTO_IDLE_MS = 10000;
static constexpr uint32_t AUTO_TICK_MS = 100;
static uint32_t nextAutoTickMs = 0;

static uint8_t manualSpeedPct = 80;
static uint8_t autoSpeedPct = 40;

static void autopilotStop_()
{
    if (autoActive)
    {
        autoActive = false;
        params.autoModeEnabled = false;
        autonomy.reset();
        motor.stop();
        Uart::write("AP=0\n");
        Uart::write("M=STOP\n");
    }
}

static void autopilotStart_()
{
    if (!autoActive)
    {
        autoActive = true;
        params.autoModeEnabled = true;
        autonomy.reset();

        motor.setSpeedPercent(autoSpeedPct);

        nextAutoTickMs = loopMs + AUTO_TICK_MS;
        Uart::write("AP=1\n");
    }
}

static void applyCommandToMotor_(const Command& c)
{
    switch (c.type)
    {
        case CommandType::Forward:
            motor.forward();
            Uart::write("M=F\n");
            break;

        case CommandType::Backward:
            motor.back();
            Uart::write("M=B\n");
            break;

        case CommandType::TurnLeft:
            motor.spinLeft();
            Uart::write("M=L\n");
            break;

        case CommandType::TurnRight:
            motor.spinRight();
            Uart::write("M=R\n");
            break;

        case CommandType::Stop:
        default:
            motor.stop();
            Uart::write("M=STOP\n");
            break;
    }
}

static void handleByte(uint8_t b)
{
    if      (b == 'H') { lights.setHeadlight(true);  Uart::write("HL=1\n"); return; }
    else if (b == 'h') { lights.setHeadlight(false); Uart::write("HL=0\n"); return; }
    else if (b == 'S') { lights.setStoplight(true);  Uart::write("SL=1\n"); return; }
    else if (b == 's') { lights.setStoplight(false); Uart::write("SL=0\n"); return; }

    if (b >= '0' && b <= '9')
    {
        const uint8_t pct = (uint8_t)(b - '0') * 10;
        manualSpeedPct = pct;
        if (!autoActive)
            setSpeed(pct);
        return;
    }

    if (b == 'A')
    {
        autoAllowed = true;
        Uart::write("AUTO=1\n");
        return;
    }

    if (b == 'a')
    {
        autoAllowed = false;
        autopilotStop_();
        motor.setSpeedPercent(manualSpeedPct);
        stopAll();
        Uart::write("AUTO=0\n");
        return;
    }

    if (b == 'F' || b == 'B' || b == 'L' || b == 'R')
    {
        lastManualDriveMs = loopMs;

        if (autoActive)
        {
            autopilotStop_();
            motor.setSpeedPercent(manualSpeedPct);
        }

        if      (b == 'F') { motor.forward();   Uart::write("M=F\n"); return; }
        else if (b == 'B') { motor.back();      Uart::write("M=B\n"); return; }
        else if (b == 'L') { motor.spinLeft();  Uart::write("M=L\n"); return; }
        else               { motor.spinRight(); Uart::write("M=R\n"); return; }
    }

    if (b == 'X')
    {
        if (autoActive)
        {
            autopilotStop_();
            motor.setSpeedPercent(manualSpeedPct);
        }
        stopAll();
        return;
    }

    if (b == 'g')
    {
        if (!sensorBusy) sensorShotReq = true;
        return;
    }

    if (b == 'E')
    {
        sensorsEnabled = true;
        nextSensorTickMs = loopMs + SENSOR_PERIOD_MS;
        Uart::write("SNS=1\n");
        return;
    }

    if (b == 'e')
    {
        sensorsEnabled = false;
        Uart::write("SNS=0\n");
        return;
    }

    Uart::write("RX=?\n");
}

int main()
{
    Clock::init48MHz_HSI48();
    Timebase::init();

    Uart::init(115200);
    Uart::write("BOOT\n");

    motor.init();
    motor.enable();

    lights.init();
    lights.setHeadlight(false);
    lights.setStoplight(false);

    usFront.init();
    usRear.init();

    setSpeed(40);
    manualSpeedPct = 40;
    stopAll();

    loopMs = 0;
    nextSensorTickMs = SENSOR_PERIOD_MS;

    params.sensorsEnabled = true;
    params.autoModeEnabled = false;
    if (params.obstacleThresholdMm == 0) params.obstacleThresholdMm = 250;
    if (params.reverseTimeMs == 0)       params.reverseTimeMs = 500;
    if (params.turnTimeMs == 0)          params.turnTimeMs = 600;

    autonomy.init(params, usFront, usRear);

    lastManualDriveMs = loopMs;
    nextAutoTickMs = loopMs + AUTO_TICK_MS;

    while (1)
    {
        uint8_t b = 0;
        while (Uart::readByte(b))
        {
            handleByte(b);
        }

        if (!sensorBusy)
        {
            const bool doShot = sensorShotReq;
            const bool doPeriodic = sensorsEnabled && ((int32_t)(loopMs - nextSensorTickMs) >= 0);

            if (doShot || doPeriodic)
            {
                sensorShotReq = false;
                sensorBusy = true;

                sendDistances();

                nextSensorTickMs = loopMs + SENSOR_PERIOD_MS;

                sensorBusy = false;
            }
        }

        if (autoAllowed && !autoActive)
        {
            if ((int32_t)(loopMs - (lastManualDriveMs + AUTO_IDLE_MS)) >= 0)
            {
                autopilotStart_();
            }
        }

        if (autoActive)
        {
            if ((int32_t)(loopMs - nextAutoTickMs) >= 0)
            {
                nextAutoTickMs = loopMs + AUTO_TICK_MS;

                const Command c = autonomy.update(loopMs);
                applyCommandToMotor_(c);
            }
        }

        Timebase::delayMs(2);
        loopMs += 2;
    }
}
