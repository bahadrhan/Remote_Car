#include <Arduino.h>

#include "WifiMgr.h"
#include "UartLink.h"
#include "MqttMgr.h"

void setup()
{
  Serial.begin(115200);
  delay(300);

  Serial.println("ESP32 GATEWAY BOOT");

  WifiMgr::init();
  UartLink::init();
  MqttMgr::init();

  Serial.println("ESP32 GATEWAY READY");
}

void loop()
{
  WifiMgr::loop();
  UartLink::loop();
  MqttMgr::loop();
  delay(2);
}
