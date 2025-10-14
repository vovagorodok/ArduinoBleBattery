#include "BleBatteryLibArduinoBle.h"
#ifdef BLE_BATTERY_BLE_LIB_ARDUINO_BLE

namespace
{
BLEService service(BLE_BATTERY_SERVICE_UUID);
BLETypedCharacteristic<uint8_t> levelCharacteristic(BLE_BATTERY_CHARACTERISTIC_UUID_LEVEL, BLERead | BLENotify);
BLECharacteristic levelStatusCharacteristic(BLE_BATTERY_CHARACTERISTIC_UUID_LEVEL_STATUS, BLERead | BLENotify, sizeof(BleBatteryLevelStatus));
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

    batteryService.begin();

    BLE.addService(service);
    return BLE.setAdvertisedService(service);
}

void BleBatteryLib::setBatteryLevel(uint8_t level)
{
    levelCharacteristic.setValue(level);
}

void BleBatteryLib::updateBatteryLevel(uint8_t level)
{
    levelCharacteristic.setValue(level);
}

void BleBatteryLib::setBatteryLevelStatus(const BleBatteryLevelStatus& status)
{
    service.addCharacteristic(levelStatusCharacteristic);
    levelStatusCharacteristic.setValue(reinterpret_cast<const uint8_t*>(&status), sizeof(BleBatteryLevelStatus));
}

void BleBatteryLib::updateBatteryLevelStatus(const BleBatteryLevelStatus& status)
{
    levelStatusCharacteristic.setValue(reinterpret_cast<const uint8_t*>(&status), sizeof(BleBatteryLevelStatus));
}

BleBatteryLib ArduinoBleBattery{};
#endif