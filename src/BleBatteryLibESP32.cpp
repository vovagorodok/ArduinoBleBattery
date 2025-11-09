#include "BleBatteryLibESP32.h"
#ifdef BLE_BATTERY_BLE_LIB_ESP32

BleBatteryLib::BleBatteryLib():
    _service(),
    _levelCharacteristic(),
    _levelStatusCharacteristic(),
    _timeStatusCharacteristic(),
    _criticalStatusCharacteristic()
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
    batteryService.handleServiceCreate();

    _service->start();
}

void BleBatteryLib::setBatteryLevel(BleBatteryLevel level)
{
    _levelCharacteristic->setValue(reinterpret_cast<uint8_t*>(&level), sizeof(BleBatteryLevel));
}

void BleBatteryLib::updateBatteryLevel(BleBatteryLevel level)
{
    setBatteryLevel(level);
    _levelCharacteristic->notify();
}

void BleBatteryLib::createBatteryLevelStatus(const BleBatteryLevelStatus& status)
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

void BleBatteryLib::createBatteryTimeStatus(const BleBatteryTimeStatus& status)
{
    _timeStatusCharacteristic = _service->createCharacteristic(
        BLE_BATTERY_CHARACTERISTIC_UUID_TIME_STATUS,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    _timeStatusCharacteristic->setValue((uint8_t*)(&status), sizeof(BleBatteryTimeStatus));
}

void BleBatteryLib::updateBatteryTimeStatus(const BleBatteryTimeStatus& status)
{
    _timeStatusCharacteristic->setValue((uint8_t*)(&status), sizeof(BleBatteryTimeStatus));
    _timeStatusCharacteristic->notify();
}

void BleBatteryLib::createBatteryCriticalStatus(const BleBatteryCriticalStatus& status)
{
    _criticalStatusCharacteristic = _service->createCharacteristic(
        BLE_BATTERY_CHARACTERISTIC_UUID_CRITICAL_STATUS,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    _criticalStatusCharacteristic->setValue((uint8_t*)(&status), sizeof(BleBatteryCriticalStatus));
}

void BleBatteryLib::updateBatteryCriticalStatus(const BleBatteryCriticalStatus& status)
{
    _criticalStatusCharacteristic->setValue((uint8_t*)(&status), sizeof(BleBatteryCriticalStatus));
    _criticalStatusCharacteristic->notify();
}

BleBatteryLib ArduinoBleBattery{};
#endif