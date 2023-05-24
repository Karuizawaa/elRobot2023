#include <Servo.h>

Servo falcon;

#define DIR 12
#define PUL 13
#define OPTIC 22

//MOTOR 2
#define pwmM2 4
#define cwM2  27
#define ccwM2 29
#define PWMMAX 200

//LIMIT atas
#define LIM10 47  //mentok depen
#define LIM9 49 //mentok blakang

#define STEPUP 24
#define STEPDOWN 26

#define stepsPerRevolution 800 // sesuaikan dengan settingan SW1-SW3 pada modul motor driver
long sekarang;
int lantai;
int prevLantai;

void motor2 (int pwm) {
  pwm = max(-PWMMAX, min(pwm, PWMMAX));
  analogWrite(pwmM2, fabs(pwm));

  if (pwm < 0) {
    digitalWrite(cwM2, 1);
    digitalWrite(ccwM2, 0);
  }
  else if (pwm > 0) {
    digitalWrite(cwM2, 0);
    digitalWrite(ccwM2, 1);
  }
  else {
    digitalWrite(cwM2, 0);
    digitalWrite(ccwM2, 0);
  }
}

void setup() {
  falcon.attach(6);
  pinMode(STEPUP, INPUT_PULLUP);
  pinMode(STEPDOWN, INPUT_PULLUP);
  pinMode(LIM9, INPUT_PULLUP);
  pinMode(LIM10, INPUT_PULLUP);
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(OPTIC, INPUT);
  pinMode(pwmM2, OUTPUT);
  pinMode(cwM2, OUTPUT);
  pinMode(ccwM2, OUTPUT);
  Serial.begin(115200);
//  while (digitalRead(LIM9) != LOW) {
//    Serial.println("motor mentokin kedepan");
//    motor2(255);
//  }
//  Serial.println("motor sudah mentok kedepan");
//  motor2(0);
//  while (digitalRead(OPTIC) != HIGH) {
//
//    Serial.println("Stepper kebawah");
//    digitalWrite(DIR, LOW);
//    digitalWrite(PUL, HIGH);
//    delayMicroseconds(200); // ganti delay untuk mempercepat motor
//    digitalWrite(PUL, LOW);
//    delayMicroseconds(200); // ganti delay untuk mempercepat motor
//  }
}

void toStep(int langkah, int kecepatan) {
  while (sekarang != langkah) {

    if (langkah > sekarang) {
      digitalWrite(DIR, LOW);
      sekarang++;
    }
    else {
      digitalWrite(DIR, HIGH);
      sekarang--;
    }
    digitalWrite(PUL, HIGH);
    delayMicroseconds(kecepatan); // ganti delay untuk mempercepat motor
    digitalWrite(PUL, LOW);
    delayMicroseconds(kecepatan); // ganti delay untuk mempercepat motor
  }
  
}

int masuk;
void loop() {
//  falcon.writeMicroseconds(1672);
if(digitalRead(STEPUP) == 0){
    digitalWrite(DIR, LOW);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(200); // ganti delay untuk mempercepat motor
    digitalWrite(PUL, LOW);
    delayMicroseconds(200); // ganti delay untuk mempercepat motor
  }
  if(digitalRead(STEPDOWN) == 0){
    digitalWrite(DIR, HIGH);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(200); // ganti delay untuk mempercepat motor
    digitalWrite(PUL, LOW);
    delayMicroseconds(200); // ganti delay untuk mempercepat motor
  }
//  if(Serial.available()){
//    lantai = Serial.parseInt();
//  }
//  if(lantai != prevLantai){
//    if(lantai < -1600 || lantai == 0){
//      //kedepan
//      while(digitalRead(LIM10) != LOW){
////        updateCMPS();
//        motor2(-255);
//      }
//      motor2(0);
//      delay(500);
//      //kebelakang
//      while(digitalRead(LIM9) != 0){
////        updateCMPS();
//        motor2(255);
//      }
//      motor2(0);
//      toStep(lantai, 200);
//      
////      masok = 'a';
//      prevLantai = lantai;
//    }
//    else{
//      toStep(lantai, 200);
//    }
//    
//  }
}
