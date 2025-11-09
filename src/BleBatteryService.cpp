#include "BleBatteryService.h"
#include "ArduinoBleBattery.h"

void BleBatteryService::handleServiceCreate()
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

void BleBatteryService::createBatteryTimeStatus(const BleBatteryTimeStatus& status)
{
    ArduinoBleBattery.createBatteryTimeStatus(status);
}

void BleBatteryService::updateBatteryTimeStatus(const BleBatteryTimeStatus& status)
{
    ArduinoBleBattery.updateBatteryTimeStatus(status);
}

void BleBatteryService::createBatteryCriticalStatus(const BleBatteryCriticalStatus& status)
{
    ArduinoBleBattery.createBatteryCriticalStatus(status);
}

void BleBatteryService::updateBatteryCriticalStatus(const BleBatteryCriticalStatus& status)
{
    ArduinoBleBattery.updateBatteryCriticalStatus(status);
}
