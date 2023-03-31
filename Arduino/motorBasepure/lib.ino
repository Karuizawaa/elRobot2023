void readEnc(){
  digitalRead(encB) == 0 ? encoder++ : encoder--;
  Udp.beginPacket(IPAddress(192,168,0,3),5555);
  sprintf(encoderStr,"%d", encoder);
  Udp.write(encoderStr);
  Udp.endPacket();
  
}

void motor(float input) {
  if (input < 0) {
    digitalWrite(CW, 1);
    digitalWrite(CCW, 0);
  }
  else if (input > 0) {
    digitalWrite(CW, 0);
    digitalWrite(CCW, 1);
  }
  input = fminf(fmaxf(input, -200), 200); //batas
  input = abs(input);
  analogWrite(PWMM, input);
}
