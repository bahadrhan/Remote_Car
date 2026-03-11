#pragma once
#include <cstdint>

namespace Uart
{
    void init(uint32_t baud);
    void write(const char* s);
    void writeByte(uint8_t b);
    bool readByte(uint8_t& out);
}
