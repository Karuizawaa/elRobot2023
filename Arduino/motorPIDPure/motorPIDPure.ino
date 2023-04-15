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
//#include <EthernetTcp.h>

#define encA 3
#define encB 4
#define PWMM 6
#define CW   7
#define CCW  8

#define KP 0.7
#define KI 0

// replace the MAC address below by the MAC address printed on a sticker on the Arduino Shield 2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// change the IP address, subnet mask, gateway's IP address, and DNS server's IP address depending on your network
IPAddress ip(192, 168, 0, 12);           //Setting IP Address
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress myDns(8, 8, 8, 8);
EthernetUDP Udp;

unsigned int localPort = 5555;
char packetBuffer[512];  // buffer to hold incoming packet,

long int encoder, lastEncoder;
String kirim;
unsigned long previousMillis = 0;
float setVel;

unsigned long int prevT;
volatile float vFilt, vPrev, sum;

// TODO: Declare something depending on your application

void setup() {
//  Serial.begin(115200);
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
}

void loop(){
//  Serial.println(encoder);
//  Udp.beginPacket(IPAddress(192,168,0,55),5555);
//  Udp.print(encoder);
//  Udp.endPacket();
//
//  if(int n = Udp.parsePacket()){
//      Udp.read(packetBuffer,5);  // buffer to hold incoming packet,
//      packetBuffer[n] = '\0';
//      setVel = atof(packetBuffer);
////      Serial.println(packetBuffer);
//  }
//  Udp.flush();
//  motor(pwm);
  setVel = 2 *M_PI* 1;
  closedloopctl(setVel);
//  motor(50);
}
