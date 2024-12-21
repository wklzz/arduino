#include <Arduino.h>
#include <vector>

const int PIN_ENABLE = GPIO_NUM_15;

const byte startByte = 0xBB; // 假设起始符为0xAA
const byte endByte = 0x7E;   // 假设结束符为0xBB

std::vector<uint8_t> generateFrame(uint8_t command, const std::vector<uint8_t>& parameter) {
    std::vector<uint8_t> frame;
    frame.push_back(0xBB);  // 帧头
    frame.push_back(0x00);
    frame.push_back(command);

    // 计算参数长度并添加到帧中
    uint8_t pl = parameter.size();
        // 将16位长度拆分成两个字节，这里假设为大端字节序
    uint8_t highByte = pl >> 8;
    uint8_t lowByte = pl & 0xFF;
    frame.push_back(highByte);
    frame.push_back(lowByte);

    // 添加参数数据
    frame.insert(frame.end(), parameter.begin(), parameter.end());

    // 计算校验位
    uint8_t checksum = 0;
    for (size_t i = 1; i < frame.size(); ++i) {
        checksum += frame[i];
    }

    frame.push_back(checksum);  // 添加校验位
    frame.push_back(0x7E);  // 帧尾

    return frame;
}

void read() {
  Serial.println("receive callback data !!!!!!!!");
  bool start = false;
  std::vector<byte> data;
  int idx = 0;
  while (Serial2.available()) {
    byte incomingByte = Serial2.read();
    Serial.printf("<%X>/", incomingByte);

    if (idx > 300) {
      break;
    }
    if (incomingByte == startByte) {
      start = true;
    }
    if (start) {
      data.push_back(incomingByte);
      idx++;
    }
    if (incomingByte == endByte) {
      start = false;
    }
  }
  if(data.size()> 0 && start == false) {
    for(byte data : data) {
      Serial.printf("<%X>/",data);
    }
    Serial.println();
    for(byte data : data) {
      Serial.print(data);
    }
    Serial.println();
  }
  start = false;
  data.clear();
  idx = 0;
}

void sendFrame(std::vector<uint8_t> frame) {
  Serial.print("send data : ");
  for (uint8_t byte : frame) {
    Serial2.write(byte);
    Serial.printf("%2X:", byte);
  }
  Serial.println();
}

void setup() {
  pinMode(PIN_ENABLE, OUTPUT);
  digitalWrite(PIN_ENABLE, HIGH);
  Serial.begin(115200);
  Serial.println("serial num <SOC_UART_NUM> : " + String(SOC_UART_NUM));
  Serial2.begin(921600, SERIAL_8N1, GPIO_NUM_19, GPIO_NUM_20);
  OnReceiveCb cb = []() { read(); };
  Serial2.onReceive(cb);
}

void loop() {
  // put your main code here, to run repeatedly:
  std::vector<uint8_t> parameter = {0x00};
  std::vector<uint8_t> data = generateFrame(0x03, parameter);
  delay(5000);
  // Serial.println("serial num <SOC_UART_NUM> : " + String(SOC_UART_NUM));
  sendFrame(data);
}