#ifndef SECURITY_H
#define SECURITY_H
#include <Arduino.h>

extern bool isSystemLocked;
extern String enteredPassword;
extern String requiredPassword;

void checkPassword();

#endif