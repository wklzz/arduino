#ifndef ESPNOWCONTROLLER_H
#define ESPNOWCONTROLLER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

class EspNowController {
public:
  EspNowController();
  void init();
  void onStationModeConnected(const WiFiEventStationModeConnected &event);
  void setupEspNow();

  bool isConnected();

  void broadcast();

  void sendData(const char *data);

  private:
  static bool connected;
  u8 mac_addr [6];
  static void recvCallback(uint8_t *mac_addr, uint8_t *incomingData, uint8_t len);
  static void printMacAddress(const uint8_t *mac_addr);
  // Add private members here if needed
};

#endif  // ESPNOWCONTROLLER_H