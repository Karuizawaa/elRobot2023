/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/tutorials/arduino-ethernet-shield-2
*/

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include "Servo.h"

Servo B3;
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
#define LIM9 47
#define LIM10 49

//Sensor optic
#define OPTIC 48

//motor stepper
#define PUL 33
#define DIR 35

//MOTOR1
#define pwmM1 4
#define cwM1  29
#define ccwM1 27

//MOTOR 2
#define pwmM2 4
#define cwM2  25
#define ccwM2 23

//MOTOR 3
#define pwmM3 6
#define cwM3  22
#define ccwM3 24

//MOTOR 4
#define pwmM4 7
#define cwM4  26
#define ccwM4 28
#define PWMMAX 200




// IMU 14 dan 15

// replace the MAC address below by the MAC address printed on a sticker on the Arduino Shield 2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// change the IP address, subnet mask, gateway's IP address, and DNS server's IP address depending on your network
IPAddress ip(192, 168, 0, 5);           //Setting IP Address
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress myDns(8, 8, 8, 8);
EthernetUDP Udp;

unsigned int localPort = 8888;
char packetBuffer[512];  // buffer to hold incoming packet,

long encoder;
char headStr[128];
unsigned long previousMillis = 0;
int pwm;
unsigned long int encFalcon, lastFalcon;

volatile float prevT;

int sekarang; // posisi step sekarang

#define KPf 1
#define KIf 1

// TODO: Declare something depending on your application

struct gy25 {
  char buffer[50];
  int counter;
  float heading;
} cmps;


void setup() {
  Serial.begin(9600);

  B3.attach(pwmM2);

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

  // initialize the Ethernet shield using the static IP address:
  Ethernet.begin(mac, ip, myDns, gateway, subnet);

  // initialize Udp communication on port
  Udp.begin(localPort);

}


void loop() {
  if (int n = Udp.parsePacket()) {
    Udp.read(packetBuffer, 3); // buffer to hold incoming packet,
    packetBuffer[n] = '\0';
    pwm = atoi(packetBuffer); //write microseconds
    toStep(lantaitoStep(pwm),200);
    servo(90);
    while(digitalRead(LIM10) == 1){
      //motor maju kebelakang
    }
    servo(0);
    while(digitalRead(LIM9) == 1){
      //motor maju kedepan
    }
    Udp.flush();
  }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1) {
    updateCMPS();
    previousMillis = currentMillis;
    Udp.beginPacket(IPAddress(192, 168, 0, 3), 5555);
    sprintf(headStr, "%d%d%d%d%d%d%d%d%d%d=%f#", digitalRead(LIM1), digitalRead(LIM2), digitalRead(LIM3),
            digitalRead(LIM4), digitalRead(LIM5), digitalRead(LIM6), digitalRead(LIM7), digitalRead(LIM8),
            digitalRead(LIM9), digitalRead(LIM10)), cmps.heading;
    Udp.endPacket();
  }
}
