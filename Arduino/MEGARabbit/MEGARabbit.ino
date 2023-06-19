/* Bismillah Juara 1
   Rabbit Robot BARELANG-V 2023

   Stik ESP, Kinematic MEGA, slave nano

*/

#include <PS3BT.h>
#include <usbhub.h>
#include <Servo.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>


#define encA1 2
#define encB1 46

#define encA2 3
#define encB2 40

#define encA3 18  
#define encB3 42

#define encA4 19
#define encB4 48

//lifter
#define PWM5 6
#define CW5 32
#define CCW5 34
#define PWMMAX5 70

//motor atas
#define PWM6 4
#define CW6 27
#define CCW6 29
#define PWMMAX6 50

//makson bawah
#define PWM7 5
#define CW7 23
#define CCW7 25
#define PWMMAX7 200

//BLDC putih  --kebelakang, ++ kedepan
#define PWM8 7
#define CW8 8
#define CCW8 30
#define PWMMAX8 70

#define LIM1 43 //mentok depan atas
#define LIM2 45 //mentok belakang atas

#define LIM3 35 //mentok belakang tengah
#define LIM4 49 //mentok depan tengah

#define LIM5 37 //mentok belakang worm
#define LIM6 39 //mentok depan worm

#define PROX 28
#define OPTIC 41
Servo Falcon;
USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;
bool mode; // jika false launcher = depan, jika true gripper = depan, untuk kinematic base;


int vx, vy, vt;


struct gy25 {
  char buffer[50];
  int counter;
  float heading;
  int headInt;
} cmps;

long int enc1, enc2, enc3, enc4, lastEnc1, lastEnc2, lastEnc3, lastEnc4;
float x, y;

float XSmoothed, YSmoothed, TSmoothed;
float XPrev, YPrev, TPrev;
int offsetFalcon;

bool speedMode, modeFB;
float speedMax, rotateMax;

int indexHadap;
unsigned int indexFalcon;

bool modeHL;
int pwmHL;
//float setX, setY, setT;

void setup() {
  Falcon.attach(11);
  Serial.begin(115200);
  Serial2.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.println(F("\r\nPS3 Bluetooth Library Started"));
    kalibrasiIMU();
  pinMode(encA1, INPUT);
  pinMode(encB1, INPUT);

  pinMode(encA2, INPUT);
  pinMode(encB2, INPUT);

  pinMode(encA3, INPUT);
  pinMode(encB3, INPUT);

  pinMode(encA4, INPUT);
  pinMode(encB4, INPUT);

  pinMode(PWM5, OUTPUT);
  pinMode(CW5, OUTPUT);
  pinMode(CCW5, OUTPUT);

  pinMode(PWM6, OUTPUT);
  pinMode(CW6, OUTPUT);
  pinMode(CCW6, OUTPUT);

  pinMode(PWM7, OUTPUT);
  pinMode(CW7, OUTPUT);
  pinMode(CCW7, OUTPUT);

  pinMode(PWM8, OUTPUT);
  pinMode(CW8, OUTPUT);
  pinMode(CCW8, OUTPUT);

  pinMode(OPTIC, INPUT);

  attachInterrupt(digitalPinToInterrupt(encA1), readEnc1, RISING);
  attachInterrupt(digitalPinToInterrupt(encA2), readEnc2, RISING);
  attachInterrupt(digitalPinToInterrupt(encA3), readEnc3, RISING);
  attachInterrupt(digitalPinToInterrupt(encA4), readEnc4, RISING);
  mode = false;
//  klbUpper();
}

void loop() {
  delay(1);
  Usb.Task();
  updateCMPS();
  calculatePos();
  smoothing();
  //Kinematic Manual
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      vx = (PS3.getAnalogHat(LeftHatX) - 127.5) * speedMax / 127.5;
      vy = (-PS3.getAnalogHat(LeftHatY) + 127.5) * speedMax / 127.5;
      vt = (PS3.getAnalogButton(L2) - PS3.getAnalogButton(R2)) * rotateMax /255.0;
      if (mode == true){
        vx = -vx;
        vy = -vy;
      }
      kinematic(XSmoothed,YSmoothed,TSmoothed,0);
    }
    else{
      vx = 0;
      vy = 0;
      XSmoothed = 0;
      XPrev = 0;
      YSmoothed = 0;
      YPrev = 0;
      TSmoothed = 0;
      TPrev = 0;
      kinematic(XSmoothed,YSmoothed,0,0);
    }
    
    if(PS3.getButtonClick(SQUARE)){
      while(y<7.76){
        setPos(-2.26,8.5,0);
      }
      while(x>-9.70){
        setPos(-10.50,7.65,0);
      }
    }
    if(PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117){
      modeHL = false;
      pwmHL = (PS3.getAnalogHat(RightHatX) - 127.5) *60 / 127.5;
    }
    else{
      pwmHL = 0;
    }
    if(PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117){
      int pwm = (-PS3.getAnalogHat(RightHatY) + 127.5) * 70 / 127.5;
      motor5(pwm);
    }
    else{
      motor5(0);
    }
    if(PS3.getButtonClick(SELECT)) {
      mode = !mode;
    }
    if(PS3.getButtonClick(START)) {
      speedMode = !speedMode;
      if(speedMode){
        speedMax = 7.0;
        rotateMax = 25;
      }
      else{
        speedMax = 2.5;
        rotateMax = 15.0;
      }
//      mode = true;
//      PS3.setLedOff();
//      PS3.setLedOn(LED2);
//      speedMax = 2.5;
//      rotateMax = 15.0;
    }

    if(PS3.getButtonClick(CIRCLE)){
      hadapFalcon(0);
      hadapFalcon(0);
      hadapFalcon(0);
      hadapFalcon(0);
      //pastikan semua mundur
      motor8(-100);
      while(digitalRead(LIM3) == 1);
      motor8(0);
      motor7(-100);
      while(digitalRead(LIM5) == 1);
      motor7(0);
      motor6(-100);
      while(digitalRead(LIM2) == 1);
      motor6(0);
      motor7(0);
      motor8(0);
      while(digitalRead(PROX) == 1){
        //motor lifter naik
        motor5(70);
      }
      motor5(0);
      //slider dorong kedepan sampe limit
//      #define LIM1 43 //mentok depan atas
//      #define LIM2 45 //mentok belakang atas
//      
//      #define LIM3 35 //mentok belakang tengah
//      #define LIM4 49 //mentok depan tengah
//      
//      #define LIM5 37 //mentok belakang worm
//      #define LIM6 39 //mentok depan worm

      motor6(150);
      while(digitalRead(LIM1) == 1);
      

      //bldc dorong kedepan sampe limit
      //motor bldc kedepan
      motor8(70);
      while(digitalRead(LIM4) == 1){
        if(digitalRead(LIM2) == 0) motor6(0);
      }
      //motor bldc kebelakang
      motor8(-50);
      motor6(-150); //kebelakang
      while(digitalRead(LIM2) == 1 || digitalRead(LIM3) == 1){
        if(digitalRead(LIM2) == 0) motor6(0);
        if(digitalRead(LIM3) == 0) motor8(0);
        
      } 
      motor6(0);
      motor8(0);     
      //lifter naik
//      motor6(0);
//      motor8(0);
//      motor7(0);
//      motor5(70);
//      while(digitalRead(PROX) == 1){
//        if(digitalRead(LIM2) == 0) motor6(0);
//        if(digitalRead(LIM6) == 0) motor7(0);
//      }
//      motor5(0);
    }
    if(PS3.getButtonClick(CROSS)){
      //worm dorong kedepan sampe limit
      motor7(150);
      
      while(digitalRead(LIM6) == 1){
      }
      motor7(-150); //worm mundur
      while(digitalRead(LIM5) == 1){
      }
      motor7(0); //worm mundur
      
    }
    if(PS3.getButtonPress(L1)){
      if(modeHL)manualFalcon(60);
      else manualFalcon(70);
    }
    else if(PS3.getButtonPress(R1)){
      if(modeHL) manualFalcon(-60);
      else manualFalcon(-70);
    }
    else{
      manualFalcon(0);
    }
    if(PS3.getButtonClick(UP)) offsetFalcon++;
    if(PS3.getButtonClick(DOWN)) offsetFalcon--;
    
    if(PS3.getButtonClick(LEFT)){
      modeFB = !modeFB;
      modeFB ? Falcon.writeMicroseconds(tiangtoFalcon(1)+offsetFalcon):Falcon.writeMicroseconds(tiangtoFalcon(2)+offsetFalcon);
    }
    if(PS3.getButtonClick(RIGHT)){
      Falcon.writeMicroseconds(tiangtoFalcon(3)+offsetFalcon);
    }
    if(PS3.getButtonClick(PS)){
      Falcon.writeMicroseconds(tiangtoFalcon(0));
      offsetFalcon = 0;
    }
    if(PS3.getButtonClick(TRIANGLE)){
      modeHL = !modeHL;
    }

//    if (PS3.getButtonClick(PS)) {
//      Serial.print(F("\r\nPS"));
////      PS3.disconnect();
//    }
//    else {
//      if (PS3.getButtonClick(TRIANGLE)) {
//        Serial.print(F("\r\nTriangle"));
//        PS3.setRumbleOn(RumbleLow);
//      }
//      if (PS3.getButtonClick(CIRCLE)) {
//        Serial.print(F("\r\nCircle"));
//        PS3.setRumbleOn(RumbleHigh);
//      }
//      if (PS3.getButtonClick(CROSS))
//        Serial.print(F("\r\nCross"));
//      if (PS3.getButtonClick(SQUARE))
//        Serial.print(F("\r\nSquare"));
//
//      if (PS3.getButtonClick(UP)) {
//        Serial.print(F("\r\nUp"));
//        if (PS3.PS3Connected) {
//          PS3.setLedOff();
//          PS3.setLedOn(LED4);
//        }
//      }
//      if (PS3.getButtonClick(RIGHT)) {
//        Serial.print(F("\r\nRight"));
//        if (PS3.PS3Connected) {
//          PS3.setLedOff();
//          PS3.setLedOn(LED1);
//        }
//      }
//      if (PS3.getButtonClick(DOWN)) {
//        Serial.print(F("\r\nDown"));
//        if (PS3.PS3Connected) {
//          PS3.setLedOff();
//          PS3.setLedOn(LED2);
//        }
//      }
//      if (PS3.getButtonClick(LEFT)) {
//        Serial.print(F("\r\nLeft"));
//        if (PS3.PS3Connected) {
//          PS3.setLedOff();
//          PS3.setLedOn(LED3);
//        }
//      }
//
//      if (PS3.getButtonClick(L1))
//        Serial.print(F("\r\nL1"));
//      if (PS3.getButtonClick(L3))
//        Serial.print(F("\r\nL3"));
//      if (PS3.getButtonClick(R1))
//        Serial.print(F("\r\nR1"));
//      if (PS3.getButtonClick(R3))
//        Serial.print(F("\r\nR3"));
//
//      if (PS3.getButtonClick(SELECT)) {
//        Serial.print(F("\r\nSelect - "));
//        PS3.printStatusString();
//      }
//      if (PS3.getButtonClick(START)) {
//        Serial.print(F("\r\nStart"));
//        printAngle = !printAngle;
//      }
//    }
  }
  else{
    kinematic(0,0,0,0);
  }
}

//void loop() {
//  //  Serial.println(digitalRead(encB1));
//  //  Serial.println(enc4);
////  Falcon.writeMicroseconds(1701);
////  Serial.println(digitalRead(LIM4));
////  Serial.println(enc4);
//  updateCMPS();
//  calculatePos();
////  Serial.println(cmps.heading);
//  delay(1);
//}
