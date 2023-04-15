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
  input = fmin(fmax(input, -200), 200); //batas
  input = abs(input);
  analogWrite(PWMM, input);
}
