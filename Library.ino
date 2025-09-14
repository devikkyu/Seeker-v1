#define pwmA 3
#define in1A 4
#define in2A 5

#define pwmB 6
#define in1B 7
#define in2B 8

#define SW 12

void motor(int channel, int pwm) {

    pwm = map(pwm, 0, 100, 0, 255);

    if(channel==1 && pwm >= 0){
        digitalWrite(in1A, HIGH);
        digitalWrite(in2A, LOW);
    } else{
        digitalWrite(in1A, LOW);
        digitalWrite(in2A, HIGH);
        pwm=pwm*(-1);
    }
    analogWrite(pwmA, pwm);

    if(channel==2 && pwm >= 0){
        digitalWrite(in1B, HIGH);
        digitalWrite(in2B, LOW);   
    } else {
        
        digitalWrite(in1B, LOW);
        digitalWrite(in2B, HIGH);
        pwm = pwm * (-1);
    }
    analogWrite(pwmB, pwm);
}

void seekersetup() {
    Serial.begin(9600);
    pinMode(in1A, OUTPUT);
    pinMode(in2A, OUTPUT);
    pinMode(in1B, OUTPUT);
    pinMode(in2B, OUTPUT);
    pinMode(SW, INPUT_PULLUP);
    TCCR2B = TCCR2B & B11111000 | B00000011;
    TCCR0B = TCCR0B & B11111000 | B00000011;
}

void wait_sw() {
    while (digitalRead(SW) == HIGH) delay(10);
    delay(50);
    while (digitalRead(SW) == LOW) delay(10);
}

void fd(int pwm) {
    if (pwm > 0) {
        motor(1, pwm);
        motor(2, pwm);
    } else {
        motor(1, 0);
        motor(2, 0);
    }
}

void bk(int pwm) {
    if (pwm > 0) {
        motor(1, -pwm);
        motor(2, -pwm);
    } else {
        motor(1, 0);
        motor(2, 0);
    }
}

void sr(int pwm) {
    if (pwm > 0) {
        motor(1, pwm);
        motor(2, -pwm);
    } else {
        motor(1, 0);
        motor(2, 0);
    }
}

void sl(int pwm) {
    if (pwm > 0) {
        motor(1, -pwm);
        motor(2, pwm);
    } else {
        motor(1, 0);
        motor(2, 0);
    }
}

void ao() {
    motor(1,0);
    motor(2,0);
}

void testmotor() {
    motor(1, 100);
    motor(2, 100);
    delay(1000);
    motor(1, -100);
    motor(2, -100);   
    delay(1000);
    motor(1, -100);
    motor(2, 100);  
    delay(1000);
    motor(1, 100);
    motor(2, -100);  
    delay(1000);
    motor(1, 0);
    motor(2, 0);  
}

void calibratesensor() {
    uint16_t tempMin[numSensor], tempMax[numSensor];
    for (int i = 0; i < numSensor; i++) {
      tempMin[i] = 1023;
      tempMax[i] = 0;
    }
    for (uint16_t i = 0; i < 400; i++) {
      for (int channel = 0; channel < numSensor; channel++) {
        int sensorValue = analogRead(sensor_pin[channel]);
        if (sensorValue < tempMin[channel]) tempMin[channel] = sensorValue;
        if (sensorValue > tempMax[channel]) tempMax[channel] = sensorValue;
      }
      Serial.println(i);
      delay(10);
    }
    Serial.print("const uint16_t Min[] = {");
    for (uint8_t i = 0; i < numSensor; i++) {
      Serial.print(tempMin[i]);
      if (i < numSensor-1) Serial.print(", ");
    }
    Serial.print("};");
    Serial.println();
    Serial.print("const uint16_t Max[] = {");
    for (uint8_t i = 0; i < numSensor; i++) {
      Serial.print(tempMax[i]);
      if (i < numSensor-1) Serial.print(", ");
    }
    Serial.print("};");
    Serial.println();
}