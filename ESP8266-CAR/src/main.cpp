#include <Arduino.h>
#include <cstdlib>
/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>

const int leftUp    = D1;  // 连接第一个LED的引脚
const int rightUp   = D3;  // 连接第二个LED的引脚
const int leftDown  = D5;  // 连接第三个LED的引脚
const int rightDown = D7;  // 连接第四个LED的引脚
const int backLeftUp    = D2;  // 连接第一个LED的引脚
const int backRightUp   = D4;  // 连接第二个LED的引脚
const int backLeftDown  = D6;  // 连接第三个LED的引脚
const int backRightDown = D8;  // 连接第四个LED的引脚

const int MAX_SPEED = 255;
const int MIN_SPEED = 50;
const int MIN_TURN = 50;

const int GD_CLEAR = 0;
const int GD_FORWARD = 1;
const int GD_BACKWARD = 2;
const int GD_TURN_LEFT = 3;
const int GD_TRUN_RIGHT = 4;

int gdirection = 0; // 

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char a[32];
  int ax;
  int ay;
  int bx;
  int by;
} struct_message;

// Create a struct_message called myData
struct_message myData;

int mapValue(int value, int div) {
  // 检查输入值是否在有效范围内
  if (value < 0 || value > 4095) {
    return -1; // 或抛出异常，表示输入值无效
  }

  // 计算映射后的值
  int mappedValue = (value - 2048) / div;

  return mappedValue;
}

  // 函数功能：计算四轮小车的左右轮速度
// 输入：
//   speed：油门大小，范围 -255 到 255
//   direction：转向方向，范围 -127 到 127
// 返回值：
//   一个数组，分别表示左轮和右轮的速度
int* calculateWheelSpeeds(int speed, int direction) {
    static int wheelSpeeds[2]; // 静态数组，用于存储左右轮速度
    speed = abs(speed);
    // 计算左右轮速度
    if (abs(direction) < MIN_TURN) {
        // 方向值较小，不转向，左右轮速度相同
        wheelSpeeds[0] = speed;
        wheelSpeeds[1] = speed;
    } else {
        wheelSpeeds[0] = speed + direction; // 左轮速度
        wheelSpeeds[1] = speed - direction; // 右轮速度
    }
    for(int i = 0; i < 2; i++) {
      if(wheelSpeeds[i] < MIN_SPEED) {
        wheelSpeeds[i] = MIN_SPEED;
      } else if (wheelSpeeds[i] > MAX_SPEED) {
        wheelSpeeds[i] = MAX_SPEED;
      }
    }

    return wheelSpeeds;
}

void forward(int* wheelSpeed) {
  analogWrite(leftUp, wheelSpeed[0]);
  analogWrite(rightUp, wheelSpeed[1]);
  analogWrite(leftDown, wheelSpeed[0]);
  analogWrite(rightDown, wheelSpeed[1]);
}

void backward(int* wheelSpeed) {
  analogWrite(backLeftUp, wheelSpeed[0]);
  analogWrite(backLeftDown, wheelSpeed[0]);
  analogWrite(backRightUp, wheelSpeed[1]);
  analogWrite(backRightDown, wheelSpeed[1]);
}

void clear(int direction) {
  extern int gdirection;
  // Serial.println("before clear :" + String(gdirection) + " / " + String(direction));
  if (direction == gdirection ) {
    return;
  }
  gdirection = direction;
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
  // Serial.println("after clear :" + String(gdirection) + " / " + String(direction));
  delay(10);
}

// 函数功能：计算四轮小车原地左右转的速度
// 输入：
//   direction：转向方向，范围 -255 到 255
// 返回值：
//   一个数组，分别表示左前轮、右前轮、左后轮、右后轮的速度
int* calculateWheelSpeedsForTurn(int direction) {
    static int wheelSpeeds[4]; // 静态数组，用于存储四个轮子的速度
    // 计算轮子速度
    if (abs(direction) < MIN_TURN) {
        // 方向值较小，不转向，所有轮子速度为0
        for (int i = 0; i < 4; ++i) {
            wheelSpeeds[i] = 0;
        }
    } else {
        // 根据转向方向计算轮子速度
        int directionSign = direction > 0 ? 1 : -1; // 获取转向方向符号
        for (int i = 0; i < 4; ++i) {
            wheelSpeeds[i] = abs(directionSign * (i % 2 ? -direction : direction));
        }
    }

    return wheelSpeeds;
}

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  int speed = mapValue(myData.ay, 8);
  int direction = mapValue(myData.ax, 16);
  int turn = mapValue(myData.bx, 8);
  if(abs(direction) < 10) {
    direction = 0;
  }
  
  if(abs(turn) >= MIN_TURN) {
    int* wheelSpeed = calculateWheelSpeedsForTurn(turn);
    if(turn < 0) {
      clear(GD_TURN_LEFT);
      analogWrite(backLeftUp, wheelSpeed[0]);
      analogWrite(rightUp, wheelSpeed[1]);
      analogWrite(backLeftDown, wheelSpeed[2]);
      analogWrite(rightDown, wheelSpeed[3]);
    } else {
      clear(GD_TRUN_RIGHT);
      analogWrite(leftUp, wheelSpeed[0]);
      analogWrite(backRightUp, wheelSpeed[1]);
      analogWrite(leftDown, wheelSpeed[2]);
      analogWrite(backRightDown, wheelSpeed[3]);
    }
  } else if (abs(speed) < MIN_SPEED) {
    // 
    clear(GD_CLEAR);
  } else if(speed < 0) {
    // 前进
    clear(GD_FORWARD);
    int* wheelSpeed = calculateWheelSpeeds(speed, direction);
    forward(wheelSpeed);
  } else {
    // 后退
    clear(GD_BACKWARD);
    int* wheelSpeed = calculateWheelSpeeds(speed, direction);
    backward(wheelSpeed);
  }
}
 
void setup() {
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  clear(GD_CLEAR); 
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}

/*
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
*/