void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);

}
char wkwk;
void loop() {
  if(Serial.available()){
    wkwk = Serial.read();
    if(wkwk = 'W') digitalWrite(13,1);
  }
//  Serial.println(wkwk);/
}
