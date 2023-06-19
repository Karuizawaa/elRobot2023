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
  while (digitalRead(OPTIC1) == LOW || digitalRead(OPTIC2) == LOW) {
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, LOW);
    if(digitalRead(OPTIC1) == LOW){
      digitalWrite(PUL1, HIGH);
    }
    if(digitalRead(OPTIC2) == LOW){
      digitalWrite(PUL2, HIGH);
    }
    delayMicroseconds(200);
    if(digitalRead(OPTIC1) == LOW){
      digitalWrite(PUL1, LOW);
    }
    if(digitalRead(OPTIC2) == LOW){
      digitalWrite(PUL2, LOW);
    }
    delayMicroseconds(200);
//    if(digitalRead(OPTIC1) == 0){
//      digitalWrite(DIR1, LOW);
//      digitalWrite(PUL1, HIGH);
//      delayMicroseconds(200); // ganti delay untuk mempercepat motor
//      digitalWrite(PUL1, LOW);
//      delayMicroseconds(200); // ganti delay untuk mempercepat motor
//    }
//    
//    if(digitalRead(OPTIC2) == 0){
//      digitalWrite(DIR2, LOW);
//      digitalWrite(PUL2, HIGH);
//      delayMicroseconds(200); // ganti delay untuk mempercepat motor
//      digitalWrite(PUL2, LOW);
//      delayMicroseconds(200); // ganti delay untuk mempercepat motor
//    }
  }
  sekarang1 = 0;
  sekarang2 = 0;
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
  while (sekarang1 != langkah) {

    if (langkah > sekarang1) {
      digitalWrite(DIR1, LOW);
      
      sekarang1++;
    }
    else {
      digitalWrite(DIR1, HIGH);
      sekarang1--;
    }
    digitalWrite(PUL1, HIGH);
    delayMicroseconds(kecepatan); // ganti delay untuk mempercepat motor
    digitalWrite(PUL1, LOW);
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

void gakTurun(){
  //mentokin keatas
      motor2(50);
      while(digitalRead(PROX1) == 1 || digitalRead(PROX2) == 1){
        if(digitalRead(PROX1) == 1){
          digitalWrite(DIR1, HIGH);
          digitalWrite(PUL1, HIGH);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
          digitalWrite(PUL1, LOW);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
        }
        if(digitalRead(PROX2) == 1){
          digitalWrite(DIR2, HIGH);
          digitalWrite(PUL2, HIGH);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
          digitalWrite(PUL2, LOW);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
        }
      }
      //turun lagi sampai mati
      while(digitalRead(PROX1) == 0 || digitalRead(PROX2) == 0){
        if(digitalRead(PROX1) == 0){
          digitalWrite(DIR1, LOW);
          digitalWrite(PUL1, HIGH);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
          digitalWrite(PUL1, LOW);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
        }
        if(digitalRead(PROX2) == 0){
          digitalWrite(DIR2, LOW);
          digitalWrite(PUL2, HIGH);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
          digitalWrite(PUL2, LOW);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
        }
      }
//      unsigned long tunggu = millis();
//      while(millis() - tunggu <= 200){
//        updateCMPS();
//        motor2(-150);
//      }
//      motor2(0);
//

//      for(int i = 0; i <= 300; i++){
//        digitalWrite(DIR2, HIGH);
//        digitalWrite(DIR1, HIGH);
//        
//        if(i < 200) digitalWrite(PUL2, HIGH);
//        digitalWrite(PUL1, HIGH);
//        delayMicroseconds(200); // ganti delay untuk mempercepat motor
//        
//        if(i < 200)digitalWrite(PUL2, LOW);
//        digitalWrite(PUL1, LOW);
//        delayMicroseconds(200); // ganti delay untuk mempercepat motor
//        
//      }

//      delay(300);
      
      while(digitalRead(LIM10) != LOW){
        updateCMPS();
        motor2(-255);
        
        if(int n = Udp.parsePacket()){
          Udp.read(packetBuffer,6);  // buffer to hold incoming packet,
          packetBuffer[n] = '\0';
          if(packetBuffer[0] == 'B') motor2(255);
          if(packetBuffer[0] == 'F') motor2(-255);
          if(packetBuffer[0] == 'S') motor2(0);
        }
      }
      for(int i = 0; i <= 500; i++){
        digitalWrite(DIR1, LOW);
        if(i<200){
          digitalWrite(DIR2, LOW);
          digitalWrite(PUL2, HIGH);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
          digitalWrite(PUL2, LOW);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
        }
        digitalWrite(DIR1, LOW);
        digitalWrite(PUL1, HIGH);
        delayMicroseconds(200); // ganti delay untuk mempercepat motor
        digitalWrite(PUL1, LOW);
        delayMicroseconds(200); // ganti delay untuk mempercepat motor
      }
      //kebelakang
      while(digitalRead(LIM9) != 0){
        updateCMPS();
        motor2(255);
      }
      motor2(0);
}
