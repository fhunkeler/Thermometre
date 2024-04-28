// #ifndef WEB_SERVER_H
// #define WEB_SERVER_H

// #if defined(ARDUINO) && (ARDUINO >= 100)
// #include <Arduino.h>
// #else // defined(ARDUINO) && (ARDUINO >= 100)
// #include <WProgram.h>
// #endif // #defined(ARDUINO) && (ARDUINO >= 100)

// #include <ArduinoJson.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
// #include <ESP8266mDNS.h>
// #include <FS.h>
// #include <LittleFS.h>
// #include <ConfigurationStorage.h>

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

//   class WebServer
//   {
//   public:
//     WebServer(ConfigurationStorage &config);
//     ~WebServer();
//     bool begin();
//     void listen();

//   private:
//     ESP8266WebServer *server;
//     const char *configPath;
//     ConfigurationStorage *configStore;
//     void setConfig();
//     void getConfig();
//     void handleRoot();
//   };

// #ifdef __cplusplus
// }
// #endif // __cplusplus
// #endif // WEB_SERVER_H

#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else // defined(ARDUINO) && (ARDUINO >= 100)
#include <WProgram.h>
#endif // #defined(ARDUINO) && (ARDUINO >= 100)

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <LittleFS.h>
#include <ConfigurationStorage.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

  class WebServer
  {
  public:
    WebServer();
    bool begin(JsonDocument config);
    void listen();

  private:
    void getConfig();
    ESP8266WebServer server;
    ConfigurationStorage configStore;
    JsonDocument configDoc;
  };

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // WEB_SERVER_H