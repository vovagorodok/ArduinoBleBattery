#include <Arduino.h>
#include <ArduinoBleBattery.h>
#include "../MyBatteryService.h"

class MyBatteryStatusService : public MyBatteryService
{
public:
  void handleServiceCreate() override {
    MyBatteryService::handleServiceCreate();

    const BleBatteryLevelStatus::PowerState powerState(
      BleBatteryLevelStatus::BatteryPresent::Yes,
      BleBatteryLevelStatus::WiredExternalPowerSourceConnected::Yes,
      BleBatteryLevelStatus::WirelessExternalPowerSourceConnected::No,
      BleBatteryLevelStatus::BatteryChargeState::Charging,
      BleBatteryLevelStatus::BatteryChargeLevel::Good,
      BleBatteryLevelStatus::ChargingType::UnknownOrNotCharging,
      BleBatteryLevelStatus::ChargingFaultReason{false, false, false});
    const BleBatteryLevelStatus levelStatus(powerState);
    createBatteryLevelStatus(levelStatus);

    const BleBatteryTimeStatus timeStatus(BleBatteryTimeStatus::TimeUntilDischarged::Max);
    createBatteryTimeStatus(timeStatus);

    const BleBatteryCriticalStatus criticalStatus{false, false};
    createBatteryCriticalStatus(criticalStatus);
  }
};

MyBatteryStatusService batteryService{};

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