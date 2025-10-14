#pragma once
#include <Arduino.h>

class BleBatteryService
{
public:
    virtual void begin();

    virtual ~BleBatteryService() = default;

protected:
    void setBatteryLevel(uint8_t level);
    void sendBatteryLevel(uint8_t level);
};