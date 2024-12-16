#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>

class WiFiManager {
public:
    void begin(const char* ssid, const char* password);
    bool isConnected();
private:
    // 私有成员变量和函数
};

#endif