#pragma once
#include <Arduino.h>

using BleBatteryLevel = uint8_t;

#pragma pack(push, 1)
struct BleBatteryLevelStatus
{
    union Flags {
        struct {
            bool identifierPresent: 1;
            bool batteryLevelPresent: 1;
            bool additionalStatusPresent: 1;
            uint8_t reserved: 5;
        };
        uint8_t value;
    };

    enum class BatteryPresent
    {
        No = 0,
        Yes = 1,
    };

    enum class WiredExternalPowerSourceConnected
    {
        No = 0,
        Yes = 1,
        Unknown = 2,
    };

    enum class WirelessExternalPowerSourceConnected
    {
        No = 0,
        Yes = 1,
        Unknown = 2,
    };

    enum class BatteryChargeState
    {
        Unknown = 0,
        Charging = 1,
        DischargingActive = 2,
        DischargingInactive = 3,
    };

    enum class BatteryChargeLevel
    {
        Unknown = 0,
        Good = 1,
        Low = 2,
        Critical = 3,
    };

    enum class ChargingType
    {
        UnknownOrNotCharging = 0,
        ConstantCurrent = 1,
        ConstantVoltage = 2,
        Trickle = 3,
        Float = 4,
    };

    union ChargingFaultReason
    {
        struct {
            uint16_t battery: 1;
            uint16_t externalPowerSource: 1;
            uint16_t other: 1;
        };
        uint16_t value;
    };

    struct PowerState
    {
        PowerState(BatteryPresent batteryPresent = {},
                   WiredExternalPowerSourceConnected wiredExternalPowerSourceConnected = {},
                   WirelessExternalPowerSourceConnected wirelessExternalPowerSourceConnected = {},
                   BatteryChargeState batteryChargeState = {},
                   BatteryChargeLevel batteryChargeLevel = {},
                   ChargingType chargingType = {},
                   ChargingFaultReason chargingFaultReason = {}):
            batteryPresent(static_cast<uint16_t>(batteryPresent)),
            wiredExternalPowerSourceConnected(static_cast<uint16_t>(wiredExternalPowerSourceConnected)),
            wirelessExternalPowerSourceConnected(static_cast<uint16_t>(wirelessExternalPowerSourceConnected)),
            batteryChargeState(static_cast<uint16_t>(batteryChargeState)),
            batteryChargeLevel(static_cast<uint16_t>(batteryChargeLevel)),
            chargingType(static_cast<uint16_t>(chargingType)),
            chargingFaultReason(chargingFaultReason.value),
            reserved()
        {}

    private:
        uint16_t batteryPresent: 1;
        uint16_t wiredExternalPowerSourceConnected: 2;
        uint16_t wirelessExternalPowerSourceConnected: 2;
        uint16_t batteryChargeState: 2;
        uint16_t batteryChargeLevel: 2;
        uint16_t chargingType: 3;
        uint16_t chargingFaultReason: 3;
        uint16_t reserved: 1;
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