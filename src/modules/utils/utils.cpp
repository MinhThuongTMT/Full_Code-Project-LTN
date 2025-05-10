#include "utils.h"

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 100;
unsigned long lastKeypadDebounceTime = 0;
unsigned long lastDistanceMeasureTime = 0;
const unsigned long distanceMeasureInterval = 1000;