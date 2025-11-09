#include "BleBatteryLibArduinoBle.h"
#ifdef BLE_BATTERY_BLE_LIB_ARDUINO_BLE

namespace
{
BLEService service(BLE_BATTERY_SERVICE_UUID);
BLETypedCharacteristic<BleBatteryLevel> levelCharacteristic(BLE_BATTERY_CHARACTERISTIC_UUID_LEVEL, BLERead | BLENotify);
BLECharacteristic levelStatusCharacteristic(BLE_BATTERY_CHARACTERISTIC_UUID_LEVEL_STATUS, BLERead | BLENotify, sizeof(BleBatteryLevelStatus));
BLECharacteristic timeStatusCharacteristic(BLE_BATTERY_CHARACTERISTIC_UUID_TIME_STATUS, BLERead | BLENotify, sizeof(BleBatteryTimeStatus));
BLECharacteristic criticalStatusCharacteristic(BLE_BATTERY_CHARACTERISTIC_UUID_CRITICAL_STATUS, BLERead | BLENotify, sizeof(BleBatteryCriticalStatus));
}

bool BleBatteryLib::begin(const char* deviceName,
                          BleBatteryService& batteryService)
{
    if (!BLE.begin())
        return false;

    BLE.setLocalName(deviceName);
    BLE.setDeviceName(deviceName);

    if (!begin(batteryService))
        return false;

    return BLE.advertise();
}

bool BleBatteryLib::begin(BleBatteryService& batteryService)
{
    service.addCharacteristic(levelCharacteristic);

    batteryService.handleServiceCreate();

    BLE.addService(service);
    return BLE.setAdvertisedService(service);
}

void BleBatteryLib::setBatteryLevel(BleBatteryLevel level)
{
    levelCharacteristic.setValue(level);
}

void BleBatteryLib::updateBatteryLevel(BleBatteryLevel level)
{
    levelCharacteristic.setValue(level);
}

void BleBatteryLib::createBatteryLevelStatus(const BleBatteryLevelStatus& status)
{
    service.addCharacteristic(levelStatusCharacteristic);
    levelStatusCharacteristic.setValue(reinterpret_cast<const uint8_t*>(&status), sizeof(BleBatteryLevelStatus));
}

void BleBatteryLib::updateBatteryLevelStatus(const BleBatteryLevelStatus& status)
{
    levelStatusCharacteristic.setValue(reinterpret_cast<const uint8_t*>(&status), sizeof(BleBatteryLevelStatus));
}

void BleBatteryLib::createBatteryTimeStatus(const BleBatteryTimeStatus& status)
{
    service.addCharacteristic(timeStatusCharacteristic);
    timeStatusCharacteristic.setValue(reinterpret_cast<const uint8_t*>(&status), sizeof(BleBatteryTimeStatus));
}

void BleBatteryLib::updateBatteryTimeStatus(const BleBatteryTimeStatus& status)
{
    timeStatusCharacteristic.setValue(reinterpret_cast<const uint8_t*>(&status), sizeof(BleBatteryTimeStatus));
}

void BleBatteryLib::createBatteryCriticalStatus(const BleBatteryCriticalStatus& status)
{
    service.addCharacteristic(criticalStatusCharacteristic);
    criticalStatusCharacteristic.setValue(reinterpret_cast<const uint8_t*>(&status), sizeof(BleBatteryCriticalStatus));
}

void BleBatteryLib::updateBatteryCriticalStatus(const BleBatteryCriticalStatus& status)
{
    criticalStatusCharacteristic.setValue(reinterpret_cast<const uint8_t*>(&status), sizeof(BleBatteryCriticalStatus));
}

BleBatteryLib ArduinoBleBattery{};
#endif