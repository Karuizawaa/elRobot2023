void motor(int input) {
  if (input < 0) {
    digitalWrite(CW, 1);
    digitalWrite(CCW, 0);
  }
  else if (input > 0) {
    digitalWrite(CW, 0);
    digitalWrite(CCW, 1);
  }
  else{
    digitalWrite(CW, 0);
    digitalWrite(CCW, 0);
  }
  input = fmin(fmax(input, -PWMMAX), PWMMAX); //batas
  input = abs(input);
  analogWrite(PWMM, input);
}

void closedloopctl (int setPOS){
  //jika belum sampe zero;
  int kondisiNow = ADS.readADC(0);
//  if(kondisiNow < NILAIMIN) ADS.readADC(0) + NILAIMAX;
  int err = setPOS - kondisiNow;

  // setelah zero atau lebih kecil dari mentok kiri;
//  if(setPOS < NILAIMIN){
//    err = (setPOS + NILAIMAX) - kondisiNow;
//  }
  float PID = KP * err;
  motor(-PID);
}

void savePosTiang(uint8_t tiang){
  if(tiang > 0){
    ADS.setGain(0);
    int16_t val_0 = ADS.readADC(0);
    float f = ADS.toVoltage(1);  // voltage factor
    EEPROM.write((tiang * 2) - 2, val_0 >> 8);
    EEPROM.write((tiang * 2) - 1, val_0);
  }
}



int16_t gotoTiang(uint8_t tiang){
  if(tiang > 0) return (EEPROM.read((tiang * 2) - 2) << 8 | EEPROM.read((tiang * 2) - 1));
  else return (EEPROM.read(4094) << 8 | EEPROM.read(4095)); // hadap depan atau origin
}

void cariTiang(){
  for(int i = 1; i <= TOTALTIANG; i++){
    while(digitalRead(SAVEPOS) == 1){
      if(digitalRead(SWCW) == 0) motor(200);
      else if(digitalRead(SWCCW) == 0) motor(-200);
      else motor(0);
      delay(5);
    }
    savePosTiang(i);
    delay(1000);
  }
}

void cariDepan(){
  int16_t maxVal, prevmaxVal;
  Serial.println("Matchkan depan launcher dengan depan Base");
  delay(1000);
  while(digitalRead(SAVEPOS) == 1){
    ADS.setGain(0);
    int16_t val_0 = ADS.readADC(0);
    float f = ADS.toVoltage(1);  // voltage factor

    
    if(val_0 > prevmaxVal) maxVal = val_0;
    prevmaxVal = maxVal;
    

    if(digitalRead(SWCW) == 0) motor(200);
    else if(digitalRead(SWCCW) == 0) motor(-200);
    else motor(0);
    delay(1);
  }
  ADS.setGain(0);
  int16_t val_0 = ADS.readADC(0);
  float f = ADS.toVoltage(1);  // voltage factor
  EEPROM.write(4092, maxVal >> 8);
  EEPROM.write(4093, maxVal);
  
  //hadap depan
  EEPROM.write(4094, val_0 >> 8);
  EEPROM.write(4095, val_0);
}

void updatePOS() {
  char tmp; // Variabel temporary
  while (Serial.available()) {
    tmp = Serial.read();
    base.buffer[base.counter++] = tmp;
    if (tmp == '\n') { // Langkah 1
      base.buffer[base.counter] = 0; // Karakter terminator
      if(base.buffer[0] == 'T'){
        base.mode = false;
        base.pos = atoi(strtok(base.buffer + 1, '='));
      }
      if(base.buffer[0] == 'C'){
        base.mode = true;
        base.pwm = atoi(strtok(base.buffer + 1, '='));
      }
      
      base.counter = 0;
    }
  }
}
