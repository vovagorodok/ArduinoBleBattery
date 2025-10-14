#pragma once
#include <Arduino.h>

#pragma pack(push, 1)
struct BleBatteryLevelStatus
{
    struct Flags
    {
        bool identifierPresent: 1;
        bool batteryLevelPresent: 1;
        bool additionalStatusPresent: 1;
        unsigned reserved: 5;
    };

    enum class BatteryPresent: unsigned
    {
        No = 0,
        Yes = 1,
    };

    enum class WiredExternalPowerSourceConnected: unsigned
    {
        No = 0,
        Yes = 1,
        Unknown = 2,
    };

    enum class WirelessExternalPowerSourceConnected: unsigned
    {
        No = 0,
        Yes = 1,
        Unknown = 2,
    };

    enum class BatteryChargeState: unsigned
    {
        Unknown = 0,
        Charging = 1,
        DischargingActive = 2,
        DischargingInactive = 3,
    };

    enum class BatteryChargeLevel: unsigned
    {
        Unknown = 0,
        Good = 1,
        Low = 2,
        Critical = 3,
    };

    enum class ChargingType: unsigned
    {
        Unknown = 0,
        NotCharging = Unknown,
        ConstantCurrent = 1,
        ConstantVoltage = 2,
        Trickle = 3,
        Float = 4,
    };

    struct ChargingFaultReason
    {
        bool battery: 1;
        bool externalPowerSource: 1;
        bool other: 1;
    };

    struct PowerState
    {
        PowerState(BatteryPresent batteryPresent = BatteryPresent::No,
                   WiredExternalPowerSourceConnected wiredExternalPowerSourceConnected = WiredExternalPowerSourceConnected::Unknown,
                   WirelessExternalPowerSourceConnected wirelessExternalPowerSourceConnected = WirelessExternalPowerSourceConnected::Unknown,
                   BatteryChargeState batteryChargeState = BatteryChargeState::Unknown,
                   BatteryChargeLevel batteryChargeLevel = BatteryChargeLevel::Unknown,
                   ChargingType chargingType = ChargingType::Unknown,
                   ChargingFaultReason chargingFaultReason = {false, false, false}):
            batteryPresent(static_cast<unsigned>(batteryPresent)),
            wiredExternalPowerSourceConnected(static_cast<unsigned>(wiredExternalPowerSourceConnected)),
            wirelessExternalPowerSourceConnected(static_cast<unsigned>(wirelessExternalPowerSourceConnected)),
            batteryChargeState(static_cast<unsigned>(batteryChargeState)),
            batteryChargeLevel(static_cast<unsigned>(batteryChargeLevel)),
            chargingType(static_cast<unsigned>(chargingType)),
            chargingFaultReason(chargingFaultReason),
            reserved()
        {}

        unsigned batteryPresent: 1;
        unsigned wiredExternalPowerSourceConnected: 2;
        unsigned wirelessExternalPowerSourceConnected: 2;
        unsigned batteryChargeState: 2;
        unsigned batteryChargeLevel: 2;
        unsigned chargingType: 3;
        ChargingFaultReason chargingFaultReason;
        unsigned reserved: 1;
    };

    BleBatteryLevelStatus(PowerState powerState):
        flags(),
        powerState(powerState)
    {}

private:
    Flags flags;
    PowerState powerState;
};
#pragma pack(pop)