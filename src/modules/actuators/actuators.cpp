#include "actuators.h"
#include <Arduino.h>

void controlLED(bool state) {
  digitalWrite(LED_PIN, state ? HIGH : LOW);
}

void controlPump(bool state) {
  digitalWrite(RELAY_PIN, state ? LOW : HIGH);
  digitalWrite(LED_1, state ? HIGH : LOW);
  digitalWrite(LED_2, state ? LOW : HIGH);
}

void controlFan(bool state) {
  digitalWrite(RELAY_FAN, state ? LOW : HIGH);
  digitalWrite(LED_1, state ? HIGH : LOW);
  digitalWrite(LED_2, state ? LOW : HIGH);
}