#ifndef CONFIGURATIONSTORAGE_H
#define CONFIGURATIONSTORAGE_H

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else // defined(ARDUINO) && (ARDUINO >= 100)
#include <WProgram.h>
#endif // #defined(ARDUINO) && (ARDUINO >= 100)

#include <ArduinoJson.h>
#include <FS.h>
#include <LittleFS.h>
#include <ArduinoUniqueID.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

  class ConfigurationStorage
  {
  public:
    ConfigurationStorage();
    ConfigurationStorage(char *file);
    // bool begin();
    JsonDocument get();
    bool set(JsonDocument doc);

  private:
    char *configPath;
    JsonDocument configDoc;
    bool createConfigFile();
    String getDeviceId();
    bool writeConfigFile();
  };
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // CONFIGURATIONSTORAGE_H