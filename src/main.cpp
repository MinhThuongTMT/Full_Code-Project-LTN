#include <Arduino.h>
#include "modules/display/display.h"
#include "modules/keypad/keypad.h"
#include "modules/buttons/buttons.h"
#include "modules/sensors/sensors.h"
#include "modules/actuators/actuators.h"
#include "modules/modes/modes.h"
#include "modules/time_management/time_management.h"
#include "modules/security/security.h"
#include "modules/utils/utils.h"

// **Khai báo biến toàn cục**
int selectedDevice = 0;           // Thiết bị được chọn để cài đặt thời gian
int inputPhase = 0;               // Giai đoạn nhập thời gian (0: giờ bật, 1: giờ tắt)
String timeInput = "";            // Chuỗi nhập thời gian từ keypad
int onHour = -1, onMinute = -1;   // Thời gian bật
int offHour = -1, offMinute = -1; // Thời gian tắt
String currentTimeInput = "";     // Chuỗi nhập thời gian hiện tại
int currentInputPhase = 0;        // Giai đoạn nhập thời gian hiện tại

// **Biến cho chức năng cài đặt mực nước**
String waterLevelInput = ""; // Chuỗi nhập mực nước từ keypad
int waterLevelPhase = 0;     // Giai đoạn: 0 = mức bật, 1 = mức tắt
int tempOnDistance = 0;      // Biến tạm lưu khoảng cách bật

void setup()
{
  // **Khởi tạo giao tiếp và màn hình**
  Serial.begin(115200);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  displayHome();

  // **Cấu hình các chân nút nhấn**
  pinMode(BUTTON_MANUAL, INPUT_PULLUP);
  pinMode(BUTTON_AUTO, INPUT_PULLUP);
  pinMode(BUTTON_SETTING, INPUT_PULLUP);
  pinMode(BUTTON_LED, INPUT_PULLUP);
  pinMode(BUTTON_RELAY_ON, INPUT_PULLUP);
  pinMode(BUTTON_RELAY_OFF, INPUT_PULLUP);

  // **Cấu hình các chân đầu ra**
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_1, OUTPUT); // LED_1 cho máy bơm
  pinMode(LED_2, OUTPUT); // LED_2 cho máy bơm
  pinMode(LED_3, OUTPUT); // LED_3 cho quạt
  pinMode(LED_4, OUTPUT); // LED_4 cho quạt
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW); // Tắt LED_3 ban đầu
  digitalWrite(LED_4, LOW); // Tắt LED_4 ban đầu
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(RELAY_FAN, HIGH);

  // **Cấu hình cảm biến**
  pinMode(LIGHT_SENSOR, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // **Cấu hình bàn phím keypad**
  for (int i = 0; i < KEYPAD_NUMBER_OF_ROWS; i++)
  {
    pinMode(keypadRowPins[i], OUTPUT);
    digitalWrite(keypadRowPins[i], HIGH);
  }
  for (int i = 0; i < KEYPAD_NUMBER_OF_COLS; i++)
  {
    pinMode(keypadColPins[i], INPUT_PULLUP);
  }
}

void loop()
{
  // **Đọc trạng thái các nút nhấn**
  int manualState = digitalRead(BUTTON_MANUAL);
  int autoState = digitalRead(BUTTON_AUTO);
  int settingState = digitalRead(BUTTON_SETTING);
  int ledButtonState = digitalRead(BUTTON_LED);
  int relayOnState = digitalRead(BUTTON_RELAY_ON);
  int relayOffState = digitalRead(BUTTON_RELAY_OFF);

  // **Xử lý nút chuyển chế độ thủ công**
  if (manualState != lastManualState && millis() - lastDebounceTime > debounceDelay)
  {
    if (!isSystemLocked && manualState == LOW)
    {
      currentMode = MANUAL;
      currentScreen = HOME;
      digitalWrite(LED_PIN, LOW);
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, LOW);
      digitalWrite(RELAY_PIN, HIGH);
      digitalWrite(RELAY_FAN, HIGH);
      displayMode();
      Serial.println("Switched to Manual");
    }
    lastDebounceTime = millis();
  }
  lastManualState = manualState;

  // **Xử lý nút chuyển chế độ tự động**
  if (autoState != lastAutoState && millis() - lastDebounceTime > debounceDelay)
  {
    if (!isSystemLocked && autoState == LOW)
    {
      currentMode = AUTO;
      currentScreen = AUTO_STATUS;
      digitalWrite(LED_PIN, LOW);
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, LOW);
      digitalWrite(RELAY_PIN, HIGH);
      digitalWrite(RELAY_FAN, HIGH);
      displayMode();
      Serial.println("Switched to Auto");
    }
    lastDebounceTime = millis();
  }
  lastAutoState = autoState;

  // **Xử lý nút chuyển chế độ cài đặt thời gian**
  if (settingState != lastSettingState && millis() - lastDebounceTime > debounceDelay)
  {
    if (!isSystemLocked && settingState == LOW)
    {
      currentMode = SETTING_TIME;
      currentScreen = SET_TIME_MENU;
      digitalWrite(LED_PIN, LOW);
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, LOW);
      digitalWrite(RELAY_PIN, HIGH);
      digitalWrite(RELAY_FAN, HIGH);
      displayMode();
      delay(1000);
      displaySetTimeMenu();
      Serial.println("Switched to Set Time");
    }
    lastDebounceTime = millis();
  }
  lastSettingState = settingState;

  // **Xử lý nút bật/tắt LED trong chế độ thủ công**
  if (ledButtonState != lastLedButtonState && millis() - lastDebounceTime > debounceDelay)
  {
    if (!isSystemLocked && currentMode == MANUAL && ledButtonState == LOW)
    {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      displayDeviceStatus(digitalRead(LED_PIN) ? "Bat den" : "Tat den");
      Serial.println(digitalRead(LED_PIN) ? "LED ON" : "LED OFF");
    }
    lastDebounceTime = millis();
  }
  lastLedButtonState = ledButtonState;

  // **Xử lý nút điều khiển relay**
  handleButton(BUTTON_RELAY_ON, lastRelayOnState, RELAY_PIN, LED_1, LED_2, "may bom");
  handleButton(BUTTON_RELAY_OFF, lastRelayOffState, RELAY_FAN, LED_3, LED_4, "quat");

  // **Xử lý nhập liệu từ keypad**
  if (millis() - lastKeypadDebounceTime > debounceDelay)
  {
    char key = scanKeypad();
    if (key != '\0')
    {
      // **Chế độ thủ công: Điều khiển thiết bị bằng phím**
      if (currentMode == MANUAL && !isSystemLocked)
      {
        if (key == 'A')
        {
          digitalWrite(LED_PIN, !digitalRead(LED_PIN));
          displayDeviceStatus(digitalRead(LED_PIN) ? "Bat den" : "Tat den");
          Serial.println(digitalRead(LED_PIN) ? "LED ON" : "LED OFF");
          lastKeypadDebounceTime = millis();
        }
        else if (key == 'B')
        {
          bool currentFanState = digitalRead(RELAY_FAN) == LOW; // LOW là ON
          controlFan(!currentFanState);                         // Đổi trạng thái quạt và LED
          displayDeviceStatus(!currentFanState ? "Bat quat" : "Tat quat");
          Serial.println(!currentFanState ? "Fan ON" : "Fan OFF");
          lastKeypadDebounceTime = millis();
        }
        else if (key == 'C')
        {
          bool currentPumpState = digitalRead(RELAY_PIN) == LOW; // LOW là ON
          controlPump(!currentPumpState);                        // Đổi trạng thái máy bơm và LED
          displayDeviceStatus(!currentPumpState ? "Bat may bom" : "Tat may bom");
          Serial.println(!currentPumpState ? "Pump ON" : "Pump OFF");
          lastKeypadDebounceTime = millis();
        }
      }

      // **Phím '*' để hiển thị menu**
      if ((currentMode == MANUAL || currentMode == AUTO) && key == '*')
      {
        lcd.clear(); // Xóa màn hình một lần duy nhất
        currentMode = MANUAL;
        currentScreen = MENU;
        // Tắt các thiết bị để đảm bảo trạng thái ban đầu
        digitalWrite(LED_PIN, LOW);
        digitalWrite(LED_1, LOW);
        digitalWrite(LED_2, LOW);
        digitalWrite(LED_3, LOW);
        digitalWrite(LED_4, LOW);
        digitalWrite(RELAY_PIN, HIGH);
        digitalWrite(RELAY_FAN, HIGH);
        displayMenu();
        lastKeypadDebounceTime = millis();
      }
      else if (currentMode == SETTING_TIME && key == 'A')
      {
        currentScreen = DEVICE_STATE;
        displayDeviceState();
        lastKeypadDebounceTime = millis();
      }
      else if (key == '*' && currentScreen == HOME)
      {
        currentScreen = MENU;
        displayMenu();
        lastKeypadDebounceTime = millis();
      }

      // **Xử lý menu chính**
      else if (key == '1' && currentScreen == MENU)
      {
        currentScreen = SELECT_MODE;
        enteredPassword = "";
        displaySelectMode();
        lastKeypadDebounceTime = millis();
      }
      else if (key == '2' && currentScreen == MENU)
      {
        currentScreen = LOCK_SYSTEM;
        displayLockSystem();
        lastKeypadDebounceTime = millis();
      }
      else if (key == '3' && currentScreen == MENU)
      {
        currentScreen = SET_WATER_LEVEL;
        waterLevelPhase = 0;
        waterLevelInput = "";
        displaySetWaterLevel();
        lastKeypadDebounceTime = millis();
      }
      else if (key == '4' && currentScreen == MENU)
      {
        currentScreen = HOME;
        displayHome();
        lastKeypadDebounceTime = millis();
      }

      // **Xử lý khóa hệ thống**
      else if (currentScreen == LOCK_SYSTEM)
      {
        if (key == '1')
        {
          currentScreen = ENTER_PASSWORD;
          requiredPassword = "8888";
          enteredPassword = "";
          displayEnterPassword();
          lastKeypadDebounceTime = millis();
        }
        else if (key == '2')
        {
          currentScreen = ENTER_PASSWORD;
          requiredPassword = "9999";
          enteredPassword = "";
          displayEnterPassword();
          lastKeypadDebounceTime = millis();
        }
      }
      else if (currentScreen == ENTER_PASSWORD)
      {
        if ((key >= '0' && key <= '9') && enteredPassword.length() < 4)
        {
          enteredPassword += key;
          displayEnterPassword();
        }
        else if (key == '#')
        {
          checkPassword();
          currentScreen = HOME;
          displayHome();
          lastKeypadDebounceTime = millis();
        }
      }

      // **Xử lý chọn chế độ**
      else if (currentScreen == SELECT_MODE)
      {
        if ((key >= '0' && key <= '9') && enteredPassword.length() < 4)
        {
          enteredPassword += key;
          displaySelectMode();
        }
        else if (key == 'D')
        {
          if (enteredPassword.length() > 0)
          {
            enteredPassword.remove(enteredPassword.length() - 1);
            displaySelectMode();
          }
        }
        else if (key == '#')
        {
          if (enteredPassword == "1111")
          {
            displayMessage("Mat khau dung");
            currentMode = MANUAL;
            currentScreen = HOME;
            digitalWrite(LED_PIN, LOW);
            digitalWrite(LED_1, LOW);
            digitalWrite(LED_2, LOW);
            digitalWrite(LED_3, LOW);
            digitalWrite(LED_4, LOW);
            digitalWrite(RELAY_PIN, HIGH);
            digitalWrite(RELAY_FAN, HIGH);
            displayMode();
            Serial.println("Switched to Manual");
          }
          else if (enteredPassword == "2222")
          {
            displayMessage("Mat khau dung");
            currentMode = AUTO;
            digitalWrite(LED_PIN, LOW);
            digitalWrite(LED_1, LOW);
            digitalWrite(LED_2, LOW);
            digitalWrite(LED_3, LOW);
            digitalWrite(LED_4, LOW);
            digitalWrite(RELAY_PIN, HIGH);
            digitalWrite(RELAY_FAN, HIGH);
            displayMode();
            Serial.println("Switched to Auto");
          }
          else if (enteredPassword == "3333")
          {
            displayMessage("Mat khau dung");
            currentMode = SETTING_TIME;
            currentScreen = SET_TIME_MENU;
            digitalWrite(LED_PIN, LOW);
            digitalWrite(LED_1, LOW);
            digitalWrite(LED_2, LOW);
            digitalWrite(LED_3, LOW);
            digitalWrite(LED_4, LOW);
            digitalWrite(RELAY_PIN, HIGH);
            digitalWrite(RELAY_FAN, HIGH);
            displaySetTimeMenu();
            Serial.println("Switched to Set Time");
          }
          else
          {
            displayMessage("Mat khau sai");
            enteredPassword = "";
            displaySelectMode();
          }
          lastKeypadDebounceTime = millis();
        }
      }

      // **Xử lý menu cài đặt thời gian**
      else if (currentScreen == SET_TIME_MENU)
      {
        if (key == '1' || key == '2' || key == '3')
        {
          selectedDevice = key - '0';
          inputPhase = 0;
          timeInput = "";
          onHour = -1;
          onMinute = -1;
          offHour = -1;
          offMinute = -1;
          currentScreen = SET_TIME_INPUT;
          displaySetTimeInput();
        }
        else if (key == '4')
        {
          currentScreen = SET_CURRENT_TIME;
          currentTimeInput = "";
          currentInputPhase = 0;
          displaySetCurrentTime();
        }
        else if (key == '*')
        {
          currentScreen = HOME;
          displayHome();
        }
      }

      // **Xử lý nhập thời gian bật/tắt**
      else if (currentScreen == SET_TIME_INPUT)
      {
        if (key >= '0' && key <= '9' && timeInput.length() < 4)
        {
          timeInput += key;
          displaySetTimeInput();
        }
        else if (key == 'C')
        {
          timeInput = "";
          if (inputPhase == 0)
          {
            onHour = -1;
            onMinute = -1;
          }
          else if (inputPhase == 1)
          {
            offHour = -1;
            offMinute = -1;
          }
          displaySetTimeInput();
        }
        else if (key == 'D')
        {
          if (timeInput.length() > 0)
          {
            timeInput.remove(timeInput.length() - 1);
            displaySetTimeInput();
          }
        }
        else if (key == '#' && timeInput.length() == 4)
        {
          int hh = timeInput.substring(0, 2).toInt();
          int mm = timeInput.substring(2, 4).toInt();
          if (hh >= 0 && hh <= 23 && mm >= 0 && mm <= 59)
          {
            if (inputPhase == 0)
            {
              onHour = hh;
              onMinute = mm;
              inputPhase = 1;
              timeInput = "";
              displaySetTimeInput();
            }
            else if (inputPhase == 1)
            {
              offHour = hh;
              offMinute = mm;
              if (selectedDevice == 1)
              {
                denTime.onHour = onHour;
                denTime.onMinute = onMinute;
                denTime.offHour = offHour;
                denTime.offMinute = offMinute;
              }
              else if (selectedDevice == 2)
              {
                quatTime.onHour = onHour;
                quatTime.onMinute = onMinute;
                quatTime.offHour = offHour;
                quatTime.offMinute = offMinute;
              }
              else if (selectedDevice == 3)
              {
                mayBomTime.onHour = onHour;
                mayBomTime.onMinute = onMinute;
                mayBomTime.offHour = offHour;
                mayBomTime.offMinute = offMinute;
              }
              displayMessage("Cai dat thanh cong");
              currentScreen = SET_TIME_MENU;
              displaySetTimeMenu();
            }
          }
          else
          {
            displayMessage("Cai dat loi");
            timeInput = "";
            displaySetTimeInput();
          }
        }
      }

      // **Xử lý cài đặt thời gian hiện tại**
      else if (currentScreen == SET_CURRENT_TIME)
      {
        if (key >= '0' && key <= '9')
        {
          if (currentInputPhase == 0 && currentTimeInput.length() < 2)
          {
            currentTimeInput += key;
            displaySetCurrentTime();
          }
          else if (currentInputPhase == 1 && currentTimeInput.length() < 4)
          {
            currentTimeInput += key;
            displaySetCurrentTime();
          }
        }
        else if (key == 'C')
        {
          currentTimeInput = "";
          currentInputPhase = 0;
          displaySetCurrentTime();
        }
        else if (key == 'D')
        {
          if (currentTimeInput.length() > 0)
          {
            currentTimeInput.remove(currentTimeInput.length() - 1);
            displaySetCurrentTime();
          }
        }
        else if (key == '#' && currentInputPhase == 0 && currentTimeInput.length() == 2)
        {
          int hh = currentTimeInput.toInt();
          if (hh >= 0 && hh <= 23)
          { // Sửa từ 12 thành 23 để hỗ trợ định dạng 24 giờ
            currentInputPhase = 1;
            displaySetCurrentTime();
          }
          else
          {
            displayMessage("Cai dat loi");
            currentTimeInput = "";
            currentInputPhase = 0;
            displaySetCurrentTime();
          }
        }
        else if (key == '#' && currentInputPhase == 1 && currentTimeInput.length() == 4)
        {
          int hh = currentTimeInput.substring(0, 2).toInt();
          int mm = currentTimeInput.substring(2, 4).toInt();
          if (mm >= 0 && mm <= 59)
          { // Sửa từ 60 thành 59
            currentTimeSeconds = hh * 3600 + mm * 60;
            timeSetMillis = millis();
            displayMessage("Cai dat thanh cong");
            currentScreen = SET_TIME_MENU;
            displaySetTimeMenu();
          }
          else
          {
            displayMessage("Cai dat loi");
            currentTimeInput = "";
            currentInputPhase = 0;
            displaySetCurrentTime();
          }
        }
      }

      // **Xử lý cài đặt mực nước**
      else if (currentScreen == SET_WATER_LEVEL)
      {
        if (key >= '0' && key <= '9')
        {
          waterLevelInput += key;
          displaySetWaterLevel();
        }
        else if (key == 'C')
        {
          waterLevelInput = "";
          displaySetWaterLevel();
        }
        else if (key == 'D')
        {
          if (waterLevelInput.length() > 0)
          {
            waterLevelInput.remove(waterLevelInput.length() - 1);
            displaySetWaterLevel();
          }
        }
        else if (key == '#')
        {
          if (waterLevelInput.length() > 0)
          {
            int value = waterLevelInput.toInt();
            if (waterLevelPhase == 0)
            {
              tempOnDistance = value;
              waterLevelPhase = 1;
              waterLevelInput = "";
              displaySetWaterLevel();
            }
            else if (waterLevelPhase == 1)
            {
              int tempOffDistance = value;
              if (tempOnDistance > tempOffDistance)
              {
                pumpOnDistance = tempOnDistance;
                pumpOffDistance = tempOffDistance;
                displayMessage("Cai dat thanh cong");
                currentScreen = MENU;
                displayMenu();
              }
              else
              {
                displayMessage("Loi: Muc bat <= muc tat");
                waterLevelInput = "";
                displaySetWaterLevel();
              }
            }
          }
        }
        else if (key == '*')
        {
          currentScreen = MENU;
          displayMenu();
          lastKeypadDebounceTime = millis();
        }
      }
    }
  }

  // **Logic chế độ tự động**
  if (currentMode == AUTO && !isSystemLocked)
  {
    // Luôn bật quạt trong chế độ Auto
    controlFan(true);

    // Điều khiển đèn dựa trên cảm biến ánh sáng
    int lightValue = readLightSensor();
    controlLED(lightValue == HIGH);

    // Điều khiển máy bơm dựa trên cảm biến khoảng cách
    if (millis() - lastDistanceMeasureTime > distanceMeasureInterval)
    {
      float distance = measureDistance();
      if (distance > pumpOnDistance)
      {
        controlPump(true);
      }
      else if (distance < pumpOffDistance)
      {
        controlPump(false);
      }
      lastDistanceMeasureTime = millis();
    }
    // Cập nhật và hiển thị trạng thái thiết bị
    displayAutoStatus(); // Gọi trực tiếp để đảm bảo cập nhật liên tục
  }

  // **Điều khiển thiết bị theo thời gian**
  if (currentMode == SETTING_TIME && !isSystemLocked && currentScreen == HOME)
  {
    controlDevicesByTime();
  }
}