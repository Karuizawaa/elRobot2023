//void readEnc(){
//  encoder++;
//}
void gasFalcon(int input){
  input = fmin(fmax(input, 1500), 2000); //batas
  falcon.writeMicroseconds(input);
}

//void readEnc(){
//  encoder++;
//  // Compute velocity with method 2
//  long currT = millis();
//  float deltaT = ((float) (currT - prevT_i))/1.0e3;
//  RPM_i = 60/(deltaT);
//  prevT_i = currT;
//}

void PID(float setRPM){
  
  volatile unsigned long currT = micros();
  float deltaT = ((float) (currT - prevT)) / 1.0e6; //jadi satuan detik
  prevT = currT;
  
  
//  RPM_i = (encoder - lastEncoder) * 60 / deltaT;
//  lastEncoder = encoder;
  
  volatile float err = setRPM - RPM_i;
  sum += err;
  volatile float PIDf = KPf * err + KIf * sum * deltaT;

  if(setRPM == 0.0){ 
    gasFalcon(1500);
    sum = 0;
  }
  gasFalcon(PIDf);
}
