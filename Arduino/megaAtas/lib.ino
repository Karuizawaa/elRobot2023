//void rpmFalcon(){
//  // Compute velocity with method 2
//  long currT = micros();
//  float deltaT = ((float) (currT - prevT))/1.0e6;
//  float rpm = 60/deltaT;
//  prevT = currT;
//}

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

void kalibrasiStepper() {
  
  //servo naik
//  servo(70);
  while (digitalRead(OPTIC) != HIGH) {

    Serial.println("Stepper kebawah");
    digitalWrite(DIR, LOW);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(200); // ganti delay untuk mempercepat motor
    digitalWrite(PUL, LOW);
    delayMicroseconds(200); // ganti delay untuk mempercepat motor
  }
  sekarang = 0;
  //kedepan
  Serial.println("Stepper udah kebawah");
  while (digitalRead(LIM10) != LOW) {
    Serial.println("motor mentokin kedepan");
    motor2(-255);
  }
  Serial.println("motor sudah mentok kedepan");
  motor2(0);
}

void updateCMPS() {
  char tmp; // Variabel temporary

  while (Serial3.available()) {
    tmp = Serial3.read();
    cmps.buffer[cmps.counter++] = tmp;
    if (tmp == '\n') { // Langkah 1
      cmps.buffer[cmps.counter] = 0; // Karakter terminator
      cmps.heading = atof(strtok(cmps.buffer + 5, ",")); // Langkah 2-4
      cmps.headInt = (int)cmps.heading;
      cmps.counter = 0;
    }


  }
  bool sw1 = digitalRead(LIM1);
  bool sw2 = digitalRead(LIM2);
  bool sw3 = digitalRead(LIM3);
  bool sw4 = digitalRead(LIM4);
  bool sw5 = digitalRead(LIM5);
  bool sw6 = digitalRead(LIM6);
  bool sw7 = digitalRead(LIM7);
  bool sw8 = digitalRead(LIM8);
  bool sw9 = digitalRead(LIM9);
  bool sw10 = digitalRead(LIM10);
  Udp.beginPacket(IPAddress(192, 168, 0, 55), 5555);
  sprintf(headStr, "%d%d%d%d%d%d%d%d%d%d=%s~", sw1, sw2, sw3, sw4, sw5, sw6, sw7, sw8, sw9, sw10, strtok(cmps.buffer + 5, ","));

  Udp.write(headStr);
  Udp.endPacket();
  Serial.println(headStr);
}

void gasFalcon(int input){
  input = fmin(fmax(input, 1500), 2000); //batas
  falcon.writeMicroseconds(input);
}

void servo(int sudut) {
  int writems = (400.0 * (float)sudut / 27.0) + 500.0;
  B3.writeMicroseconds(writems);
}

void toStep(int langkah, int kecepatan) {
  while (sekarang != langkah) {

    if (langkah > sekarang) {
      digitalWrite(DIR, LOW);
      
      sekarang++;
    }
    else {
      digitalWrite(DIR, HIGH);
      sekarang--;
    }
    digitalWrite(PUL, HIGH);
    delayMicroseconds(kecepatan); // ganti delay untuk mempercepat motor
    digitalWrite(PUL, LOW);
    delayMicroseconds(kecepatan); // ganti delay untuk mempercepat motor
  }
}

void toStepBareng(int langkah, int kecepatan) {
  digitalRead(LIM9) != LOW ? motor2(-200) : motor2(0);
  while (sekarang != langkah) {
    if (langkah > sekarang) {
      digitalWrite(DIR, LOW);
      sekarang++;
    }
    else {
      digitalWrite(DIR, HIGH);
      sekarang--;
    }
    digitalWrite(PUL, HIGH);
    delayMicroseconds(kecepatan); // ganti delay untuk mempercepat motor
    digitalWrite(PUL, LOW);
    delayMicroseconds(kecepatan); // ganti delay untuk mempercepat motor
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

  if (pwm < 0) {
    digitalWrite(cwM2, 1);
    digitalWrite(ccwM2, 0);
  }
  else if (pwm > 0) {
    digitalWrite(cwM2, 0);
    digitalWrite(ccwM2, 1);
  }
  else {
    digitalWrite(cwM2, 0);
    digitalWrite(ccwM2, 0);
  }
}

//volatile float sum;
//#define PPR 1
//void PID(){
//
//  volatile unsigned long currT = micros();
//  float deltaT = ((float) (currT - prevT)) / 1.0e6; //jadi satuan detik
//  prevT = currT;
//
//  volatile float setRPM;
//
//  volatile float RPM = ((encFalcon - lastFalcon) * 1 / PPR)  * 60 / deltaT;
//
//  volatile float err = setRPM - RPM;
//  sum += err;
//  volatile float PIDf = KPf * err + KIf * sum;
//
//  if(setRPM == 0){
//    gasFalcon(1500);
//    sum = 0;
//  }
//  gasFalcon(PIDf);
//}
