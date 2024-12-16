#include <Arduino.h>
#include "wificonn.h"

void WiFiManager::begin(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

bool WiFiManager::isConnected() {
  return WiFi.isConnected();
}