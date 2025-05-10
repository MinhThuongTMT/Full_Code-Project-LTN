#ifndef TIME_MANAGEMENT_H
#define TIME_MANAGEMENT_H
#include <Arduino.h>

struct DeviceTime {
  int onHour;
  int onMinute;
  int offHour;
  int offMinute;
};

extern DeviceTime denTime;
extern DeviceTime quatTime;
extern DeviceTime mayBomTime;
extern unsigned long timeSetMillis;
extern long currentTimeSeconds;

long getCurrentTimeSeconds();
void controlDevicesByTime();
String getDeviceStateString(DeviceTime deviceTime, long currentSeconds);

#endif