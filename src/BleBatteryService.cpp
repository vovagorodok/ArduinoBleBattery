#include "BleBatteryService.h"
#include "ArduinoBleBattery.h"

void BleBatteryService::begin()
{}

void BleBatteryService::setBatteryLevel(uint8_t level)
{
    ArduinoBleBattery.setBatteryLevel(level);
}

void BleBatteryService::sendBatteryLevel(uint8_t level)
{
    ArduinoBleBattery.sendBatteryLevel(level);
}