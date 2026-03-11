/*
 * Clock.hpp
 *
 *  Created on: Jan 15, 2026
 *      Author: bahad
 */

#pragma once
#include <cstdint>
#include "stm32f0xx.h"

namespace Clock
{
    void init48MHz_HSI48();
    void enableGpioClock(GPIO_TypeDef* port);
}
