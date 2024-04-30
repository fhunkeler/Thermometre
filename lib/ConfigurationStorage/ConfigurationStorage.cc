// Path: lib/ConfigurationStorage/ConfigurationStorage.h
#include "ConfigurationStorage.h"

ConfigurationStorage::ConfigurationStorage()
{
  Serial.begin(115200);
  DEBUG_PRINT("ConfigurationStorage::ConfigurationStorage()");
  if (!LittleFS.begin())
  {
    DEBUG_PRINT("Failed to start LittleFS");
  }
}
/**
 * @brief Construct a new Configuration Storage:: Configuration Storage object
 *
 * @param file
 */
ConfigurationStorage::ConfigurationStorage(char *file)
{
  Serial.begin(115200);
  DEBUG_PRINT("ConfigurationStorage::ConfigurationStorage(" + String(file) + ")");
  configPath = file;
  if (LittleFS.begin() && LittleFS.exists(configPath))
  {
    File configFile = LittleFS.open(configPath, "r");
    if (!configFile)
    {
      Serial.println("Failed to open configuration file");
      ESP.restart();
    }

    DeserializationError error = deserializeJson(configDoc, configFile);
    if (error)
    {
      DEBUG_PRINT(F("Failed to parse configuration file"));
      ESP.restart();
    }
    DEBUG_PRINT(F("Configuration file parsed"));
  }
  else
  {
    DEBUG_PRINT(F("Configuration file does not exist"));
    createConfigFile();
  }
}

/**
 * @brief Return the configuration document
 *
 * @return JsonDocument*
 */
JsonDocument ConfigurationStorage::get()
{
  DEBUG_PRINT(F("ConfigurationStorage::get()"));
  DEBUG_PRINT_JSON(configDoc, Serial);
  return configDoc;
}

/**
 * @brief Set the configuration document
 *
 * @param doc
 */
bool ConfigurationStorage::set(JsonDocument doc)
{
  DEBUG_PRINT(F("ConfigurationStorage::set()"));
  configDoc = doc;
  DEBUG_PRINT_JSON(configDoc, Serial);
  return writeConfigFile();
}

/**
 * @brief Write config to file
 *
 */
bool ConfigurationStorage::writeConfigFile()
{
  DEBUG_PRINT(F("ConfigurationStorage::writeConfigFile()"));
  String deviceId = getDeviceId();
  configDoc["deviceId"] = deviceId;
  File configFile = LittleFS.open(configPath, "w");

  if (!configFile)
  {
    DEBUG_PRINT(F("Failed to open configuration file"));
    configFile.close();
    return false;
  }
  if (serializeJson(configDoc, configFile) == 0)
  {
    DEBUG_PRINT(F("Failed to write file"));
    configFile.close();
    return false;
  }
  DEBUG_PRINT("Config file wrote");
  configFile.close();
  return true;
}

/**
 * @brief Create a configuration file
 *
 * @return true
 * @return false
 */
bool ConfigurationStorage::createConfigFile()
{
  DEBUG_PRINT(F("ConfigurationStorage::createConfigFile()"));
  File configFile = LittleFS.open(configPath, "w");
  if (!configFile)
  {
    Serial.println("Failed to open configuration file");
    return false;
  }
  String deviceId = getDeviceId();
  configDoc["deviceId"] = deviceId;
  configDoc["firstBoot"] = true;
  configDoc["wifi"]["ssid"] = "your-ssid";
  configDoc["wifi"]["password"] = "your-password";
  configDoc["mqtt"]["server"] = "your-server";
  configDoc["mqtt"]["port"] = 1883;
  configDoc["mqtt"]["user"] = "user";
  configDoc["mqtt"]["password"] = "password";
  configDoc["mqtt"]["topic"] = "topic";
  configDoc["mqtt"]["id"] = "thermometer_" + deviceId;
  DEBUG_PRINT(F("Configuration file created : "));
  DEBUG_PRINT_JSON(configDoc, Serial);

  return writeConfigFile();
}

/**
 * @brief get the device id
 *
 * @return String
 */
String ConfigurationStorage::getDeviceId()
{
  DEBUG_PRINT(F("ConfigurationStorage::getDeviceId()"));
  String deviceId = "";
  for (size_t i = 0; i < UniqueIDsize; i++)
  {
    if (UniqueID[i] < 0x10)
      deviceId += "0";
    deviceId += String(UniqueID[i], HEX);
  }
  return deviceId;
}
