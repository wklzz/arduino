#include <Arduino.h>
#include <driver/adc.h>
#include <WiFi.h>
#include <esp_now.h>

esp_now_peer_info_t peerInfo;

String dataToString(uint8_t data[], int length) {
  String mac_str = "";
  for (int i = 0; i < length; i++) {
    if (data[i] < 0x10) {
      mac_str += "0";
    }
    mac_str += String(data[i], HEX);
    if (i < length - 1) {
      mac_str += ":";
    }
  }
  return mac_str;
}

// a0:20:a6:0a:c9:f1
uint8_t mac_address[] = {0xa0, 0x20, 0xa6, 0x0a, 0xc9, 0xf1}; // MAC address for ESP-NOG
// MAC: c4:d8:d5:03:57:6f
uint8_t mac_address2[] = {0xc4, 0xd8, 0xd5, 0x03, 0x57, 0x6f};
int esp_now_channel = 1;
bool connected = false;
const uint8_t REQ_CONNECT[] = "REQ_CONNECT";
const uint8_t CONFIRM_CONNECTED[] = "CONFIRM_CONNECTED";

void setup() {
  Serial.begin(115200);
  // 配置引脚为ADC
  pinMode(GPIO_NUM_4, INPUT);
  pinMode(GPIO_NUM_5, INPUT);
  pinMode(GPIO_NUM_6, INPUT);
  pinMode(GPIO_NUM_7, INPUT);

  // 初始化ADC
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_12);
  adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_12);
  adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_12);
  adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_12);

  // 初始化esp now
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  // Initialize ESP-NOW
  while(true) 
  {
  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW initialization failed");
    // Handle the error, e.g., restart or indicate failure
  } else {
    break;
    }
  }

while(true) 
{
  
  esp_err_t result = esp_now_register_send_cb([](const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Send status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail" + String(status, HEX));
  });

  if (result != ESP_OK) {
    Serial.println("esp_now_register_send_cb failed");
  } else {
    break;
  }

}
while(true ) {
  
  esp_err_t result = esp_now_register_recv_cb([](const uint8_t *mac_addr, const uint8_t *data, int data_len) {
    extern bool connected;
    connected = true;
    extern uint8_t mac_address[];
    Serial.print("Received data from ");
    for (int i = 0; i < 6; i++) {
      mac_address[i] = mac_addr[i];
      Serial.print(mac_addr[i], HEX);
      Serial.print(":");
    }
    Serial.println();
    Serial.print("Data: ");
    for (int i = 0; i < data_len; i++) {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  });

  if (result != ESP_OK) {
    Serial.println("esp_now_register_recv_cb failed");
  } else {
    break;
  }
}

peerInfo.encrypt = false;
peerInfo.ifidx = WIFI_IF_STA;
peerInfo.channel = 0;
memcpy(peerInfo.peer_addr, mac_address2, 6);
if(esp_now_add_peer(&peerInfo) != ESP_OK) {
  while(true) {
    Serial.println("esp_now_add_peer failed");
    delay(1000);
  }
}

}

void loop() {
  // 读取ADC值
  int value0 = adc1_get_raw(ADC1_CHANNEL_3);
  int value1 = adc1_get_raw(ADC1_CHANNEL_4);
  int value2 = adc1_get_raw(ADC1_CHANNEL_5);
  int value3 = adc1_get_raw(ADC1_CHANNEL_6);

  // 打印ADC值
  // Serial.print("ADC0: ");
  // Serial.println(value0);

  // Serial.print("ADC1: ");
  // Serial.println(value1);

  // Serial.print("ADC2: ");
  // Serial.println(value2);

  // Serial.print("ADC3: ");
  // Serial.println(value3);
  Serial.println("is connected: " + String(connected));

  if (true)
  {
    uint8_t data[] = { (uint8_t)value0, (uint8_t)value1, (uint8_t)value2, (uint8_t)value3};
    esp_err_t result = esp_now_send(NULL, data, sizeof(data));
    if (result != ESP_OK) {
      Serial.println("esp_now_send failed");
      Serial.println(result);
    }
    Serial.println(dataToString(mac_address2, 6));
    Serial.println(dataToString(data, 4));
  }

  delay(500);
}

void recvCallback(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  extern bool connected;
  extern uint8_t mac_address[];
  if (!connected && data == REQ_CONNECT)
  {
    for (int i = 0; i < 6; i++)
    {
      mac_address[i] = mac_addr[i];
      connected = true;
      Serial.print(mac_addr[i], HEX);
      Serial.print(":");
    }
  }
}