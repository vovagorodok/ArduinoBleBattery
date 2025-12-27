#pragma once
#include "BleBatteryDefines.h"
#ifdef BLE_BATTERY_BLE_LIB_FAKE
#include "BleBatteryUuids.h"
#include "BleBatteryService.h"
#include <string>

using BleBatteryServerFake = int;

class BleBatteryLib
{
public:
    bool begin(const char* deviceName,
               BleBatteryService& batteryService);
    bool begin(BleBatteryService& batteryService);
    bool begin(const std::string& deviceName,
               BleBatteryService& batteryService);
    bool begin(BleBatteryServerFake* server,
               BleBatteryService& batteryService);

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