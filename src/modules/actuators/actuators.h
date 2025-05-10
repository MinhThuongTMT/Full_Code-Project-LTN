#ifndef ACTUATORS_H
#define ACTUATORS_H

#define LED_PIN PG14
#define LED_1 PB6
#define LED_2 PB2
#define RELAY_PIN PF2
#define RELAY_FAN PE6

void controlLED(bool state);
void controlPump(bool state);
void controlFan(bool state);

#endif