#include "WebServer.h"

WebServer::WebServer()
{
  Serial.begin(115200);
  Serial.println("WebServer::WebServer()");
  ESP8266WebServer server(80);
}

bool WebServer::begin(JsonDocument config)
{
  Serial.println("WebServer::begin()");
  configDoc = config;
  // serializeJsonPretty(configDoc, Serial);
  // Serial.println();

  const char *deviceId = configDoc["deviceId"];
  String ssid = "thermometer_" + String(deviceId);
  bool wifiStatus = WiFi.softAP(ssid);
  MDNS.begin(ssid);
  server.serveStatic("/", LittleFS, "/www/index.html");
  // server.on("/", handleRoot);
  server.on("/api/config", HTTP_GET, [&]()
            { getConfig(); });
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
  Serial.println("WebServer::handleGetConfig()");
  WiFiClient client = server.client();
  serializeJson(configDoc, client);
  // server.send(200, "application/json", data);
}

// #include "WebServer.h"

// WebServer::WebServer(ConfigurationStorage &config)
// {
//   Serial.println("WebServer::WebServer()");
//   configStore = &config;
//   ESP8266WebServer server(80);
// }

// WebServer::~WebServer()
// {
//   Serial.println("WebServer::~WebServer()");
// }

// bool WebServer::begin()
// {
//   Serial.println("WebServer::begin()");
//   JsonDocument configDoc = configStore->get();
//   const char *deviceId = configDoc["deviceId"];
//   String ssid = "thermometer_" + String(deviceId);
//   bool wifiStatus = WiFi.softAP(ssid);
//   MDNS.begin(ssid);
//   // server->serveStatic("/", LittleFS, "/www/index.html");
//   // server.on("/", handleRoot);
//   server->begin();
//   return wifiStatus;
// }

// void WebServer::handleRoot()
// {
//   Serial.println("WebServer::handleRoot()");
//   server->send(200, "text/plain", "this works as well");
// }
// // bool WebServer::begin()
// // {
// //   Serial.println("WebServer::begin(): ");
// //   if (!LittleFS.begin())
// //   {
// //     Serial.println("LittleFS Mount Failed");
// //     return false;
// //   }

// //   JsonDocument configDoc = configStore->get();
// //   const char *deviceId = configDoc["deviceId"];
// //   serializeJsonPretty(configDoc, Serial);
// //   Serial.println();
// //   String ssid = "thermometer_" + String(deviceId);

// //   if (!MDNS.begin(ssid))
// //   {
// //     Serial.println("MDNS responder failed to start");
// //   }

// //   server->on("/api/config", HTTP_GET, [&]()
// //              { getConfig(); });
// //   server->on("/api/config", HTTP_POST, [&]()
// //              { setConfig(); });
// //   // serve all static files
// //   server->serveStatic("/", LittleFS, "/www/index.html");

// //   bool wifiStatus = WiFi.softAP(ssid);
// //   server->begin();
// //   return wifiStatus;
// // }

// void WebServer::setConfig()
// {
//   Serial.println("WebServer::handlePostConfig()");
//   JsonDocument configDoc = configStore->get();
//   deserializeJson(configDoc, server->arg("plain"));
//   configStore->set(configDoc);
//   server->send(200, "application/json", "{\"status\":\"ok\"}");
// }

// void WebServer::getConfig()
// {
//   Serial.println("WebServer::handleGetConfig()");
//   WiFiClient client = server->client();
//   serializeJson(configStore->get(), client);
//   // server.send(200, "application/json", data);
// }

// void WebServer::listen()
// {
//   server->handleClient();
//   MDNS.update();
// }
