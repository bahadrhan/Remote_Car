#pragma once
#include <cstdint>

class MotorDriver
{
public:
    void init();
    void enable();
    void disable();

    void stop();

    void setSpeedPercent(uint8_t percent); // 0..100

    void forward();
    void back();
    void spinRight();
    void spinLeft();

private:
    void setLeftForward();
    void setLeftBack();
    void setRightForward();
    void setRightBack();

    void initPwmTim3_(uint32_t pwm_hz);
    void setDutyAll_(uint16_t duty);
};
