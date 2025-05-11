#ifndef SENSORS_H
#define SENSORS_H

#define LIGHT_SENSOR PG9
#define TRIG_PIN PA6
#define ECHO_PIN PA7
#define PIR_PIN PA3          // Định nghĩa chân cho cảm biến PIR

// Thay #define bằng biến extern
extern int pumpOnDistance;  // Khoảng cách bật máy bơm (cm)
extern int pumpOffDistance; // Khoảng cách tắt máy bơm (cm)

float measureDistance();
int readLightSensor();
int readPIRSensor();        // Thêm hàm đọc cảm biến PIR

#endif