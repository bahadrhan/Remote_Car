/*
 * Timebase.cpp
 *
 *  Created on: Jan 15, 2026
 *      Author: bahad
 */

#include "hw/Timebase.hpp"
#include "stm32f0xx.h"

static volatile uint32_t g_ms = 0;

extern "C" void SysTick_Handler(void)
{
    ++g_ms;
}

namespace Timebase
{
    void init()
    {
        g_ms = 0;

        SysTick_Config(SystemCoreClock / 1000u); // 1ms tick
    }

    uint32_t millis()
    {
        return g_ms;
    }

    void delayMs(uint32_t ms)
    {
        uint32_t start = millis();
        while ((millis() - start) < ms) { /* wait */ }
    }
    uint32_t micros()
    {
        const uint32_t ticks_per_us = SystemCoreClock / 1000000u;
        const uint32_t reload = SysTick->LOAD + 1u;
        uint32_t ms1, ms2, val;
        do {
                    ms1 = g_ms;
                    val = SysTick->VAL;
                    ms2 = g_ms;
                } while (ms1 != ms2);


                const uint32_t elapsed_ticks = (reload - val);
                const uint32_t elapsed_us_in_ms = elapsed_ticks / ticks_per_us;

                return (ms1 * 1000u) + elapsed_us_in_ms;
    }

    void delayUs(uint32_t us)
    {
        const uint32_t start = micros();
        while ((micros() - start) < us)
        {
            __NOP();
        }
    }

}
