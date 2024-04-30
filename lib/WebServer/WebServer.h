#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else // defined(ARDUINO) && (ARDUINO >= 100)
#include <WProgram.h>
#endif // #defined(ARDUINO) && (ARDUINO >= 100)

// #ifdef DEBUG
// #define DEBUG_ESP_HTTP_SERVER
// #endif

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <LittleFS.h>
#include <ConfigurationStorage.h>
#include "Debug.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

  class WebServer
  {
  public:
    WebServer(ConfigurationStorage store);
    bool begin(JsonDocument config);
    void listen();

  private:
    void getConfig();
    void setConfig();
    ESP8266WebServer server;
    ConfigurationStorage configStore;
    JsonDocument configDoc;
  };

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // WEB_SERVER_H