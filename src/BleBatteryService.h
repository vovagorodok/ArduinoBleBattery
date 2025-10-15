#pragma once
#include <Arduino.h>
#include "BleBatteryStructs.h"

class BleBatteryService
{
public:
    virtual void begin();

    virtual ~BleBatteryService() = default;

protected:
    void setBatteryLevel(BleBatteryLevel level);
    void updateBatteryLevel(BleBatteryLevel level);

    void createBatteryLevelStatus(const BleBatteryLevelStatus& status);
    void updateBatteryLevelStatus(const BleBatteryLevelStatus& status);
};