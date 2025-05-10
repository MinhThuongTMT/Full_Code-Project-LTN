#ifndef BUTTONS_H
#define BUTTONS_H
#include <Arduino.h>

#define BUTTON_LED PF13
#define BUTTON_MANUAL PE9
#define BUTTON_AUTO PE11
#define BUTTON_SETTING PF14
#define BUTTON_RELAY_ON PE13
#define BUTTON_RELAY_OFF PF15

extern int lastManualState;
extern int lastAutoState;
extern int lastSettingState;
extern int lastLedButtonState;
extern int lastRelayOnState;
extern int lastRelayOffState;

void handleButton(int buttonPin, int &lastState, int relayPin, int ledOnPin, int ledOffPin, String deviceName);

#endif