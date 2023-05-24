void readEnc(){
  digitalRead(encB) == 0 ? encoder++ : encoder--;
}

void updateVel() {
  char tmp; // Variabel temporary
  while (Serial.available()) {
    tmp = Serial.read();
    base.buffer[base.counter++] = tmp;
    if (tmp == '\n') { // Langkah 1
      base.buffer[base.counter] = 0; // Karakter terminator
      if(base.buffer[0] == '!') base.vel = atof(strtok(base.buffer + 1, '='));
      base.counter = 0;
    }
  }
}

void motor(int input) {
  if (input < 0) {
    digitalWrite(CW, 1);
    digitalWrite(CCW, 0);
  }
  else if (input > 0) {
    digitalWrite(CW, 0);
    digitalWrite(CCW, 1);
  }
  input = fmin(fmax(input, -200), 200); //batas
  input = abs(input);
  analogWrite(PWMM, input);
}

void closedloopctl (float setradPS){
  volatile unsigned long currT = micros();
  float deltaT = ((float) (currT - prevT)) / 1.0e6;
  prevT = currT;
  float radps = ((encoder - lastEncoder) * 2 * M_PI / (200*19.2)) / deltaT;
  lastEncoder = encoder;
  vFilt = 0.854 * vFilt + 0.0728 * radps + 0.0728 * vPrev;
  
  vPrev = radps;
  float err = setradPS - radps;
  sum += err * deltaT;
  float PID = KP * err + KI * sum;
  motor(PID);
}
