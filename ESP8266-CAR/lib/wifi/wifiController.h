#ifndef WiFiController_h
#define WiFiController_h

#include <ESP8266WiFi.h>

class WiFiController {
  public:
    WiFiController(const char* ssid, const char* password);
    void setup();
    bool isConnected();

  private:
    const char* ssid;
    const char* password;
};

#endif  // WiFiController_h