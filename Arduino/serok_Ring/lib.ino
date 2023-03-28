void kalibrasi(){
  while(digitalRead(OPT) == 0){
    digitalWrite(DIR, LOW);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(700); // ganti delay untuk mempercepat motor
    digitalWrite(PUL, LOW);
    delayMicroseconds(700); // ganti delay untuk mempercepat motor
  }
  sekarang = 0;
}

void waitMillis(int millisec) {
  curr = millis();
  do{
    nh.spinOnce();
  }
  while (!(millis() - curr > millisec));
}

void ROSCON(){
  if(millis() - curr > 1000){
    nh.spinOnce();
    curr = millis();
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

void smoothing() {
  falconSmoothed = (setPoint * 0.0005) + (falconPrev * 0.9995);
  falconPrev = falconSmoothed;
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
  input = fminf(fmaxf(input, -PWMMAX), PWMMAX); //batas
  input = abs(input);
  analogWrite(PWMM1, input);
}
