#include "hw/Clock.hpp"
#include "stm32f0xx.h"

namespace Clock
{
    void init48MHz_HSI48()
    {
        RCC->CR2 |= RCC_CR2_HSI48ON;
        while ((RCC->CR2 & RCC_CR2_HSI48RDY) == 0) {}

        FLASH->ACR &= ~(0x7UL);
        FLASH->ACR |= (0x1UL);

        RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE);

        RCC->CFGR &= ~RCC_CFGR_SW;
        RCC->CFGR |= RCC_CFGR_SW_HSI48;

        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI48) {}

        __DSB();
        __ISB();

        SystemCoreClockUpdate();
    }

    void enableGpioClock(GPIO_TypeDef* port)
    {
        if (port == GPIOA)      RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
        else if (port == GPIOB) RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
        else if (port == GPIOC) RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
        else if (port == GPIOD) RCC->AHBENR |= RCC_AHBENR_GPIODEN;
        else if (port == GPIOF) RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
    }
}
