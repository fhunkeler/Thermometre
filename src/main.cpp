#include <Arduino.h>
#include "ConfigurationStorage.h"
#include "WebServer.h"
char configPath[] = "/config.json";
ConfigurationStorage configStorage(configPath);
WebServer webServer(configStorage);

void setup()
{
  Serial.begin(115200);
  Serial.println("Start");
  // configStorage.begin();
  webServer.begin();
}

void loop()
{
}
