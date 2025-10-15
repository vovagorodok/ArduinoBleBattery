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
    void setBatteryLevel(BleBatteryLevel level);
    void updateBatteryLevel(BleBatteryLevel level);

    void createBatteryLevelStatus(const BleBatteryLevelStatus& status);
    void updateBatteryLevelStatus(const BleBatteryLevelStatus& status);

    void createBatteryTimeStatus(const BleBatteryTimeStatus& status);
    void updateBatteryTimeStatus(const BleBatteryTimeStatus& status);

    void createBatteryCriticalStatus(const BleBatteryCriticalStatus& status);
    void updateBatteryCriticalStatus(const BleBatteryCriticalStatus& status);
};

extern BleBatteryLib ArduinoBleBattery;
#endif