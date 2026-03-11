#include "hw/Gpio.hpp"

namespace Gpio
{
    void configureOutput(GPIO_TypeDef* const port, uint16_t pinMask)
    {
        for (uint8_t pin = 0; pin < 16; ++pin)
        {
            if (pinMask & (1u << pin))
            {
                uint32_t shift = 2u * pin;

                port->MODER   &= ~(0x3u << shift);
                port->MODER   |=  (0x1u << shift);

                port->OTYPER  &= ~(1u << pin);

                port->OSPEEDR &= ~(0x3u << shift);
                port->OSPEEDR |=  (0x3u << shift);

                port->PUPDR   &= ~(0x3u << shift);
            }
        }
    }

    void configureInput(GPIO_TypeDef* const port, uint16_t pinMask, Pull pull)
    {
        for (uint8_t pin = 0; pin < 16; ++pin)
        {
            if (pinMask & (1u << pin))
            {
                uint32_t shift = 2u * pin;

                port->MODER &= ~(0x3u << shift);
                port->PUPDR &= ~(0x3u << shift);

                if (pull == Pull::Up)
                    port->PUPDR |= (0x1u << shift);
                else if (pull == Pull::Down)
                    port->PUPDR |= (0x2u << shift);
            }
        }
    }

    void configureAltFunction(GPIO_TypeDef* const port, uint16_t pinMask, uint8_t af)
    {
        for (uint8_t pin = 0; pin < 16; ++pin)
        {
            if (pinMask & (1u << pin))
            {
                uint32_t shift = 2u * pin;

                port->MODER &= ~(0x3u << shift);
                port->MODER |=  (0x2u << shift);

                volatile uint32_t* afr =
                    (pin < 8) ? &port->AFR[0] : &port->AFR[1];

                uint32_t afrShift = 4u * (pin & 0x7u);
                *afr &= ~(0xFu << afrShift);
                *afr |=  (static_cast<uint32_t>(af) << afrShift);

                port->OTYPER  &= ~(1u << pin);

                port->OSPEEDR &= ~(0x3u << shift);
                port->OSPEEDR |=  (0x3u << shift);

                port->PUPDR   &= ~(0x3u << shift);
            }
        }
    }

    void setHigh(GPIO_TypeDef* const port, uint16_t pinMask)
    {
        port->BSRR = pinMask;
    }

    void setLow(GPIO_TypeDef* const port, uint16_t pinMask)
    {
        port->BSRR = static_cast<uint32_t>(pinMask) << 16;
    }

    bool read(GPIO_TypeDef* const port, uint16_t pinMask)
    {
        return (port->IDR & pinMask) != 0;
    }
}
