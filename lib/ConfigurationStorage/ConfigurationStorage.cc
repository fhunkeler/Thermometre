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
  Serial.println("ConfigurationStorage::ConfigurationStorage()");
  configPath = file;
  if (LittleFS.begin() && LittleFS.exists(configPath))
  {
    File configFile = LittleFS.open(configPath, "r");
    if (!configFile)
    {
      Serial.println("Failed to open configuration file");
      ESP.restart();
    }
    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    configFile.close();

    DeserializationError error = deserializeJson(configDoc, buf.get());
    if (error)
    {
      Serial.println("Failed to parse configuration file");
      ESP.restart();
    }
    Serial.println("Configuration file parsed");
  }
  else
  {
    Serial.println("Configuration file does not exist");
    createConfigFile();
  }
}

/**
 * @brief Start point for the configuration storage
 *
 * @return true
 * @return false
 */
// bool ConfigurationStorage::begin()
// {
//   Serial.println("ConfigurationStorage::begin(): ");
//   if (!LittleFS.begin())
//   {
//     Serial.println("LittleFS Mount Failed");
//     return false;
//   }

//   if (!LittleFS.exists(configPath))
//   {
//     Serial.println("Configuration file does not exist");
//     createConfigFile();
//     return true;
//   }
//   File configFile = LittleFS.open(configPath, "r");
//   if (!configFile)
//   {
//     Serial.println("Failed to open configuration file");
//     return false;
//   }
//   size_t size = configFile.size();
//   if (size > 1024)
//   {
//     Serial.println("Configuration file size is too large");
//     return false;
//   }
//   std::unique_ptr<char[]> buf(new char[size]);
//   configFile.readBytes(buf.get(), size);
//   configFile.close();

//   DeserializationError error = deserializeJson(configDoc, buf.get());
//   if (error)
//   {
//     Serial.println("Failed to parse configuration file");
//     return false;
//   }
//   Serial.println("Configuration file parsed");
//   return true;
// }

/**
 * @brief Return the configuration document
 *
 * @return JsonDocument*
 */
JsonDocument ConfigurationStorage::get()
{
  Serial.println("ConfigurationStorage::get()");
  return configDoc;
}

/**
 * @brief Set the configuration document
 *
 * @param doc
 */
bool ConfigurationStorage::set(JsonDocument doc)
{
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
  LittleFS.format();
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
  configDoc["mqtt"]["id"] = 1883;
  configDoc["mqtt"]["topic"] = "topic";
  configDoc["mqtt"]["id"] = "thermometer_" + deviceId;
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
