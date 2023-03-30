void setup() {
  Serial.begin(115200);
  Serial3.begin(57600);

}
char wkwk;
void loop() {
  if(Serial3.available()){
    wkwk = Serial3.read();
  }
  Serial.println(wkwk);
}
