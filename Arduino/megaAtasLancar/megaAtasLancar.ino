/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-ethernet-shield-2
 */

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include <Servo.h>

Servo B3, falcon;
#define pinB3 8

//encoder
#define encA1 2
#define encB1 46

#define encA2 3
#define encB2 44

#define encA3 18
#define encB3 42

#define encA4 19
#define encB4 41

//LIMIT base
#define LIM1 31 // belum fix
#define LIM2 33
#define LIM3 35
#define LIM4 37
#define LIM5 39
#define LIM6 41
#define LIM7 43
#define LIM8 45

//LIMIT atas
#define LIM10 47  //mentok depen
#define LIM9 49 //mentok blakang

//Sensor optic
#define OPTIC1 22
#define OPTIC2 3

//Sensor Prox
#define PROX1 7
#define PROX2 8

//motor stepper
#define PUL1 13
#define DIR1 12

#define PUL2 11
#define DIR2 9

//MOTOR1
#define pwmM1 3
#define cwM1  25
#define ccwM1 23

//MOTOR 2
#define pwmM2 4
#define cwM2  27
#define ccwM2 29

//MOTOR 3
#define pwmM3 6
#define cwM3  22
#define ccwM3 24

//MOTOR 4
#define pwmM4 9
#define cwM4  8
#define ccwM4 11
#define PWMMAX 255

#define LEDD1 28
#define LEDD2 30
#define LEDD3 32
#define LEDD4 34

#define STEPUP 24
#define STEPDOWN 26

// IMU 14 dan 15

// replace the MAC address below by the MAC address printed on a sticker on the Arduino Shield 2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// change the IP address, subnet mask, gateway's IP address, and DNS server's IP address depending on your network
IPAddress ip(192, 168, 0, 99);           //Setting IP Address
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress myDns(8, 8, 8, 8);
EthernetUDP Udp;

unsigned int localPort = 8888;
char packetBuffer[512];  // buffer to hold incoming packet,

char headStr[20];
int lantai = 0;
int prevLantai = 0;

int sekarang1, sekarang2;
int velocity;
int indexTiang, indexTiangPrev;
// TODO: Declare something depending on your application

struct gy25 {
  char buffer[50];
  int counter;
  float heading;
  int headInt;
} cmps;


long long int variable;



void setup() {
  Serial.begin(115200);
  falcon.attach(6);
  pinMode(PUL1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(PUL2, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(LIM1, INPUT_PULLUP);
  pinMode(LIM2, INPUT_PULLUP);
  pinMode(LIM3, INPUT_PULLUP);
  pinMode(LIM4, INPUT_PULLUP);
  pinMode(LIM5, INPUT_PULLUP);
  pinMode(LIM6, INPUT_PULLUP);
  pinMode(LIM7, INPUT_PULLUP);
  pinMode(LIM8, INPUT_PULLUP);
  pinMode(LIM9, INPUT_PULLUP);
  pinMode(LIM10, INPUT_PULLUP);
  pinMode(OPTIC1, INPUT);
  pinMode(OPTIC2, INPUT);
  pinMode(PROX1, INPUT);
  pinMode(PROX2 , INPUT);

  pinMode(pwmM2, OUTPUT);
  pinMode(cwM2, OUTPUT);
  pinMode(ccwM2, OUTPUT);

  pinMode(LEDD1, OUTPUT);
  pinMode(LEDD2, OUTPUT);
  pinMode(LEDD3, OUTPUT);
  pinMode(LEDD4, OUTPUT);

  pinMode(STEPUP, INPUT_PULLUP);
  pinMode(STEPDOWN, INPUT_PULLUP);
  
  // initialize the Ethernet shield using the static IP address:
  Ethernet.begin(mac, ip, myDns, gateway, subnet);

  // initialize Udp communication on port
  Udp.begin(localPort);
  kalibrasiIMU();
  kalibrasiStepper();

  for(int i = 0; i <= 400; i++){
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
    digitalWrite(PUL2, HIGH);
    digitalWrite(PUL1, HIGH);
    delayMicroseconds(200); // ganti delay untuk mempercepat motor
    digitalWrite(PUL2, LOW);
    digitalWrite(PUL1, LOW);
    delayMicroseconds(200); // ganti delay untuk mempercepat motor
  }
//  lantai = -200;
//  prevLantai = 0;
}
int melangkah;
char masok;
void loop(){
//  Serial.print(digitalRead(PROX1)); Serial.print("\t"); Serial.println(digitalRead(PROX2));
  updateCMPS();
//  digitalWrite(LEDD2, 1);
//  Serial.print(digitalRead(LIM9)); Serial.print("\t");Serial.println(digitalRead(LIM10));
  if(int n = Udp.parsePacket()){
    Udp.read(packetBuffer,6);  // buffer to hold incoming packet,
    packetBuffer[n] = '\0';
    if(packetBuffer[0] == '-') lantai = atoi(packetBuffer); //write microseconds
    if(packetBuffer[0] == '+') velocity = atoi(packetBuffer);
    if(packetBuffer[0] == ' ') indexTiang = atoi(packetBuffer);
    if(packetBuffer[0] == 'B') motor2(255);
    if(packetBuffer[0] == 'F') motor2(-255);
    if(packetBuffer[0] == 'S') motor2(0);
  }
  if(packetBuffer[0] == '1'){
    updateCMPS();
    while  (digitalRead(OPTIC1) != HIGH || digitalRead(OPTIC2) != HIGH) {
      digitalWrite(DIR1, LOW);
      digitalWrite(DIR2, LOW);
      if(digitalRead(OPTIC1) == LOW){
        digitalWrite(PUL1, HIGH);
      }
      if(digitalRead(OPTIC2) == LOW){
        digitalWrite(PUL2, HIGH);
      }
      delayMicroseconds(200);
      if(digitalRead(OPTIC1) == LOW){
        digitalWrite(PUL1, LOW);
      }
      if(digitalRead(OPTIC2) == LOW){
        digitalWrite(PUL2, LOW);
      }
      delayMicroseconds(200);
      
//      if(digitalRead(OPTIC1) == LOW){
//        digitalWrite(DIR1, LOW);
//        digitalWrite(PUL1, HIGH);
//        delayMicroseconds(200); // ganti delay untuk mempercepat motor
//        digitalWrite(PUL1, LOW);
//        delayMicroseconds(200); // ganti delay untuk mempercepat motor
//      }
//      if(digitalRead(OPTIC2) == LOW){
//        digitalWrite(DIR2, LOW);
//        digitalWrite(PUL2, HIGH);
//        delayMicroseconds(200); // ganti delay untuk mempercepat motor
//        digitalWrite(PUL2, LOW);
//        delayMicroseconds(200); // ganti delay untuk mempercepat motor
//      }
    }
    //kebelakang
    if(digitalRead(LIM9) != LOW){
      motor2(255);
      updateCMPS();
    }
    else{
      motor2(0);
      memset(packetBuffer, '\0', sizeof(packetBuffer));
    }
    
  }  
  if(lantai != prevLantai){
    if(lantai < -1001){
      //mentokin keatas
      motor2(50);
      while(digitalRead(PROX1) == 1 || digitalRead(PROX2) == 1){
        if(digitalRead(PROX1) == 1){
          digitalWrite(DIR1, HIGH);
          digitalWrite(PUL1, HIGH);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
          digitalWrite(PUL1, LOW);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
        }
        if(digitalRead(PROX2) == 1){
          digitalWrite(DIR2, HIGH);
          digitalWrite(PUL2, HIGH);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
          digitalWrite(PUL2, LOW);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
        }
      }
      unsigned long tunggu = millis();
      while(millis() - tunggu <= 200){
//        updateCMPS();
        motor2(-150);
      }
//      motor2(0);
//
      for(int i = 0; i <= 500; i++){
        digitalWrite(DIR1, LOW);
        if(i<200){
          digitalWrite(DIR2, LOW);
          digitalWrite(PUL2, HIGH);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
          digitalWrite(PUL2, LOW);
          delayMicroseconds(200); // ganti delay untuk mempercepat motor
        }
        digitalWrite(DIR1, LOW);
        digitalWrite(PUL1, HIGH);
        delayMicroseconds(200); // ganti delay untuk mempercepat motor
        digitalWrite(PUL1, LOW);
        delayMicroseconds(200); // ganti delay untuk mempercepat motor
      }
//      delay(300);
      while(digitalRead(LIM10) != LOW){
        updateCMPS();
        motor2(-255);
        if(int n = Udp.parsePacket()){
          Udp.read(packetBuffer,6);  // buffer to hold incoming packet,
          packetBuffer[n] = '\0';
          if(packetBuffer[0] == 'B') motor2(255);
          if(packetBuffer[0] == 'F') motor2(-255);
          if(packetBuffer[0] == 'S') motor2(0);
        }
      }
      //kebelakang
      while(digitalRead(LIM9) != 0){
        updateCMPS();
        motor2(255);
      }
      motor2(0);
      
      masok = 'a';
      prevLantai = lantai;
    }
    else{
      toStep(lantai, 200);
    }
    
  }
  if(packetBuffer[0] == 'G'){
    gakTurun();
    memset(packetBuffer, '\0', sizeof(packetBuffer));
  }
  
  if(indexTiang == 1){
    digitalWrite(LEDD1,1);
    digitalWrite(LEDD2,0);
    digitalWrite(LEDD3,0);
    digitalWrite(LEDD4,0);
  }
  else if(indexTiang == 2){
    digitalWrite(LEDD1,0);
    digitalWrite(LEDD2,1);
    digitalWrite(LEDD3,0);
    digitalWrite(LEDD4,0);
  }
  else if(indexTiang == 3){
    digitalWrite(LEDD1,0);
    digitalWrite(LEDD2,0);
    digitalWrite(LEDD3,1);
    digitalWrite(LEDD4,0);
  }
  else if(indexTiang == 4){
    digitalWrite(LEDD1,0);
    digitalWrite(LEDD2,0);
    digitalWrite(LEDD3,0);
    digitalWrite(LEDD4,1);
  }
  else{
    digitalWrite(LEDD1,0);
    digitalWrite(LEDD2,0);
    digitalWrite(LEDD3,0);
    digitalWrite(LEDD4,0);
  }
   
  gasFalcon(velocity);
}
