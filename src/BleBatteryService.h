#pragma once
#include <Arduino.h>
#include "BleBatteryStructs.h"

class BleBatteryService
{
public:
    virtual void begin();

    virtual ~BleBatteryService() = default;

protected:
    void setBatteryLevel(uint8_t level);
    void updateBatteryLevel(uint8_t level);

    void setBatteryLevelStatus(const BleBatteryLevelStatus& status);
    void updateBatteryLevelStatus(const BleBatteryLevelStatus& status);
};