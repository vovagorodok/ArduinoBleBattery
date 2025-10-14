#pragma once
#include <Arduino.h>

#ifdef BLE_BATTERY_LOGS
    #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
        #define BLE_BATTERY_PRINTF Serial.printf
    #else
        #define BLE_BATTERY_PRINTF printf
    #endif

    #define BLE_BATTERY_LOG(tag, fmt, ...) \
        BLE_BATTERY_PRINTF("DBG: BleBattery: " tag ": " fmt "\n", ##__VA_ARGS__)
#else
    #define BLE_BATTERY_LOG(fmt, ...) \
        do {} while (0)
#endif