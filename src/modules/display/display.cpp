#include "display.h"
#include <Wire.h>
#include <Arduino.h>
#include "../modes/modes.h"
#include "../time_management/time_management.h"
#include "../keypad/keypad.h"
#include "../actuators/actuators.h"  

LiquidCrystal_I2C lcd(0x27, 20, 4);

void displayHome() {
  lcd.clear();
  lcd.setCursor(7, 0);
  lcd.print("PTIT");
  lcd.setCursor(2, 1);
  lcd.print("TRAN MINH THUONG");
  lcd.setCursor(5, 2);
  lcd.print("N21DCVT101");
  lcd.setCursor(3, 3);
  lcd.print("- SMART HOME -");
}

void displayMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1. Chon che do");
  lcd.setCursor(0, 1);
  lcd.print("2. Khoa he thong");
  lcd.setCursor(0, 2);
  lcd.print("3. Cai dat muc nuoc");
  lcd.setCursor(0, 3);
  lcd.print("4. Thoat");
}

void displayLockSystem() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vui long chon:");
  lcd.setCursor(0, 1);
  lcd.print("1. Mo he thong");
  lcd.setCursor(0, 2);
  lcd.print("2. Khoa he thong");
}

void displayEnterPassword() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nhap mat khau:");
  lcd.setCursor(0, 1);
  String displayPassword = "";
  extern String enteredPassword;
  for (size_t i = 0; i < enteredPassword.length(); i++) {
    displayPassword += "*";
  }
  lcd.print(displayPassword);
}

void displaySelectMode() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nhap ma che do:");
  lcd.setCursor(0, 1);
  String displayPassword = "";
  extern String enteredPassword;
  for (size_t i = 0; i < enteredPassword.length(); i++) {
    displayPassword += "*";
  }
  lcd.print(displayPassword);
}

void displayMessage(String message) {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(message);
  delay(2000);
}

void displayDeviceStatus(String status) {
  lcd.setCursor(6, 2);
  lcd.print("                    ");
  lcd.setCursor(6, 2);
  lcd.print(status);
  delay(2000);
  lcd.setCursor(6, 2);
  lcd.print("                    ");
}

void displayMode() {
  lcd.clear();
  String modeText;
  extern Mode currentMode;
  switch (currentMode) {
    case MANUAL:
      modeText = "Mode: Manual";
      break;
    case AUTO:
      modeText = "Mode: Auto";
      displayAutoStatus(); // Hiển thị trạng thái thiết bị ngay lập tức
      return; // Thoát hàm để không ghi đè lcd.clear()
    case SETTING_TIME:
      modeText = "Mode: Set Time";
      break;
  }
  int padding = (20 - modeText.length()) / 2;
  lcd.setCursor(padding, 0);
  lcd.print(modeText);
}

void displaySetTimeMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Chon thiet bi");
  lcd.setCursor(0, 1);
  lcd.print("1. Den");
  lcd.setCursor(0, 2);
  lcd.print("2. Quat");
  lcd.setCursor(0, 3);
  lcd.print("3. May bom nuoc");
}

void displaySetTimeInput() {
  lcd.clear();
  extern int selectedDevice;
  extern int inputPhase;
  extern String timeInput;
  extern int onHour, onMinute, offHour, offMinute;
  String deviceName;
  if (selectedDevice == 1) deviceName = "Den";
  else if (selectedDevice == 2) deviceName = "Quat";
  else if (selectedDevice == 3) deviceName = "May bom nuoc";
  lcd.setCursor(0, 0);
  lcd.print("Thiet bi: " + deviceName);

  if (inputPhase == 0) {
    String onStr = timeInput;
    while (onStr.length() < 4) onStr += " ";
    onStr = onStr.substring(0, 2) + ":" + onStr.substring(2, 4);
    lcd.setCursor(0, 1);
    lcd.print("Bat: " + onStr);
    lcd.setCursor(0, 2);
    lcd.print("Tat: ");
  } else if (inputPhase == 1) {
    String onStr = String(onHour / 10) + String(onHour % 10) + ":" + 
                   String(onMinute / 10) + String(onMinute % 10);
    lcd.setCursor(0, 1);
    lcd.print("Bat: " + onStr);
    String offStr = timeInput;
    while (offStr.length() < 4) offStr += " ";
    offStr = offStr.substring(0, 2) + ":" + offStr.substring(2, 4);
    lcd.setCursor(0, 2);
    lcd.print("Tat: " + offStr);
  }
}

void displaySetCurrentTime() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cai dat thoi gian");
  lcd.setCursor(0, 1);
  extern String currentTimeInput;
  extern int currentInputPhase;
  String timeStr = currentTimeInput;
  if (currentInputPhase == 0) {
    while (timeStr.length() < 2) timeStr += " ";
    lcd.print("Gio: " + timeStr);
    lcd.setCursor(0, 2);
    lcd.print("Phut: ");
  } else if (currentInputPhase == 1) {
    lcd.print("Gio: " + String(currentTimeInput.substring(0, 2)));
    lcd.setCursor(0, 2);
    while (timeStr.length() < 4) timeStr += " ";
    lcd.print("Phut: " + timeStr.substring(2));
  }
}

void displayDeviceState() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("  Mode: Set time   ");

  long currentSeconds = getCurrentTimeSeconds();
  if (currentSeconds == -1) {
    lcd.setCursor(0, 1);
    lcd.print("Time not set");
    return;
  }

  unsigned long lastUpdateTime = millis();
  const unsigned long updateInterval = 1000;

  while (true) {
    if (millis() - lastUpdateTime >= updateInterval) {
      lastUpdateTime = millis();
      currentSeconds = getCurrentTimeSeconds();
      controlDevicesByTime();

      lcd.setCursor(0, 1);
      lcd.print("Den: ");
      extern DeviceTime denTime;
      if (denTime.onHour != -1) {
        String status = getDeviceStateString(denTime, currentSeconds);
        lcd.print(status + "    ");
      } else {
        lcd.print("Not set    ");
      }

      lcd.setCursor(0, 2);
      lcd.print("Quat: ");
      extern DeviceTime quatTime;
      if (quatTime.onHour != -1) {
        String status = getDeviceStateString(quatTime, currentSeconds);
        lcd.print(status + "    ");
      } else {
        lcd.print("Not set    ");
      }

      lcd.setCursor(0, 3);
      lcd.print("May bom nuoc:");
      extern DeviceTime mayBomTime;
      if (mayBomTime.onHour != -1) {
        String status = getDeviceStateString(mayBomTime, currentSeconds);
        lcd.print(status + "    ");
      } else {
        lcd.print("Not set    ");
      }
    }

    char key = scanKeypad();
    if (key == '*') {
      extern ScreenState currentScreen;
      currentScreen = HOME;
      displayHome();
      extern unsigned long lastKeypadDebounceTime;
      lastKeypadDebounceTime = millis();
      break;
    }
  }
}
// Hiển thị hàm cài đặt mực nước
void displaySetWaterLevel() {
  lcd.clear();
  lcd.setCursor(0, 0);
  extern int waterLevelPhase;  // Truy cập biến toàn cục từ main.cpp
  if (waterLevelPhase == 0) {
    lcd.print("Nhap muc nuoc bat:");
  } else if (waterLevelPhase == 1) {
    lcd.print("Nhap muc nuoc tat:");
  }
  lcd.setCursor(0, 1);
  extern String waterLevelInput;  // Truy cập biến toàn cục từ main.cpp
  lcd.print(waterLevelInput);
}
// Hiển thi trạng thái thiết bị ở chế độ Auto
void displayAutoStatus() {
  lcd.setCursor(5, 0);
  lcd.print("Mode: Auto");
  lcd.setCursor(0, 1);
  lcd.print("Quat: ON "); // Quạt luôn bật trong chế độ Auto
  lcd.setCursor(0, 2);
  lcd.print("Den: ");
  lcd.print(digitalRead(LED_PIN) ? "ON " : "OFF"); // Trạng thái đèn
  lcd.setCursor(0, 3);
  lcd.print("May bom nuoc: ");
  lcd.print(digitalRead(RELAY_PIN) == LOW ? "ON " : "OFF"); // Trạng thái máy bơm (LOW = ON)
}