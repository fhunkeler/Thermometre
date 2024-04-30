#ifndef DOUBLE_RESET_H
#define DOUBLE_RESET_H

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else // defined(ARDUINO) && (ARDUINO >= 100)
#include <WProgram.h>
#endif                            // #defined(ARDUINO) && (ARDUINO >= 100)
#define ESP8266_DRD_USE_RTC false // true
#define ESP_DRD_USE_LITTLEFS true // false

// Number of seconds after reset during which a
// subsequent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector to use
#define DRD_ADDRESS 0

#ifdef DEBUG
#define DOUBLERESETDETECTOR_DEBUG true
#endif

#include <ESP_DoubleResetDetector.h> //https://github.com/khoih-prog/ESP_DoubleResetDetector
#include "ConfigurationStorage.h"
#include "Debug.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

  class DoubleReset
  {
  public:
    DoubleReset(char *file);
    void loop();

  private:
    DoubleResetDetector *drd;
    ConfigurationStorage configStorage;
  };
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // WEB_SERVER_H