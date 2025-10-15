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

    const BleBatteryLevelStatus::PowerState powerState(
      BleBatteryLevelStatus::BatteryPresent::Yes,
      BleBatteryLevelStatus::WiredExternalPowerSourceConnected::Yes,
      BleBatteryLevelStatus::WirelessExternalPowerSourceConnected::No,
      BleBatteryLevelStatus::BatteryChargeState::Charging,
      BleBatteryLevelStatus::BatteryChargeLevel::Good,
      BleBatteryLevelStatus::ChargingType::UnknownOrNotCharging,
      BleBatteryLevelStatus::ChargingFaultReason{false, false, false});
    const BleBatteryLevelStatus status(powerState);

    createBatteryLevelStatus(status);
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