#include "BleBatteryLibESP32.h"
#ifdef BLE_BATTERY_BLE_LIB_ESP32

BleBatteryLib::BleBatteryLib():
    _service(),
    _levelCharacteristic(),
    _levelStatusCharacteristic()
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
    _service = server->createService(BLE_BATTERY_SERVICE_UUID);

    _levelCharacteristic = _service->createCharacteristic(
        BLE_BATTERY_CHARACTERISTIC_UUID_LEVEL,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    batteryService.begin();

    _service->start();
}

void BleBatteryLib::setBatteryLevel(uint8_t level)
{
    _levelCharacteristic->setValue(reinterpret_cast<uint8_t*>(&level), sizeof(uint8_t));
}

void BleBatteryLib::updateBatteryLevel(uint8_t level)
{
    setBatteryLevel(level);
    _levelCharacteristic->notify();
}

void BleBatteryLib::setBatteryLevelStatus(const BleBatteryLevelStatus& status)
{
    _levelStatusCharacteristic = _service->createCharacteristic(
        BLE_BATTERY_CHARACTERISTIC_UUID_LEVEL_STATUS,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    _levelStatusCharacteristic->setValue((uint8_t*)(&status), sizeof(BleBatteryLevelStatus));
}

void BleBatteryLib::updateBatteryLevelStatus(const BleBatteryLevelStatus& status)
{
    _levelStatusCharacteristic->setValue((uint8_t*)(&status), sizeof(BleBatteryLevelStatus));
    _levelStatusCharacteristic->notify();
}

BleBatteryLib ArduinoBleBattery{};
#endif