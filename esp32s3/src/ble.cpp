#include "ble.h"

BluetoothScanner::BluetoothScanner() {
  BLEDevice::init("ESP32");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(&myCallbacks);
  pBLEScan->setActiveScan(true);
}

void BluetoothScanner::startScan() {
  BLEScanResults results = pBLEScan->start(2, false);
  Serial.printf("Found %d devices\n", results.getCount());
  pBLEScan->clearResults();
}

void BluetoothScanner::stopScan() {
  pBLEScan->stop();
}

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.printf("Found device: %s - %s \n", advertisedDevice.toString().c_str(), advertisedDevice.getAddress().toString().c_str());
    }
};