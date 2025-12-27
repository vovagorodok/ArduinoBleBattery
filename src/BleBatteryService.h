#pragma once
#include "BleBatteryDefinesArduino.h"
#include "BleBatteryStructs.h"

class BleBatteryService
{
public:
    virtual void handleServiceCreate();

    virtual ~BleBatteryService() = default;

protected:
    void setBatteryLevel(BleBatteryLevel level);
    void updateBatteryLevel(BleBatteryLevel level);

    void createBatteryLevelStatus(const BleBatteryLevelStatus& status);
    void updateBatteryLevelStatus(const BleBatteryLevelStatus& status);

    void createBatteryTimeStatus(const BleBatteryTimeStatus& status);
    void updateBatteryTimeStatus(const BleBatteryTimeStatus& status);

    void createBatteryCriticalStatus(const BleBatteryCriticalStatus& status);
    void updateBatteryCriticalStatus(const BleBatteryCriticalStatus& status);
};