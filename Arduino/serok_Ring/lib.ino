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
