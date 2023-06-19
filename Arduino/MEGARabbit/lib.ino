#define POSM1 45
#define POSM2 135
#define POSM3 225
#define POSM4 315

#define RADIUSMTR 0.1 //meter unit
#define RADIUSBAN 0.1/2
#define KBAN 2*M_PI*RADIUSBAN

#define PPR 200*19.2

#define KPx 1.3
#define KPy 1.3
#define KPt 1.0

float toRad(float degree) {
  return degree * M_PI / 180;
}
void klbUpper(){
  //maxon bawah mundur
  motor7(-100);
  while(digitalRead(LIM5) == 1);
  motor7(0);
  //bldc mundur
  motor8(-100);
  while(digitalRead(LIM3) == 1);
  motor8(0);
  motor6(100);
  while(digitalRead(LIM1) == 1);
  motor6(0);
  motor7(0);
  motor8(0);
}
void smoothing() {
  //smoothing
  XSmoothed = (vx * 0.05) + (XPrev * 0.95);
  XPrev = XSmoothed;
  YSmoothed = (vy * 0.05) + (YPrev * 0.95);
  YPrev = YSmoothed;
  TSmoothed = (vt * 0.05) + (TPrev * 0.95);
  TPrev = TSmoothed;
}

void kalibrasiIMU() {
  Serial3.begin(115200);

  Serial.println("Mulai Kalibret");

  delay(3000);

  Serial3.write(0xA5);
  Serial3.write(0x54);

  delay(1000); // Jeda sebelum kalibrasi heading

  // Kalibrasi Heading
  Serial3.write(0xA5);
  Serial3.write(0x55);

  delay(100); // Jeda sebelum konfigurasi output

  // Output ASCII
  Serial3.write(0xA5);
  Serial3.write(0x53);

  delay(100); // Jeda sebentar
  Serial.println("selesai kalibret IMU");
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
//  Serial.println(cmps.heading);
}

void readEnc1() {
  digitalRead(encB1) == 1 ? enc1++ : enc1--;
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

void kinematic(float vX, float vY, float theta, float heading) {
  float setradPS1 = (-sin(toRad(POSM1 + heading)) * vX + cos(toRad(POSM1 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
  float setradPS2 = (-sin(toRad(POSM2 + heading)) * vX + cos(toRad(POSM2 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
  float setradPS3 = (-sin(toRad(POSM3 + heading)) * vX + cos(toRad(POSM3 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
  float setradPS4 = (-sin(toRad(POSM4 + heading)) * vX + cos(toRad(POSM4 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
  Serial2.print('!'); Serial2.println(setradPS1);
  Serial2.print('@'); Serial2.println(setradPS2);
  Serial2.print('#'); Serial2.println(setradPS3);
  Serial2.print('$'); Serial2.println(setradPS4);
}
void hadapFalcon(int tiang){
  Serial2.print('T'); Serial2.println(tiang);
}
void manualFalcon(int arah){ //manual
  Serial2.print('C'); Serial2.println(arah);
}
void calculatePos() {
  updateCMPS();
  //displacement
  float v1 = (enc1 - lastEnc1) * KBAN / (PPR);
  float v2 = (enc2 - lastEnc2) * KBAN / (PPR);
  float v3 = (enc3 - lastEnc3) * KBAN / (PPR);
  float v4 = (enc4 - lastEnc4) * KBAN / (PPR);
  
  lastEnc1 = enc1;
  lastEnc2 = enc2;
  lastEnc3 = enc3;
  lastEnc4 = enc4;
  
  float Vx = -sin(toRad(cmps.heading + POSM1)) * v1 + -sin(toRad(cmps.heading + POSM2)) * v2 + -sin(toRad(cmps.heading + POSM3)) * v3 + -sin(toRad(cmps.heading + POSM4)) * v4;
  float Vy = cos(toRad(cmps.heading + POSM1)) * v1 + cos(toRad(cmps.heading + POSM2)) * v2 + cos(toRad(cmps.heading + POSM3)) * v3 + cos(toRad(cmps.heading + POSM4)) * v4;
  
  x += Vx;
  y += Vy;
//  Serial.print(x); Serial.print("\t"); Serial.println(y);
}

void setPos(float POSX, float POSY, float HADAP) {
  calculatePos();
  //PID Posisi
  float errX = POSX - x;
  float PIDx = KPx * errX;
  //  PIDx = fmaxf(-6.3, fminf(PIDx,6.3));

  float errY = POSY - y;
  float PIDy = KPy * errY;
  //  PIDy = fmaxf(-6.3, fminf(PIDy, 6.3));


  float errT = HADAP - cmps.heading;
  if(errT > 180 || errT < -180){
  errT = cmps.heading - HADAP;
  }
  float PIDt = KPt * errT;
  PIDt = fmaxf(-3.7, fminf(PIDt, 3.7));
  kinematic(PIDx, PIDy, PIDt, cmps.heading);
}

int tiangtoFalcon(uint8_t tiang){
  if(tiang == 1) return 1643;
  else if(tiang == 2) return 1680;
  else if(tiang == 3) return 1705;
  else return 1500; //falcon mati
}

void motor5(int input) {
  if (input < 0) {
    digitalWrite(CW5, 1);
    digitalWrite(CCW5, 0);
  }
  else if (input > 0) {
    digitalWrite(CW5, 0);
    digitalWrite(CCW5, 1);
  }
  input = fmin(fmax(input, -PWMMAX5), PWMMAX5); //batas
  input = abs(input);
  analogWrite(PWM5, input);
}

void motor6(int input) {
  if (input < 0) {
    digitalWrite(CW6, 1);
    digitalWrite(CCW6, 0);
  }
  else if (input > 0) {
    digitalWrite(CW6, 0);
    digitalWrite(CCW6, 1);
  }
  input = fmin(fmax(input, -PWMMAX6), PWMMAX6); //batas
  input = abs(input);
  analogWrite(PWM6, input);
}

void motor7(int input) {
  if (input < 0) {
    digitalWrite(CW7, 1);
    digitalWrite(CCW7, 0);
  }
  else if (input > 0) {
    digitalWrite(CW7, 0);
    digitalWrite(CCW7, 1);
  }
  input = fmin(fmax(input, -PWMMAX7), PWMMAX7); //batas
  input = abs(input);
  analogWrite(PWM7, input);
}

void motor8(int input) {
  if (input < 0) {
    digitalWrite(CW8, 1);
    digitalWrite(CCW8, 0);
  }
  else if (input > 0) {
    digitalWrite(CW8, 0);
    digitalWrite(CCW8, 1);
  }
  input = fmin(fmax(input, -PWMMAX8), PWMMAX8); //batas
  input = abs(input);
  analogWrite(PWM8, input);
}
