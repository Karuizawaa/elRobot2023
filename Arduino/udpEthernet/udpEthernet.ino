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

#define encA1 2
#define encB1 44
#define PWMM1 9
#define CW1   8
#define CCW1  7

// replace the MAC address below by the MAC address printed on a sticker on the Arduino Shield 2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// change the IP address, subnet mask, gateway's IP address, and DNS server's IP address depending on your network
IPAddress ip(192, 168, 0, 5);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress myDns(8, 8, 8, 8);
EthernetUDP Udp;

unsigned int localPort = 8888;
char packetBuffer[512];  // buffer to hold incoming packet,

long encoder;
char encoderStr[10];
unsigned long previousMillis = 0;
// TODO: Declare something depending on your application

void setup() {
  Serial.begin(9600);
  pinMode(PWMM1, OUTPUT);
  pinMode(CW1, OUTPUT);
  pinMode(CCW1, OUTPUT);
  // initialize the Ethernet shield using the static IP address:
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  Udp.begin(localPort);
  Udp.beginPacket(IPAddress(192,168,0,3),5555);
  // TODO: initialize something depending on your application
  
}


void loop(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      Udp.beginPacket(IPAddress(192,168,0,3),5555);
      encoder++;
      sprintf(encoderStr,"%d", encoder);
      if(encoder > 5000) encoder = 0;
      
      
      
    //  
      
      Udp.write(encoderStr);
      Udp.endPacket();
      
      if(int n = Udp.parsePacket()){
    //    strPWM = Udp.read();
          Udp.read(packetBuffer,7);  // buffer to hold incoming packet,
          packetBuffer[n] = '\0';
//          int pwm = atoi(packetBuffer);
          Serial.print("encoder\t: "); Serial.println(encoder);
          Serial.print("pwm\t: ");Serial.println(packetBuffer);Serial.println();
    //      Serial.println(n);
      }
      Udp.flush();
  }
  
//  receive
  
  
//  motor1(pwm);
  
}
