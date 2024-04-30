#ifndef DEBUG_H
#define DEBUG_H

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else // defined(ARDUINO) && (ARDUINO >= 100)
#include <WProgram.h>
#endif

#ifdef DEBUG
#define DEBUG_ESP_CORE
#define DEBUG_PRINT(str) \
  Serial.printf("%lu: [%s:%d -> %s] : %s\n", millis(), __FILE__, __LINE__, __PRETTY_FUNCTION__, str);
#else
#define DEBUG_PRINT(str)
#endif

#endif