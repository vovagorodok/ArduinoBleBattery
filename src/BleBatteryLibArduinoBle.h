#pragma once
#include "BleBatteryDefines.h"
#ifdef BLE_BATTERY_BLE_LIB_ARDUINO_BLE
#include "BleBatteryUuids.h"
#include "BleBatteryService.h"

class BleBatteryLib
{
public:
    bool begin(const char* deviceName,
               BleBatteryService& batteryService);
    bool begin(BleBatteryService& batteryService);

private:
    friend BleBatteryService;
    void setBatteryLevel(uint8_t level);
    void updateBatteryLevel(uint8_t level);

    void setBatteryLevelStatus(const BleBatteryLevelStatus& status);
    void updateBatteryLevelStatus(const BleBatteryLevelStatus& status);
};

extern BleBatteryLib ArduinoBleBattery;
#endif