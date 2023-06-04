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
  input = fmin(fmax(input, -250), 250); //batas
  input = abs(input);
  analogWrite(PWMM, input);
}

void closedloopctl (float setPOS){
  float err = setPOS - ADS.readADC(0);
  float PID = KP * err;
  motor(PID);
}

void savePosTiang(uint8_t tiang){
  if(tiang > 0){
    ADS.setGain(0);
    int16_t val_0 = ADS.readADC(0);
    float f = ADS.toVoltage(1);  // voltage factor
    EEPROM.update((tiang * 2) - 2, val_0 >> 8);
    EEPROM.update((tiang * 2) - 1, val_0);
    Serial.print("Save tiang "); Serial.print(tiang); Serial.print(" dengan nilai "); Serial.println(val_0); 
  }
}

int16_t gotoTiang(uint8_t tiang){
  if(tiang > 0) return (EEPROM.read((tiang * 2) - 2) << 8 | EEPROM.read((tiang * 2) - 1));
  else return 0;
}

void cariTiang(){
  for(int i = 1; i <= TOTALTIANG; i++){
    Serial.print("Cari tiang ke "); Serial.println(i);
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
