// Path: lib/ConfigurationStorage/ConfigurationStorage.h
#include "ConfigurationStorage.h"

ConfigurationStorage::ConfigurationStorage()
{
}
/**
 * @brief Construct a new Configuration Storage:: Configuration Storage object
 *
 * @param file
 */
ConfigurationStorage::ConfigurationStorage(char *file)
{
  Serial.begin(115200);
  Serial.println("ConfigurationStorage::ConfigurationStorage(" + String(file) + ")");
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
      Serial.println("Failed to parse configuration file");
      ESP.restart();
    }
    Serial.println("Configuration file parsed");
    // serializeJsonPretty(configDoc, Serial);
    // Serial.println();
  }
  else
  {
    Serial.println("Configuration file does not exist");
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
  Serial.println("ConfigurationStorage::get()");
  serializeJsonPretty(configDoc, Serial);
  return configDoc;
}

/**
 * @brief Set the configuration document
 *
 * @param doc
 */
bool ConfigurationStorage::set(JsonDocument doc)
{
  Serial.println("ConfigurationStorage::set()");
  configDoc = doc;
  return writeConfigFile();
}

/**
 * @brief Write config to file
 *
 */
bool ConfigurationStorage::writeConfigFile()
{
  Serial.println("ConfigurationStorage::writeConfigFile()");
  LittleFS.remove(configPath);
  File configFile = LittleFS.open(configPath, "w");
  if (!configFile)
  {
    Serial.println("Failed to open configuration file");
    return false;
  }
  serializeJson(configDoc, configFile);
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
  Serial.println("ConfigurationStorage::createConfigFile()");
  if (!LittleFS.begin())
  {
    Serial.println("LittleFS Mount Failed");
    return false;
  }
  // LittleFS.format();
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
  Serial.println("Configuration file created : ");
  serializeJsonPretty(configDoc, Serial);
  serializeJson(configDoc, configFile);
  configFile.close();
  return true;
}

/**
 * @brief get the device id
 *
 * @return String
 */
String ConfigurationStorage::getDeviceId()
{
  Serial.println("ConfigurationStorage::getDeviceId()");
  String deviceId = "";
  for (size_t i = 0; i < UniqueIDsize; i++)
  {
    if (UniqueID[i] < 0x10)
      deviceId += "0";
    deviceId += String(UniqueID[i], HEX);
  }
  return deviceId;
}
