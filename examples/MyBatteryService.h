#pragma once
#include <ArduinoBleBattery.h>

class MyBatteryService : public BleBatteryService
{
public:
  void begin() override {
    setBatteryLevel(100);
  }
  void checkBatteryLevel() {
    if (Serial.available()) {
      uint8_t level = Serial.parseInt();
      Serial.print("update battery level: ");
      Serial.println(level);
      updateBatteryLevel(level);
    }
  }
};