#include "BleBatteryService.h"
#include "ArduinoBleBattery.h"

void BleBatteryService::begin()
{}

void BleBatteryService::setBatteryLevel(uint8_t level)
{
    ArduinoBleBattery.setBatteryLevel(level);
}

void BleBatteryService::updateBatteryLevel(uint8_t level)
{
    ArduinoBleBattery.updateBatteryLevel(level);
}

void BleBatteryService::setBatteryLevelStatus(const BleBatteryLevelStatus& status)
{
    ArduinoBleBattery.setBatteryLevelStatus(status);
}

void BleBatteryService::updateBatteryLevelStatus(const BleBatteryLevelStatus& status)
{
    ArduinoBleBattery.updateBatteryLevelStatus(status);
}