#include<Arduino.h>

uint8_t numSensor = 8;  // จำนวนเซ็นเซอร์
uint16_t sensor_pin[] = {A0, A1 ,A2 ,A3, A4, A5, A6,A7};
uint16_t min_sensor_values[] = {145, 252, 126, 142 ,145, 252, 126, 142};
uint16_t max_sensor_values[] = {976, 978, 975, 975 ,976, 978, 975, 975};

void setup() {
  seekersetup();
  wait_sw();
//   calibratesensorminmax();
}

void loop() {
    TL(30,1,0);
}
