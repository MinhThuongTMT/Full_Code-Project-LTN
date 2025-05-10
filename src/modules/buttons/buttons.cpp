#include "buttons.h"
#include <Arduino.h>
#include "../utils/utils.h"
#include "../modes/modes.h"
#include "../display/display.h"

int lastManualState = HIGH;
int lastAutoState = HIGH;
int lastSettingState = HIGH;
int lastLedButtonState = HIGH;
int lastRelayOnState = HIGH;
int lastRelayOffState = HIGH;

void handleButton(int buttonPin, int &lastState, int relayPin, int ledOnPin, int ledOffPin, String deviceName) {
  int buttonState = digitalRead(buttonPin);
  extern unsigned long lastDebounceTime;
  extern const unsigned long debounceDelay;
  extern bool isSystemLocked;
  extern Mode currentMode;
  if (buttonState != lastState && millis() - lastDebounceTime > debounceDelay) {
    if (!isSystemLocked && currentMode == MANUAL) {
      if (buttonState == LOW) {
        bool currentRelayState = digitalRead(relayPin);
        digitalWrite(relayPin, !currentRelayState);
        if (digitalRead(relayPin) == LOW) {
          digitalWrite(ledOnPin, HIGH);
          digitalWrite(ledOffPin, LOW);
          Serial.println(deviceName + " ON, LED ON, LED OFF");
          displayDeviceStatus("Bat " + deviceName);
        } else {
          digitalWrite(ledOnPin, LOW);
          digitalWrite(ledOffPin, HIGH);
          Serial.println(deviceName + " OFF, LED OFF, LED ON");
          displayDeviceStatus("Tat " + deviceName);
        }
      }
    } else {
      Serial.println(deviceName + " Button ignored: System is locked or not in Manual mode");
    }
    lastDebounceTime = millis();
  }
  lastState = buttonState;
}