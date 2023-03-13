xvoid setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

}

void loop() {
  digitalWrite(2, !digitalRead(2));
  delay(1500);
  digitalWrite(3, !digitalRead(3));
  delay(1500);
  digitalWrite(4, !digitalRead(4));
  delay(1500);
}
