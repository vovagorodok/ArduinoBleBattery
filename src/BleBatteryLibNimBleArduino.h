#pragma once
#include "BleBatteryDefines.h"
#ifdef BLE_BATTERY_BLE_LIB_NIM_BLE_ARDUINO
#include "BleBatteryUuids.h"
#include "BleBatteryService.h"

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
    void setBatteryLevel(uint8_t level);
    void updateBatteryLevel(uint8_t level);

    BLECharacteristic* _levelCharacteristic;
};

extern BleBatteryLib ArduinoBleBattery;
#endif