/*
 * Timebase.hpp
 *
 *  Created on: Jan 15, 2026
 *      Author: bahad
 */

#pragma once
#include <cstdint>

namespace Timebase
{
    void init();
    uint32_t millis();
    void delayMs(uint32_t ms);
    uint32_t micros();
    void delayUs(uint32_t us);

}
