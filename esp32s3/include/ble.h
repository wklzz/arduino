// BluetoothScanner.h
#ifndef BLUETOOTH_SCANNER_H
#define BLUETOOTH_SCANNER_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>

class BluetoothScanner {
public:
    BluetoothScanner();
    void startScan();
    void stopScan();

private:
    BLEScan* pBLEScan;

    // Define the callback class within BluetoothScanner
    class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
        void onResult(BLEAdvertisedDevice advertisedDevice) override {
            // Handle discovered devices here
            Serial.println("Device found:");
            // Serial.println("  Name: " + advertisedDevice.getName());
            // Serial.println("  Address: " + advertisedDevice.getAddress().toString());
            Serial.println("  RSSI: " + String(advertisedDevice.getRSSI()));
            Serial.println("一些消息"); // 添加这一行
        }
    };

    MyAdvertisedDeviceCallbacks myCallbacks;
};

#endif