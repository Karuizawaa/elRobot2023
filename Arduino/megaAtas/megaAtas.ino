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

#include "Servo.h"

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
#define LIM9 47  //mentok belakang
#define LIM10 49 //mentok depan

//Sensor optic
#define OPTIC 22

//motor stepper
#define PUL 13
#define DIR 12

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
#define PWMMAX 200




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
int lantai = -1;
int prevLantai = -1;

int sekarang;
int velocity;
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
  B3.attach(7);
  falcon.attach(6);
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
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
  pinMode(OPTIC, INPUT);

  pinMode(pwmM2, OUTPUT);
  pinMode(cwM2, OUTPUT);
  pinMode(ccwM2, OUTPUT);
  
  // initialize the Ethernet shield using the static IP address:
  Ethernet.begin(mac, ip, myDns, gateway, subnet);

  // initialize Udp communication on port
  Udp.begin(localPort);
  kalibrasiIMU();
  kalibrasiStepper();
  
  
}

char masok;
void loop(){
  if(int n = Udp.parsePacket()){
    Udp.read(packetBuffer,6);  // buffer to hold incoming packet,
    packetBuffer[n] = '\0';
    if(packetBuffer[0] == '-') lantai = atoi(packetBuffer); //write microseconds
    if(packetBuffer[0] == '+') velocity = atoi(packetBuffer);
//    Serial.print("vel : ");
//    Serial.println(velocity);
  }
  Udp.flush();
  if(packetBuffer[0] == '1'){
    toStep(0,200);
    lantai = 0;
    prevLantai = 0;
    //servo naik
    servo(70);
    //kebelakang
    while(digitalRead(LIM9) != LOW){
//      Serial.print("lim belakangg " ); Serial.println(digitalRead(LIM9));
      motor2(-200);
    }
    motor2(0);
    //servo turun
    servo(-4);
  }
  updateCMPS();
//  Serial.println(digitalRead(OPTIC));
  if(lantai != prevLantai || masok == '1'){
    
    //kedepan
    while(digitalRead(LIM10) != LOW){
//      Serial.print("lim depan " ); Serial.println(digitalRead(LIM10));
      motor2(200);
    }
    motor2(0);
    //servo naik
    servo(70);
    //lantai begerak
    while(digitalRead(LIM9) != 0){
      toStepBareng(lantai, 200);
    }
    
    
    
    
    //kebelakang
//    while(digitalRead(LIM9) != LOW){
////      Serial.print("lim belakangg " ); Serial.println(digitalRead(LIM9));
//      motor2(-200);
//    }
    motor2(0);
    //servo turun
    servo(-4);
    masok = 'a';
    prevLantai = lantai;
  }
  gasFalcon(velocity);
}
