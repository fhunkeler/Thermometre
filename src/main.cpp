#define DEBUG_ESP_HTTP_SERVER
#include <Arduino.h>
#include "ConfigurationStorage.h"
#include "WebServer.h"
#include <FS.h>
#include <LittleFS.h>

char configPath[] = "/config.json";
ConfigurationStorage configStorage(configPath);
WebServer webServer;

void setup()
{
  Serial.begin(115200);
  Serial.println("main::setup()");

  webServer.begin(configStorage.get());
}

void loop()
{
  webServer.listen();
}

// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>
// #include <ESP8266WebServer.h>
// #include <ESP8266mDNS.h>
// #include <FS.h>
// #include <LittleFS.h>

// ESP8266WebServer server(80);

// void setup()
// {
//   Serial.begin(115200);
//   Serial.println("main::setup()");
//   LittleFS.begin();
//   WiFi.softAP("thermometer");
//   server.serveStatic("/", LittleFS, "/www/index.html");
//   server.begin();

//   Dir dir = LittleFS.openDir("/");
//   while (dir.next())
//   {
//     Serial.print(dir.fileName());
//     Serial.print(" : ");
//     Serial.println(dir.fileSize());
//   }

//   // webServer.begin();
// }

// void loop()
// {
//   server.handleClient();
//   // webServer.listen();
// }
