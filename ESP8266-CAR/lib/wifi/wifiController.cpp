#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "WiFiController.h"

WiFiController::WiFiController(const char* ssid, const char* password) {
  this->ssid = ssid;
  this->password = password;
}

void WiFiController::setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin();
}

bool WiFiController::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}