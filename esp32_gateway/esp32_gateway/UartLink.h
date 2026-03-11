#pragma once
#include <stddef.h>

class UartLink {
public:
  static void init();
  static void loop();


  static void send(const char* s);

  static void sendByte(char c);


  static bool popLine(char* out, size_t outLen);
};
