#pragma once
#include "BleBatteryDefines.h"
#ifdef BLE_BATTERY_BLE_LIB_ESP32
#include "BleBatteryUuids.h"
#include "BleBatteryService.h"
#include "BleBatteryStructs.h"

class BleBatteryLib
{
public:
    BleBatteryLib();

    void begin(const std::string& deviceName,
               BleBatteryService& batteryService);
    void begin(BLEServer* server,
               BleBatteryService& batteryService);

private:
    friend BleBatteryService;
    void setBatteryLevel(uint8_t level);
    void updateBatteryLevel(uint8_t level);

    void setBatteryLevelStatus(const BleBatteryLevelStatus& status);
    void updateBatteryLevelStatus(const BleBatteryLevelStatus& status);

    BLEService* _service;
    BLECharacteristic* _levelCharacteristic;
    BLECharacteristic* _levelStatusCharacteristic;
};

extern BleBatteryLib ArduinoBleBattery;
#endif