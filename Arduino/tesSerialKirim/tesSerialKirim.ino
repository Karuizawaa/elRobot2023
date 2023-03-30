void setup() {
  Serial.begin(57600);

}

void loop() {
  Serial.write(88);
  delay(100);
}
