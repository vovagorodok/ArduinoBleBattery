#include "BleBatteryLibNimBleArduino.h"
#ifdef BLE_BATTERY_BLE_LIB_NIM_BLE_ARDUINO

BleBatteryLib::BleBatteryLib():
    _service(),
    _levelCharacteristic(),
    _levelStatusCharacteristic()
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
    _service = server->createService(BLE_BATTERY_SERVICE_UUID);
    _levelCharacteristic = _service->createCharacteristic(
        BLE_BATTERY_CHARACTERISTIC_UUID_LEVEL,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY,
        sizeof(BleBatteryLevel)
    );
    batteryService.begin();

    return _service->start();
}

void BleBatteryLib::setBatteryLevel(BleBatteryLevel level)
{
    _levelCharacteristic->setValue(reinterpret_cast<const uint8_t*>(&level), sizeof(BleBatteryLevel));
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
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY,
        sizeof(BleBatteryLevelStatus)
    );
    _levelStatusCharacteristic->setValue(reinterpret_cast<const uint8_t*>(&status), sizeof(BleBatteryLevelStatus));
}

void BleBatteryLib::updateBatteryLevelStatus(const BleBatteryLevelStatus& status)
{
    _levelStatusCharacteristic->setValue(reinterpret_cast<const uint8_t*>(&status), sizeof(BleBatteryLevelStatus));
    _levelStatusCharacteristic->notify();
}

BleBatteryLib ArduinoBleBattery{};
#endif