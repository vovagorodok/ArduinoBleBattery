#include "BleBatteryService.h"
#include "ArduinoBleBattery.h"

void BleBatteryService::begin()
{}

void BleBatteryService::setBatteryLevel(BleBatteryLevel level)
{
    ArduinoBleBattery.setBatteryLevel(level);
}

void BleBatteryService::updateBatteryLevel(BleBatteryLevel level)
{
    ArduinoBleBattery.updateBatteryLevel(level);
}

void BleBatteryService::createBatteryLevelStatus(const BleBatteryLevelStatus& status)
{
    ArduinoBleBattery.createBatteryLevelStatus(status);
}

void BleBatteryService::updateBatteryLevelStatus(const BleBatteryLevelStatus& status)
{
    ArduinoBleBattery.updateBatteryLevelStatus(status);
}