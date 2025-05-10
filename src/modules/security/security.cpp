#include "security.h"
#include <Arduino.h>
#include "../display/display.h"

bool isSystemLocked = false;
String enteredPassword = "";
String requiredPassword = "";

void checkPassword() {
  if (enteredPassword == requiredPassword) {
    if (requiredPassword == "8888") {
      isSystemLocked = false;
      displayMessage("System Unlocked");
      Serial.println("System Unlocked");
    } else if (requiredPassword == "9999") {
      isSystemLocked = true;
      displayMessage("System Locked");
      Serial.println("System Locked");
    }
  } else {
    displayMessage("Wrong Password");
    Serial.println("Wrong Password");
    enteredPassword = "";
    displayEnterPassword();
  }
}