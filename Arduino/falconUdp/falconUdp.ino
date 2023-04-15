/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/tutorials/arduino-ethernet-shield-2
*/

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include "Servo.h"

Servo falcon;

#define encZ 3
#define PPR 1

#define KPf 1400
#define KIf 10

// replace the MAC address below by the MAC address printed on a sticker on the Arduino Shield 2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// change the IP address, subnet mask, gateway's IP address, and DNS server's IP address depending on your network
IPAddress ip(192, 168, 0, 15);           //Setting IP Address
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress myDns(8, 8, 8, 8);
EthernetUDP Udp;

unsigned int localPort = 5555;
char packetBuffer[512];  // buffer to hold incoming packet,

unsigned long encoder, lastEncoder, prevT_i, prevEncoder, RPM_i, prevT;
unsigned long previousMillis = 0;
int velocity;
volatile float sum;
// TODO: Declare something depending on your application

void setup() {
  Serial.begin(9600);

  falcon.attach(6);
  pinMode(encZ, INPUT);

  // initialize the Ethernet shield using the static IP address:
  Ethernet.begin(mac, ip, myDns, gateway, subnet);

  // initialize Udp communication on port
  Udp.begin(localPort);
//  attachInterrupt(digit/alPinToInterrupt(encZ), readEnc, RISING);
  // TODO: initialize something depending on your application

}


void loop() {
  if(int n = Udp.parsePacket()){
      Udp.read(packetBuffer,512);  // buffer to hold incoming packet,
      packetBuffer[n] = '\0';
      velocity = atof(packetBuffer); //write microseconds
  }
  Udp.flush();
  gasFalcon(velocity);
}
