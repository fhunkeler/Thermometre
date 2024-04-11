#include "WebServer.h"

WebServer::WebServer(ConfigurationStorage config)
{
  Serial.println("WebServer::WebServer()");
  configStore = config;
}

WebServer::~WebServer()
{
  Serial.println("WebServer::~WebServer()");
  delete server;
}

bool WebServer::begin()
{
  Serial.println("WebServer::begin(): ");
  if (!LittleFS.begin())
  {
    Serial.println("LittleFS Mount Failed");
    return false;
  }
  ConfigurationStorage configStorage(configPath);

  JsonDocument configDoc = configStorage.get();
  const char *deviceId = configDoc["deviceId"];
  String ssid = "thermometer_" + String(deviceId);
  ESP8266WebServer server(80);

  server.on("/api/config", HTTP_GET, [&]()
            { getConfig(server, configStorage); });
  server.on("/api/config", HTTP_POST, [&]()
            { setConfig(server, configStorage); });
  // serve all static files
  server.serveStatic("/", LittleFS, "/web");

  bool wifiStatus = WiFi.softAP(ssid);
  server.begin();
  return wifiStatus;
}

void WebServer::setConfig(ESP8266WebServer &server, ConfigurationStorage &configStorage)
{
  Serial.println("WebServer::handlePostConfig()");
  JsonDocument configDoc = configStore.get();
  deserializeJson(configDoc, server.arg("plain"));
  configStorage.set(configDoc);
  server.send(200, "application/json", "{\"status\":\"ok\"}");
}

void WebServer::getConfig(ESP8266WebServer &server, ConfigurationStorage &configStorage)
{
  Serial.println("WebServer::handleGetConfig()");
  WiFiClient client = server.client();
  serializeJson(configStorage.get(), client);
  // server.send(200, "application/json", data);
}
