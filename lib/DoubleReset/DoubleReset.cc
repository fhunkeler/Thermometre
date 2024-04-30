#include "DoubleReset.h"

DoubleReset::DoubleReset(char *file)
{
  Serial.begin(115200);
  DEBUG_PRINT("DoubleReset::DoubleReset(" + String(file) + ")");
  drd = new DoubleResetDetector(DRD_TIMEOUT, DRD_ADDRESS);
  ConfigurationStorage configStorage(file);
  if (drd->detectDoubleReset())
  {
    DEBUG_PRINT(F("Double Reset Detected"));
    JsonDocument config = configStorage.get();
    config["firstBoot"] = true;
    configStorage.set(config);
    ESP.restart();
  }
}

void DoubleReset::loop()
{
  drd->loop();
}