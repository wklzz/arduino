#include <Arduino.h>
#include "websocket.h"

WebSocketsClient ws;

void WebSocketClientNew::begin(const char* host, uint16_t port, const char* url) {
    // 连接到 WebSocket 服务器
    ws.begin(host, port, url); 
    ws.onEvent([this](WStype_t type, uint8_t * payload, size_t length) {
        onEvent(type, payload, length);
    });
}

void  WebSocketClientNew::loop() {
    ws.loop();
}

void WebSocketClientNew::sendText(const char* message) {
    ws.sendTXT(message);
}

bool WebSocketClientNew::isConnected() {
    return ws.isConnected();
}

void WebSocketClientNew::onEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("Disconnected!\n");
            break;
        case WStype_CONNECTED: {
                Serial.printf(" Connected from url: %s\n", payload);
                ws.sendTXT("esp32 Connected");
            }
            break;
        case WStype_TEXT:
            Serial.printf("get Text: %s\n", payload);
            break;
    }

}
