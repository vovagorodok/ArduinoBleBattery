#pragma once
#include "BleBatteryDefines.h"
#ifdef BLE_BATTERY_BLE_LIB_NIM_BLE_ARDUINO
#include "BleBatteryUuids.h"
#include "BleBatteryService.h"
#include "BleBatteryStructs.h"

class BleBatteryLib
{
public:
    BleBatteryLib();

    bool begin(const std::string& deviceName,
               BleBatteryService& batteryService);
    bool begin(BLEServer* server,
               BleBatteryService& batteryService);

private:
    friend BleBatteryService;
    void setBatteryLevel(BleBatteryLevel level);
    void updateBatteryLevel(BleBatteryLevel level);

    void createBatteryLevelStatus(const BleBatteryLevelStatus& status);
    void updateBatteryLevelStatus(const BleBatteryLevelStatus& status);

    BLEService* _service;
    BLECharacteristic* _levelCharacteristic;
    BLECharacteristic* _levelStatusCharacteristic;
};

extern BleBatteryLib ArduinoBleBattery;
#endif