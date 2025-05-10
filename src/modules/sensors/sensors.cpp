#include "sensors.h"
#include <Arduino.h>

// Khai báo biến toàn cục
int pumpOnDistance = 20;  // Giá trị mặc định: 20 cm
int pumpOffDistance = 10; // Giá trị mặc định: 10 cm

float measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration / 2.0) * 0.0343;
  return distance;
}

int readLightSensor() {
  return digitalRead(LIGHT_SENSOR);
}