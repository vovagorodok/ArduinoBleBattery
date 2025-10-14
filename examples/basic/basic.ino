#include <Arduino.h>
#include <ArduinoBleBattery.h>
#include "../MyBatteryService.h"

#ifdef BLE_BATTERY_LOGS
#ifndef ARDUINO_ARCH_ESP32
extern "C" {
int _write(int fd, char *ptr, int len) {
  (void) fd;
  return Serial.write(ptr, len);
}
}
#endif
#endif

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