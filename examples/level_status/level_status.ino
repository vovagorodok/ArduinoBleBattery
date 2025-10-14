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

class MyBatteryLevelStatusService : public MyBatteryService
{
public:
  void begin() override {
    MyBatteryService::begin();

    BleBatteryLevelStatus status(BleBatteryLevelStatus::PowerState{
      .batteryPresent = BleBatteryLevelStatus::BatteryPresent::Yes,
      .wiredExternalPowerSourceConnected = BleBatteryLevelStatus::WiredExternalPowerSourceConnected::Yes,
      .wirelessExternalPowerSourceConnected = BleBatteryLevelStatus::WirelessExternalPowerSourceConnected::No,
      .batteryChargeState = BleBatteryLevelStatus::BatteryChargeState::Charging,
      .batteryChargeLevel = BleBatteryLevelStatus::BatteryChargeLevel::Good}); 
    setBatteryLevelStatus(status);
  }
};

MyBatteryLevelStatusService batteryService{};

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