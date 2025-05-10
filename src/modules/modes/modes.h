#ifndef MODES_H
#define MODES_H

enum Mode {
  MANUAL,
  AUTO,
  SETTING_TIME
};

enum ScreenState {
  HOME,
  MENU,
  LOCK_SYSTEM,
  ENTER_PASSWORD,
  SELECT_MODE,
  SET_TIME_MENU,
  SET_TIME_INPUT,
  SET_CURRENT_TIME,
  DEVICE_STATE,
  SET_WATER_LEVEL,
  AUTO_STATUS
};

extern Mode currentMode;
extern ScreenState currentScreen;

#endif