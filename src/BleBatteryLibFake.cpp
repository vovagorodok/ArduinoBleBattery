#include "BleBatteryLibFake.h"
#ifdef BLE_BATTERY_BLE_LIB_FAKE

bool BleBatteryLib::begin(const char* deviceName,
                          BleBatteryService& batteryService)
{
    return false;
}

bool BleBatteryLib::begin(BleBatteryService& batteryService)
{
    return false;
}

bool BleBatteryLib::begin(const std::string& deviceName,
                          BleBatteryService& batteryService)
{
    return false;
}

bool BleBatteryLib::begin(BleBatteryServerFake* server,
                          BleBatteryService& batteryService)
{
    return false;
}

void BleBatteryLib::setBatteryLevel(BleBatteryLevel level)
{}

void BleBatteryLib::updateBatteryLevel(BleBatteryLevel level)
{}

void BleBatteryLib::createBatteryLevelStatus(const BleBatteryLevelStatus& status)
{}

void BleBatteryLib::updateBatteryLevelStatus(const BleBatteryLevelStatus& status)
{}

void BleBatteryLib::createBatteryTimeStatus(const BleBatteryTimeStatus& status)
{}

void BleBatteryLib::updateBatteryTimeStatus(const BleBatteryTimeStatus& status)
{}

void BleBatteryLib::createBatteryCriticalStatus(const BleBatteryCriticalStatus& status)
{}

void BleBatteryLib::updateBatteryCriticalStatus(const BleBatteryCriticalStatus& status)
{}

BleBatteryLib ArduinoBleBattery{};
#endif