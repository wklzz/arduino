#include <Arduino.h>
#include "wificonn.h"
#include "websocket.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include <esp_bt.h>

#define SCAN_TIME 5
WiFiManager wifiManager;
WebSocketClientNew webSocketClientNew;


// 将设备地址转换为字符串
char *bda2str(const uint8_t *bda, char *str) {
  sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x",
          bda[0], bda[1], bda[2], bda[3], bda[4], bda[5]);
  return str;
}

// 蓝牙扫描回调函数
void btScanCallback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param) {
  if (event == ESP_BT_GAP_DISC_RES_EVT) {
    // 发现设备
    char bda_str[18];
    // 输出设备信息
    Serial.printf("Device found: Address: %s", bda2str(param->disc_res.bda, bda_str));
  } else if (event == ESP_BT_GAP_DISC_STATE_CHANGED_EVT) {
    // 扫描状态变化
    if (param->disc_st_chg.state == ESP_BT_GAP_DISCOVERY_STARTED) {
      Serial.println("Discovery started...");
    } else if (param->disc_st_chg.state == ESP_BT_GAP_DISCOVERY_STOPPED) {
      Serial.println("Discovery stopped...");
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  wifiManager.begin("wklzz", "wkwkwkwk");
  // webSocketClientNew.begin("47.99.35.179", 7004, "/ws");
 Serial.println("Initializing Bluetooth...");

// 停止 BLE，释放资源
  esp_bt_controller_mem_release(ESP_BT_MODE_BLE);

  // 初始化蓝牙控制器为经典蓝牙模式
  esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
  if (esp_bt_controller_init(&bt_cfg) != ESP_OK) {
    Serial.println("Failed to initialize Bluetooth controller");
    return;
  }

  if (esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT) != ESP_OK) {
    Serial.println("Failed to enable Bluetooth controller");
    return;
  }

  // 初始化 Bluedroid 堆栈
  if (esp_bluedroid_init() != ESP_OK) {
    Serial.println("Failed to initialize Bluedroid stack");
    return;
  }

  if (esp_bluedroid_enable() != ESP_OK) {
    Serial.println("Failed to enable Bluedroid stack");
    return;
  }

  Serial.println("Classic Bluetooth initialized and ready.");
  // 初始化蓝牙控制器
  if (!btStart()) {
    Serial.println("Failed to initialize Bluetooth controller");
    return;
  }

  // 初始化经典蓝牙
  if (esp_bluedroid_init() != ESP_OK) {
    Serial.println("Failed to initialize Bluedroid stack");
    return;
  }
  if (esp_bluedroid_enable() != ESP_OK) {
    Serial.println("Failed to enable Bluedroid stack");
    return;
  }

  // 注册扫描回调
  esp_bt_gap_register_callback(btScanCallback);

  // 开始设备发现（扫描）
  Serial.println("Starting Bluetooth device discovery...");
  esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 10, 0);
}

void loop() {
  // webSocketClientNew.loop();
  // put your main code here, to run repeatedly:
  // if (webSocketClientNew.isConnected()) {
  //   webSocketClientNew.sendText("Hello, world!");
  // } else {
  //   Serial.println("websocket not connected!");
  // }

  // delay(1000); // 延时1秒
}
