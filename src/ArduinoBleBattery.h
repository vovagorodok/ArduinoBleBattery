#pragma once
#include "BleBatteryDefines.h"
#if defined(BLE_BATTERY_BLE_LIB_ARDUINO_BLE)
#include "BleBatteryLibArduinoBle.h"
#elif defined(BLE_BATTERY_BLE_LIB_NIM_BLE_ARDUINO)
#include "BleBatteryLibNimBleArduino.h"
#elif defined(BLE_BATTERY_BLE_LIB_ESP32)
#include "BleBatteryLibESP32.h"
#else
#error "Unsupported BLE library."
#endif