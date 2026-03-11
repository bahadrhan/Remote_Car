#pragma once

#include <cstdint>
#include "stm32f0xx.h"

class UltrasonicSensor
{
public:
    UltrasonicSensor(GPIO_TypeDef* trigPort, uint16_t trigPin,
                     GPIO_TypeDef* echoPort, uint16_t echoPin);

    void init();
    bool measureOnce(uint32_t& distance_mm);
    bool measureStable(uint32_t& distance_mm);

private:
    struct Pins
    {
        GPIO_TypeDef* trigPort;
        uint16_t      trigPin;
        GPIO_TypeDef* echoPort;
        uint16_t      echoPin;
    };

    void tim2Init1MHzOnce_();
    uint32_t nowUs_();

    void guardTime_();
    void trigPulse10us_();

    bool waitForLevel_(bool high, uint32_t timeout_us);
    uint32_t measureEchoHighUs_(uint32_t timeout_us);
    uint32_t usToMm_(uint32_t echo_high_us);

private:
    Pins pins_;
    uint32_t lastTrigUs_ = 0;

    static bool tim2_inited_;

    static constexpr uint32_t kGuardUs = 60000;
};
