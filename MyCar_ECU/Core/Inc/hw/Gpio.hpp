#pragma once
#include <cstdint>
#include "stm32f0xx.h"

namespace Gpio
{
    enum class Pull : uint8_t
    {
        None,
        Up,
        Down
    };

    void configureOutput(GPIO_TypeDef* const port, uint16_t pinMask);
    void configureInput(GPIO_TypeDef* const port, uint16_t pinMask, Pull pull = Pull::None);
    void configureAltFunction(GPIO_TypeDef* const port, uint16_t pinMask, uint8_t af);

    void setHigh(GPIO_TypeDef* const port, uint16_t pinMask);
    void setLow (GPIO_TypeDef* const port, uint16_t pinMask);

    bool read(GPIO_TypeDef* const port, uint16_t pinMask);
}
