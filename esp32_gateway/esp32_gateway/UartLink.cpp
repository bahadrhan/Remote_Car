#include <Arduino.h>
#include "UartLink.h"
#include "Config.h"

static HardwareSerial STMSerial(STM_UART_NUM);


static char   rxLine[256];
static size_t rxIdx = 0;

void UartLink::init()
{
  STMSerial.begin(STM_UART_BAUD, SERIAL_8N1, STM_UART_RX, STM_UART_TX);
  rxIdx = 0;
}

void UartLink::loop()
{
  while (STMSerial.available())
  {
    char c = (char)STMSerial.read();

    if (c == '\r') continue;

    if (c == '\n')
    {

      if (rxIdx < sizeof(rxLine)) rxLine[rxIdx] = '\0';
      rxIdx = 0;

      return;
    }

    if (rxIdx < (sizeof(rxLine) - 1))
      rxLine[rxIdx++] = c;
    else
      rxIdx = 0; 
  }
}

void UartLink::send(const char* s)
{

  STMSerial.print(s);
  STMSerial.print('\n');
}

void UartLink::sendByte(char c)
{

  STMSerial.write((uint8_t)c);
}

bool UartLink::popLine(char* out, size_t outLen)
{


  static bool hasLine = false;
  static char lastLine[256];

  if (hasLine)
  {
    strncpy(out, lastLine, outLen);
    out[outLen - 1] = '\0';
    hasLine = false;
    return true;
  }

  if (rxIdx == 0 && rxLine[0] != '\0')
  {
    strncpy(lastLine, rxLine, sizeof(lastLine));
    lastLine[sizeof(lastLine) - 1] = '\0';

    rxLine[0] = '\0';
    hasLine = true;

    strncpy(out, lastLine, outLen);
    out[outLen - 1] = '\0';
    hasLine = false;
    return true;
  }

  return false;
}
