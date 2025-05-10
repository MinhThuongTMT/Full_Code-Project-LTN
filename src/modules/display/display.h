#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

void displayHome();
void displayMenu();
void displayLockSystem();
void displayEnterPassword();
void displaySelectMode();
void displayMessage(String message);
void displayDeviceStatus(String status);
void displayMode();
void displaySetTimeMenu();
void displaySetTimeInput();
void displaySetCurrentTime();
void displayDeviceState();
void displaySetWaterLevel();
void displayAutoStatus();
#endif