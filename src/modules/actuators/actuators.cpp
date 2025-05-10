#include "actuators.h"
#include <Arduino.h>

void controlLED(bool state) {
  digitalWrite(LED_PIN, state ? HIGH : LOW);
}

void controlPump(bool state) {
  digitalWrite(RELAY_PIN, state ? LOW : HIGH); // Relay bật khi LOW
  digitalWrite(LED_1, state ? HIGH : LOW);     // LED 1 (xanh) sáng khi bật
  digitalWrite(LED_2, state ? LOW : HIGH);     // LED 2 (đỏ) sáng khi tắt
}

void controlFan(bool state) {
  digitalWrite(RELAY_FAN, state ? LOW : HIGH); // Relay bật khi LOW
  digitalWrite(LED_3, state ? HIGH : LOW);     // LED 3 (xanh) sáng khi bật
  digitalWrite(LED_4, state ? LOW : HIGH);     // LED 4 (đỏ) sáng khi tắt
}