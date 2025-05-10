#ifndef ACTUATORS_H
#define ACTUATORS_H

#define LED_PIN PG14
#define LED_1 PB6             // LED 1 (xanh)
#define LED_2 PB2             // LED 2 (đỏ)
#define LED_3 PD15             // LED 3 (xanh)
#define LED_4 PF12             // LED 4 (đỏ)
#define RELAY_PIN PF2
#define RELAY_FAN PE6

void controlLED(bool state);
void controlPump(bool state);
void controlFan(bool state);

#endif