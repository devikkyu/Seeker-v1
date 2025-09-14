uint16_t setpoint;
uint32_t _lastPosition;
uint16_t state_on_Line = 0;
float present_position;
float errors = 0;
float output = 0;
float integral ;
float derivative ;
float previous_error ;

int calposition() {               
    bool onLine = false;
    long avg = 0;
    long sum = 0;
    for (uint8_t i = 0; i < numSensor ; i++)
    {
      long value = map(analog(sensor_pin[i]), min_sensor_values[i], max_sensor_values[i], 1000, 0);                                                                   
      if (value > 200) {        
        onLine = true;
      }
      if (value > 50)           
      {
        avg += (long)value * (i * 1000);   
        sum += value;                          
      }
    }
    if (!onLine)    
    {
      if (_lastPosition < (numSensor - 1) * 1000 / 2) 
      {
        return 0;
      }
      else                                          
      {
        return (numSensor - 1) * 1000;
      }
    }
    _lastPosition = avg / sum;        
    return _lastPosition;           
  }

  void TL(int avgspeed , float Kp , float Kd) {

    int Ki = 0;
    present_position = calposition() / ((numSensor - 1) * 10) ;
    setpoint = 50.0;
    errors = setpoint - present_position;
    integral = integral + errors ;
    derivative = (errors - previous_error) ;
    output = Kp * errors + Ki * integral + Kd * derivative;
    motor(1, constrain(avgspeed + output,-100,100));
    motor(2, constrain(avgspeed - output,-100,100));
    previous_error = errors;
    delay(1);
  
}

unsigned long millisFixed() {
  return millis() / 64;  // ชดเชย prescaler ที่เปลี่ยนเป็น 1
}


void TT(int avgspeed, float Kp, float Kd, int milisec) {
    int Status = 0;
    errors = 0;
    previous_error = 0;
    unsigned long BaseTimer = millisFixed();
    unsigned long Timer = 0;
    while(Status == 0) {
      TL(avgspeed, Kp, Kd);
      Timer = millisFixed() - BaseTimer;
      if(Timer >= milisec) {
        Status = 1;
      }
    }

}
