#include "BleBatteryLibESP32.h"
#ifdef BLE_BATTERY_BLE_LIB_ESP32

BleBatteryLib::BleBatteryLib():
    _levelCharacteristic()
{}

void BleBatteryLib::begin(const std::string& deviceName,
                          BleBatteryService& batteryService)
{
    BLEDevice::init(deviceName);
    auto* server = BLEDevice::createServer();

    begin(server, batteryService);

    auto* advertising = server->getAdvertising();
    advertising->addServiceUUID(BLE_BATTERY_SERVICE_UUID);
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    advertising->setMaxPreferred(0x12);
    advertising->start();
}

void BleBatteryLib::begin(BLEServer* server,
                          BleBatteryService& batteryService)
{
    auto* service = server->createService(BLE_BATTERY_SERVICE_UUID);

    auto* levelCharacteristic = service->createCharacteristic(
        BLE_BATTERY_CHARACTERISTIC_UUID_LEVEL,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    _levelCharacteristic = levelCharacteristic;
    batteryService.begin();

    service->start();
}

void BleBatteryLib::setBatteryLevel(uint8_t level)
{
    _levelCharacteristic->setValue(reinterpret_cast<uint8_t*>(&level), sizeof(uint8_t));
}

void BleBatteryLib::sendBatteryLevel(uint8_t level)
{
    setBatteryLevel(level);
    _levelCharacteristic->notify();
}

BleBatteryLib ArduinoBleBattery{};
#endif