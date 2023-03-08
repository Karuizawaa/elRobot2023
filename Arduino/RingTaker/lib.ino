void iqro1() {
  digitalRead(encB1) == 1 ? counter1++ : counter1--;
}

void iqro2() {
  digitalRead(encB2) == 1 ? counter2++ : counter2--;
}

void smoothing() {
  falconSmoothed = (setPoint * 0.0005) + (falconPrev * 0.9995);
  falconPrev = falconSmoothed;
}

void motoFalcon(int rpm){
  setPoint = (-rpm / 13) + 1500;
//  Serial.printSerial.print(rpm); Serial.print("\t");Serial.println(pwm);
  falcon.writeMicroseconds(falconSmoothed);
}

void waitMillis(int millisec) {
  curr = millis();
  do{
    nh.spinOnce();
  }
  while (!(millis() - curr > millisec));
}

void calibrate() {

//  do {
//    lifter(100);
//  } while (digitalRead(LSWUP) != LOW);
//  lifter(30);
//  counter2 = 0;
//  do {
//    worm(135);
//  } while (digitalRead(LSDPN) != LOW);
//  worm(0);
//  counter1 = 0;
}

void motor1(float input) {
  if (input < 0) {
    digitalWrite(CW1, 1);
    digitalWrite(CCW1, 0);
  }
  else if (input > 0) {
    digitalWrite(CW1, 0);
    digitalWrite(CCW1, 1);
  }
  input = fminf(fmaxf(input, -100), 105); //batas
  input = abs(input);
  analogWrite(PWMM1, input);
}

void motor2(float input) {
  if (input < 0) {
    digitalWrite(CW2, 1);
    digitalWrite(CCW2, 0);
  }
  else if (input > 0) {
    digitalWrite(CW2, 0);
    digitalWrite(CCW2, 1);
  }
  input = fminf(fmaxf(input, -20), 100); //batas
  input = abs(input);
  analogWrite(PWMM2, input);
}
void motor3(float input) {
  if (input < 0) {
    digitalWrite(CW3, 1);
    digitalWrite(CCW3, 0);
  }
  else if (input > 0) {
    digitalWrite(CW3, 0);
    digitalWrite(CCW3, 1);
  }
  input = fminf(fmaxf(input, -255), 255); //batas
  input = abs(input);
  analogWrite(PWMM3, input);
}
void motor4(float input) {
  if (input < 0) {
    digitalWrite(CW4, 1);
    digitalWrite(CCW4, 0);
  }
  else if (input > 0) {
    digitalWrite(CW4, 0);
    digitalWrite(CCW4, 1);
  }
  input = fminf(fmaxf(input, -255), 255); //batas
  input = abs(input);
  analogWrite(PWMM4, input);
}

void motor5(float input) {
  if (input < 0) {
    digitalWrite(CW5, 1);
    digitalWrite(CCW5, 0);
  }
  else if (input > 0) {
    digitalWrite(CW5, 0);
    digitalWrite(CCW5, 1);
  }
  input = fminf(fmaxf(input, -255), 255); //batas
  input = abs(input);
  analogWrite(PWMM5, input);
}
