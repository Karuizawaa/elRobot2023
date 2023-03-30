void motor1(float input) {
  if (input < 0) {
    digitalWrite(CW1, 1);
    digitalWrite(CCW1, 0);
  }
  else if (input > 0) {
    digitalWrite(CW1, 0);
    digitalWrite(CCW1, 1);
  }
  input = fminf(fmaxf(input, -200), 200); //batas
  input = abs(input);
  analogWrite(PWMM1, input);
}
