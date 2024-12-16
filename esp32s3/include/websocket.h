#ifndef WEBSOCKET_CLIENT_NEW_H
#define WEBSOCKET_CLIENT_NEW_H

#include <WebSocketsClient.h>

class WebSocketClientNew {
public:
    void begin(const char* host, uint16_t port, const char* url);
    void onEvent(WStype_t type, uint8_t * payload, size_t length);
    void sendText(const char* text);
    bool isConnected();
    void loop();
private:
    WebSocketsClient ws;
    // 其他私有成员变量
};

#endif