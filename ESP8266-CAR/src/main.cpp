#include <Arduino.h>
#include "wifiController.h"
#include "espnowController.h"
#include <espnow.h>

WiFiController wifiController("wklzz", "wkwkwkwk");
EspNowController espNowController;
uint8_t broadCastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
u8 espNowChannel = 1;

const u8 REQ_CONNECT[] = "REQ_CONNECT";
const u8 CONFIRM_CONNECTED[] = "CONFIRM_CONNECTED";

const int leftUp    = D1;  // 连接第一个LED的引脚
const int rightUp   = D3;  // 连接第二个LED的引脚
const int leftDown  = D5;  // 连接第三个LED的引脚
const int rightDown = D7;  // 连接第四个LED的引脚

void espNowCallback(uint8_t *mac_addr, uint8_t *data, uint8_t len) {
  Serial.print("Received ESP-NOW packet from: ");
}
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_recv_cb(espNowCallback);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  // int ret = esp_now_send(NULL, (uint8_t *)REQ_CONNECT, sizeof(REQ_CONNECT));
  // Serial.print("ret: ");
  // Serial.println(ret);
  // Serial.println("sent!!!!!");
  // delay(1000);

// int max = 255;
// int min = 50;
// for(int i = min; i < max; i++) {
//   analogWrite(leftUp, i);
//   analogWrite(rightUp, i);
//   analogWrite(leftDown, i);
//   analogWrite(rightDown, i);
//   delay(10);
// }
// for(int i = max; i > min; i--) {
//     analogWrite(leftUp, i);
//   analogWrite(rightUp, i);
//   analogWrite(leftDown, i);
//   analogWrite(rightDown, i);
//   delay(10);
// }

}