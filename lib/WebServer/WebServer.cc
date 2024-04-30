#include "WebServer.h"

WebServer::WebServer(ConfigurationStorage store)
{
  Serial.begin(115200);
  DEBUG_PRINT(F("WebServer::WebServer()"));
  ESP8266WebServer server(80);
  configStore = store;
}

bool WebServer::begin(JsonDocument config)
{
  DEBUG_PRINT(F("WebServer::begin()"));
  configDoc = config;

  const char *deviceId = configDoc["deviceId"];
  String ssid = "thermometer_" + String(deviceId);
  bool wifiStatus = WiFi.softAP(ssid);
  MDNS.begin(ssid);
  server.serveStatic("/", LittleFS, "/www/index.html");
  // server.on("/", handleRoot);
  server.on("/api/config", HTTP_GET, [&]()
            { getConfig(); });

  server.on("/api/config", HTTP_POST, [&]()
            { setConfig(); });

  server.begin();
  return wifiStatus;
}

void WebServer::listen()
{
  server.handleClient();
  MDNS.update();
}

void WebServer::getConfig()
{
  DEBUG_PRINT(F("WebServer::handleGetConfig()"));
  WiFiClient client = server.client();
  serializeJson(configDoc, client);
}

void WebServer::setConfig()
{
  DEBUG_PRINT(F("WebServer::handlePostConfig()"));
  deserializeJson(configDoc, server.arg("plain"));
  if (configStore.set(configDoc))
  {
    server.send(200, "application/json", "{\"status\":\"OK\"}");
  }
  else
  {
    server.send(500, "application/json", "{\"status\":\"KO\"}");
  }
}
