uint8_t buf[8] = { 0 };   //Keyboard report buffer

void setup() {
  Serial.begin(9600);

  //open terminal
  buf[2] = 224; //ctrl
  Serial.write(buf, 8); // Send keypress
  buf[2] = 226; //alt
  Serial.write(buf, 8); // Send keypress
  buf[2] = 23; //alt
  Serial.write(buf, 8); // Send keypress 
  releaseKey();

  delay(2500);
  buf[2] = 22; //s
  Serial.write(buf, 8); // Send keypress
  buf[2] = 11; //h
  Serial.write(buf, 8); // Send keypress
  buf[2] = 24; //u
  Serial.write(buf, 8); // Send keypress 
  buf[2] = 23; //t
  Serial.write(buf, 8); // Send keypress
  buf[2] = 7; //d
  Serial.write(buf, 8); // Send keypress
  buf[2] = 18; //o
  Serial.write(buf, 8); // Send keypress 
  buf[2] = 26; //w
  Serial.write(buf, 8); // Send keypress
  buf[2] = 17; //n
  Serial.write(buf, 8); // Send keypress
  buf[2] = 44; //'space'
  Serial.write(buf, 8); // Send keypress 
  buf[2] = 17; //n
  Serial.write(buf, 8); // Send keypress
  buf[2] = 18; //o
  Serial.write(buf, 8); // Send keypress
  buf[2] = 26; //w
  Serial.write(buf, 8); // Send keypress 
  buf[2] = 40; //w
  Serial.write(buf, 8); // Send keypress 
}

void loop() {
  // put your main code here, to run repeatedly:

}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Send Release key  
}
