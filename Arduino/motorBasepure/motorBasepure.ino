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

#define encA 2
#define encB 44
#define PWMM 6
#define CW   7
#define CCW  8

// replace the MAC address below by the MAC address printed on a sticker on the Arduino Shield 2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// change the IP address, subnet mask, gateway's IP address, and DNS server's IP address depending on your network
IPAddress ip(192, 168, 0, 11);           //Setting IP Address
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress myDns(8, 8, 8, 8);
EthernetUDP Udp;

unsigned int localPort = 8888;
char packetBuffer[512];  // buffer to hold incoming packet,

long encoder;
char encoderStr[10];
unsigned long previousMillis = 0;
int pwm;
// TODO: Declare something depending on your application

void setup() {
  Serial.begin(9600);
  pinMode(encA, INPUT);
  pinMode(encB, INPUT);
  
  pinMode(PWMM, OUTPUT);
  pinMode(CW, OUTPUT);
  pinMode(CCW, OUTPUT);
  // initialize the Ethernet shield using the static IP address:
  Ethernet.begin(mac, ip, myDns, gateway, subnet);

  // initialize Udp communication on port
  Udp.begin(localPort);
  attachInterrupt(digitalPinToInterrupt(encA), readEnc, RISING);
  // TODO: initialize something depending on your application
  
}


void loop(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1) {
      previousMillis = currentMillis;
      Udp.beginPacket(IPAddress(192,168,0,3),5555);
      
      if(int n = Udp.parsePacket()){
          Udp.read(packetBuffer,5);  // buffer to hold incoming packet,
          packetBuffer[n] = '\0';
          pwm = atoi(packetBuffer);
      }
      Udp.flush();
  }
  motor(100);
  
}
