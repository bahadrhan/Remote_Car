#include <WiFi.h>
#include "Config.h"
#include "WifiMgr.h"

void WifiMgr::init() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  unsigned long t0 = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t0 < 10000) {
  delay(300);
}
  }


void WifiMgr::loop() {
  // reconnect logic later
}
