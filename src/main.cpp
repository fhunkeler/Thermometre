#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <ESP8266WiFi.h>

#include "ConfigurationStorage.h"
#include "WebServer.h"
#include "DoubleReset.h"
#include "Debug.h"

WiFiClient wifi;

char configPath[] = "/config.json";
ConfigurationStorage configStorage(configPath);
WebServer webServer(configStorage);
DoubleReset doubleReset(configPath);

void setup()
{
  Serial.begin(115200);
  DEBUG_PRINT("Start");
  JsonDocument config = configStorage.get();

  if (config["firstBoot"])
  {
    webServer.begin(config);
  }
  else
  {
    String ssid = config["wifi"]["ssid"];
    String pwd = config["wifi"]["password"];
    WiFi.begin(ssid, pwd);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP());
  }
}

void loop()
{
  webServer.listen();
  doubleReset.loop();
}
