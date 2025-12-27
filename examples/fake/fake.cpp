#ifndef ARDUINO
#include <ArduinoBleBattery.h>

BleBatteryService batteryService{};

int main() {
  ArduinoBleBattery.begin("Arduino Ble Battery", batteryService);
  return 0;
}
#endif