void kalibrasiTransfer(){
  while(digitalRead(LIM9) == 1){
    //motor maju sampe kedepan
    servo(90);
  }
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

int lantaitoStep(int lantai){
  return(lantai * -100);
}
void kalibrasiIMU() {
  Serial3.begin(115200);

  Serial.println("mulai kalibret");

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
  char hadap[6];
  sprintf(headStr , "!%d", cmps.heading);
  Udp.beginPacket(IPAddress(192,168,0,3),5555);
  Udp.write(headStr);
  Udp.endPacket();
}

void servo(int sudut){
  int writems = (400.0 * (float)sudut / 27.0) + 500.0;
  B3.writeMicroseconds(writems);
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
