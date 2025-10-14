#include "BleBatteryLibNimBleArduino.h"
#ifdef BLE_BATTERY_BLE_LIB_NIM_BLE_ARDUINO

BleBatteryLib::BleBatteryLib():
    _levelCharacteristic()
{}

bool BleBatteryLib::begin(const std::string& deviceName,
                          BleBatteryService& batteryService)
{
    BLEDevice::init(deviceName);
    auto* server = BLEDevice::createServer();

    if(!begin(server, batteryService))
        return false;

    auto* advertising = server->getAdvertising();
    advertising->addServiceUUID(BLE_BATTERY_SERVICE_UUID);
#ifdef BLE_BATTERY_BLE_LIB_NIM_BLE_ARDUINO_V1
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    advertising->setMaxPreferred(0x12);
#endif
    return advertising->start();
}

bool BleBatteryLib::begin(BLEServer* server,
                          BleBatteryService& batteryService)
{
    auto* service = server->createService(BLE_BATTERY_SERVICE_UUID);

    auto* levelCharacteristic = service->createCharacteristic(
        BLE_BATTERY_CHARACTERISTIC_UUID_LEVEL,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY,
        sizeof(uint8_t)
    );
    _levelCharacteristic = levelCharacteristic;
    batteryService.begin();

    return service->start();
}

void BleBatteryLib::setBatteryLevel(uint8_t level)
{
    _levelCharacteristic->setValue(reinterpret_cast<const uint8_t*>(&level), sizeof(uint8_t));
}

void BleBatteryLib::sendBatteryLevel(uint8_t level)
{
    setBatteryLevel(level);
    _levelCharacteristic->notify();
}

BleBatteryLib ArduinoBleBattery{};
#endif