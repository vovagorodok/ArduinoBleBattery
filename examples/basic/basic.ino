#include <Arduino.h>
#include <ArduinoBleBattery.h>
#include "../MyBatteryService.h"

MyBatteryService batteryService{};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  ArduinoBleBattery.begin("Arduino Ble Battery", batteryService);
}

void loop() {
#ifdef BLE_BATTERY_LIB_ARDUINO_BLE
  BLE.poll();
#endif
  batteryService.checkBatteryLevel();
}