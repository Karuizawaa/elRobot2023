void rpmFalcon(){
  // Compute velocity with method 2
  long currT = micros();
  float deltaT = ((float) (currT - prevT))/1.0e6;
  float rpm = 60/deltaT;
  prevT = currT;
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

void gasFalcon(int microsec){
  microsec = max(1500, min(microsec, 2000));
  falcon.writeMicroseconds(microsec);
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

volatile float sum;
#define PPR 1
void PID(){
  
  volatile unsigned long currT = micros();
  float deltaT = ((float) (currT - prevT)) / 1.0e6; //jadi satuan detik
  prevT = currT;
  
  volatile float setRPM;
  
  volatile float RPM = ((encFalcon - lastFalcon) * 1 / PPR)  * 60 / deltaT;
  
  volatile float err = setRPM - RPM;
  sum += err;
  volatile float PIDf = KPf * err + KIf * sum;

  if(setRPM == 0){
    gasFalcon(1500);
    sum = 0;
  }
  gasFalcon(PIDf);
}
