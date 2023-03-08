void readEnc1() {
  digitalRead(encB1) == 0 ? enc1++ : enc1--;
}

void readEnc2() {
  digitalRead(encB2) == 0 ? enc2++ : enc2--;
}

void readEnc3() {
  digitalRead(encB3) == 0 ? enc3++ : enc3--;
}

void readEnc4() {
  digitalRead(encB4) == 0 ? enc4++ : enc4--;
}

float toRad(float degree) {
  return degree * M_PI / 180;
}

void smoothing() {
  //smoothing
  XSmoothed = (setX * 0.005) + (XPrev * 0.995);
  XPrev = XSmoothed;
  YSmoothed = (setY * 0.005) + (YPrev * 0.995);
  YPrev = YSmoothed;
  TSmoothed = (setT * 0.005) + (TPrev * 0.995);
  TPrev = TSmoothed;
}



void updateCMPS() {
  char tmp; // Variabel temporary

  while (Serial3.available()) {
    tmp = Serial3.read();
    cmps.buffer[cmps.counter++] = tmp;
    if (tmp == '\n') { // Langkah 1
      cmps.buffer[cmps.counter] = 0; // Karakter terminator
      cmps.heading = atof(strtok(cmps.buffer + 5, ",")); // Langkah 2-4
      cmps.counter = 0;
    }
  }
}

void motor1 (int pwm) {
  pwm = max(-PWMMAX, min(pwm, PWMMAX));
  analogWrite(pwmM1, fabs(pwm));

  if (pwm > 0) {
    digitalWrite(cwM1, 1);
    digitalWrite(ccwM1, 0);
  }
  else if (pwm < 0) {
    digitalWrite(cwM1, 0);
    digitalWrite(ccwM1, 1);
  }
  else {
    digitalWrite(cwM1, 0);
    digitalWrite(ccwM1, 0);
  }
}

void motor2 (int pwm) {
  pwm = max(-PWMMAX, min(pwm, PWMMAX));
  analogWrite(pwmM2, fabs(pwm));

  if (pwm > 0) {
    digitalWrite(cwM2, 1);
    digitalWrite(ccwM2, 0);
  }
  else if (pwm < 0) {
    digitalWrite(cwM2, 0);
    digitalWrite(ccwM2, 1);
  }
  else {
    digitalWrite(cwM2, 0);
    digitalWrite(ccwM2, 0);
  }
}

void motor3 (int pwm) {
  pwm = max(-PWMMAX, min(pwm, PWMMAX));
  analogWrite(pwmM3, fabs(pwm));

  if (pwm < 0) {
    digitalWrite(cwM3, 1);
    digitalWrite(ccwM3, 0);
  }
  else if (pwm > 0) {
    digitalWrite(cwM3, 0);
    digitalWrite(ccwM3, 1);
  }
  else {
    digitalWrite(cwM3, 0);
    digitalWrite(ccwM3, 0);
  }
}

void motor4 (int pwm) {
  pwm = max(-PWMMAX, min(pwm, PWMMAX));
  analogWrite(pwmM4, fabs(pwm));

  if (pwm < 0) {
    digitalWrite(cwM4, 1);
    digitalWrite(ccwM4, 0);
  }
  else if (pwm > 0) {
    digitalWrite(cwM4, 0);
    digitalWrite(ccwM4, 1);
  }
  else {
    digitalWrite(cwM4, 0);
    digitalWrite(ccwM4, 0);
  }
}

void kinematic(float vX, float vY, float theta) {
  setradPS1 = (-sin(toRad(POSM1 + cmps.heading)) * vX + cos(toRad(POSM1 + cmps.heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
  setradPS2 = (-sin(toRad(POSM2 + cmps.heading)) * vX + cos(toRad(POSM2 + cmps.heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
  setradPS3 = (-sin(toRad(POSM3 + cmps.heading)) * vX + cos(toRad(POSM3 + cmps.heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
  setradPS4 = (-sin(toRad(POSM4 + cmps.heading)) * vX + cos(toRad(POSM4 + cmps.heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
  PID();
}

void setPos(float POSX, float POSY, float HADAP) {
  setX = POSX;
  setY = POSY;
  setT = HADAP;
  calculatePos();
  kinematic(PIDx, PIDy, PIDt);

}

void calculatePos() {
  float v1 = (enc1 - last1) * KBAN / (PPR);
  float v2 = (enc2 - last2) * KBAN / (PPR);
  float v3 = (enc3 - last3) * KBAN / (PPR);
  float v4 = (enc4 - last4) * KBAN / (PPR);

  last1 = enc1;
  last2 = enc2;
  last3 = enc3;
  last4 = enc4;

  float Vx = -sin(toRad(cmps.heading + POSM1)) * v1 + -sin(toRad(cmps.heading + POSM2)) * v2 + -sin(toRad(cmps.heading + POSM3)) * v3 + -sin(toRad(cmps.heading + POSM4)) * v4;
  float Vy = cos(toRad(cmps.heading + POSM1)) * v1 + cos(toRad(cmps.heading + POSM2)) * v2 + cos(toRad(cmps.heading + POSM3)) * v3 + cos(toRad(cmps.heading + POSM4)) * v4;

  x += Vx;
  y += Vy;
}

void PID() {
  smoothing();
  volatile unsigned long currT = micros();
  float deltaT = ((float) (currT - prevT)) / 1.0e6;
  prevT = currT;

  radps1 = ((enc1 - lastEnc1) * 2 * M_PI / PPR) / deltaT;
  radps2 = ((enc2 - lastEnc2) * 2 * M_PI / PPR) / deltaT;
  radps3 = ((enc3 - lastEnc3) * 2 * M_PI / PPR) / deltaT;
  radps4 = ((enc4 - lastEnc4) * 2 * M_PI / PPR) / deltaT;
  lastEnc1 = enc1;
  lastEnc2 = enc2;
  lastEnc3 = enc3;
  lastEnc4 = enc4;

  v1Filt = 0.854 * v1Filt + 0.0728 * radps1 + 0.0728 * v1Prev;
  v1Prev = radps1;
  v2Filt = 0.854 * v2Filt + 0.0728 * radps2 + 0.0728 * v2Prev;
  v2Prev = radps2;
  v3Filt = 0.854 * v3Filt + 0.0728 * radps3 + 0.0728 * v3Prev;
  v3Prev = radps3;
  v4Filt = 0.854 * v4Filt + 0.0728 * radps4 + 0.0728 * v4Prev;
  v4Prev = radps4;

  //PID KECEPATAN
  err1 = setradPS1 - v1Filt;
  sum1 += err1;
  PID1 = KP1 * err1 + KI1 * sum1 * deltaT;

  err2 = setradPS2 - v2Filt;
  sum2 += err2;
  PID2 = KP2 * err2 + KI2 * sum2 * deltaT;

  err3 = setradPS3 - v3Filt;
  sum3 += err3;
  PID3 = KP3 * err3 + KI3 * sum3 * deltaT;

  err4 = setradPS4 - v4Filt;
  sum4 += err4;
  PID4 = KP4 * err4 + KI4 * sum4 * deltaT;

  //PID Posisi
  errX = XSmoothed - x;
  sumX += errX;
  PIDx = KPx * errX + KIx * sumX * deltaT;
  PIDx = fmaxf(-7.3, fminf(PIDx, 7.3));

  errY = YSmoothed - y;
  sumY += errY;
  PIDy = KPy * errY + KIy * sumY * deltaT;
  PIDy = fmaxf(-7.3, fminf(PIDy, 7.3));

  errT = TSmoothed - cmps.heading;
  sumT += errT;
  PIDt = KPt * errT + KIt * sumT * deltaT;
  PIDt = fmaxf(-3.7, fminf(PIDt, 3.7));

  motor1(PID1);
  motor2(PID2);
  motor3(PID3);
  motor4(PID4);
}
