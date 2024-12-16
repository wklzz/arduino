#include <Arduino.h>
#include "espnowController.h"
#include <ESP8266WiFi.h>
#include <espnow.h>

EspNowController::EspNowController() {}
const u8 REQ_CONNECT[] = "REQ_CONNECT";
const u8 CONFIRM_CONNECTED[] = "CONFIRM_CONNECTED";

void EspNowController::init() {
  // Initialize ESP-NOW
  esp_now_init();
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  // Register callback function for ESP-NOW events
  esp_now_register_recv_cb([](uint8_t *mac_addr, uint8_t *incomingData, uint8_t len) {
    Serial.print("Received ESP-NOW packet from: ");
    printMacAddress(mac_addr);
    Serial.println();
  });

}

bool EspNowController::isConnected() {
  return false; 
}

void EspNowController::broadcast() {
    u8 mac_addr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    esp_now_send(mac_addr, (uint8_t*)REQ_CONNECT, sizeof(REQ_CONNECT));
}

void EspNowController::sendData(const char* data) {
  esp_now_send(this->mac_addr, (uint8_t*)data, strlen(data));
}

void EspNowController::recvCallback(uint8_t *mac_addr, uint8_t *incomingData, uint8_t len) {
  Serial.print("Received ESP-NOW packet from: ");
  printMacAddress(mac_addr);
  if (incomingData == CONFIRM_CONNECTED) {
    Serial.println("ESP-NOW connection confirmed");
    return;
  }
  Serial.println();

  // Assuming the data is a string:
  if (len > 0) {
    char receivedData[len + 1]; // Add 1 for null terminator
    memcpy(receivedData, incomingData, len);
    receivedData[len] = '\0';
    Serial.print("Data: ");
    Serial.println(receivedData);
  } else {
    Serial.println("Received empty data");
  }
}

void EspNowController::printMacAddress(const uint8_t *mac_addr) {
  char mac_str[18];
  sprintf(mac_str, "%02x:%02x:%02x:%02x:%02x:%02x",
          mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(mac_str);
}