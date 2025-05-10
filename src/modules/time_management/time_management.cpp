#include "time_management.h"
#include <Arduino.h>
#include "../actuators/actuators.h"

DeviceTime denTime = {-1, -1, -1, -1};
DeviceTime quatTime = {-1, -1, -1, -1};
DeviceTime mayBomTime = {-1, -1, -1, -1};
unsigned long timeSetMillis = 0;
long currentTimeSeconds = -1;

long getCurrentTimeSeconds() {
  if (currentTimeSeconds == -1) return -1;
  unsigned long elapsedMillis = millis() - timeSetMillis;
  long elapsedSeconds = elapsedMillis / 1000;
  long totalSeconds = currentTimeSeconds + elapsedSeconds;
  long currentDaySeconds = totalSeconds % 86400;
  Serial.print("Current time (seconds): ");
  Serial.print(currentDaySeconds);
  Serial.print(" (");
  Serial.print(currentDaySeconds / 3600);
  Serial.print(":");
  Serial.print((currentDaySeconds % 3600) / 60);
  Serial.println(")");
  return currentDaySeconds;
}

void controlDevicesByTime() {
  if (currentTimeSeconds == -1) {
    Serial.println("Time not set, skipping device control");
    return;
  }

  long currentSeconds = getCurrentTimeSeconds();
  if (currentSeconds == -1) return;

  if (denTime.onHour != -1) {
    long onSeconds = denTime.onHour * 3600 + denTime.onMinute * 60;
    long offSeconds = denTime.offHour * 3600 + denTime.offMinute * 60;
    bool shouldBeOn = (onSeconds <= offSeconds) ? 
                      (currentSeconds >= onSeconds && currentSeconds < offSeconds) :
                      (currentSeconds >= onSeconds || currentSeconds < offSeconds);
    controlLED(shouldBeOn);
    Serial.println(shouldBeOn ? "Den ON" : "Den OFF");
  }

  if (quatTime.onHour != -1) {
    long onSeconds = quatTime.onHour * 3600 + quatTime.onMinute * 60;
    long offSeconds = quatTime.offHour * 3600 + quatTime.offMinute * 60;
    bool shouldBeOn = (onSeconds <= offSeconds) ? 
                      (currentSeconds >= onSeconds && currentSeconds < offSeconds) :
                      (currentSeconds >= onSeconds || currentSeconds < offSeconds);
    controlFan(shouldBeOn);
    Serial.println(shouldBeOn ? "Quat ON" : "Quat OFF");
  }

  if (mayBomTime.onHour != -1) {
    long onSeconds = mayBomTime.onHour * 3600 + mayBomTime.onMinute * 60;
    long offSeconds = mayBomTime.offHour * 3600 + mayBomTime.offMinute * 60;
    bool shouldBeOn = (onSeconds <= offSeconds) ? 
                      (currentSeconds >= onSeconds && currentSeconds < offSeconds) :
                      (currentSeconds >= onSeconds || currentSeconds < offSeconds);
    controlPump(shouldBeOn);
    Serial.println(shouldBeOn ? "May bom ON" : "May bom OFF");
  }
}

String getDeviceStateString(DeviceTime deviceTime, long currentSeconds) {
  if (deviceTime.onHour == -1 || deviceTime.offHour == -1) {
    return "Not set";
  }
  long onSeconds = deviceTime.onHour * 3600 + deviceTime.onMinute * 60;
  long offSeconds = deviceTime.offHour * 3600 + deviceTime.offMinute * 60;
  bool shouldBeOn = (onSeconds <= offSeconds) ? 
                    (currentSeconds >= onSeconds && currentSeconds < offSeconds) :
                    (currentSeconds >= onSeconds || currentSeconds < offSeconds);
  return shouldBeOn ? "ON" : "OFF";
}