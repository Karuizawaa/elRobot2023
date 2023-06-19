void readEnc(){
  digitalRead(encB) == 0 ? encoder++ : encoder--;
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
  else{
    digitalWrite(CW, 0);
    digitalWrite(CCW, 0);
  }
  input = fmin(fmax(input, -200), 200); //batas
  input = abs(input);
  analogWrite(PWMM, input);
}

void kirimEnc(){
  Udp.beginPacket(IPAddress(192,168,0,55),5555);
  Udp.print(encoder);
  Udp.endPacket();
//  Udp.flush();
}

void updateVel(){
  if(int n = Udp.parsePacket()){
    Udp.read(packetBuffer,512);  // buffer to hold incoming packet,
    packetBuffer[n] = '\0';
    setVel = atof(packetBuffer);
  }
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
  motor(-PID);
}
