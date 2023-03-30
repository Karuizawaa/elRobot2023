#include <SPI.h>
#include <Ethernet.h>

#define ROSSERIAL_ARDUINO_TCP
#include "ros.h"
#include "std_msgs/Int16.h"



byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// change the IP address, subnet mask, gateway's IP address, and DNS server's IP address depending on your network
IPAddress ip(192, 168, 0, 5);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress myDns(8, 8, 8, 8);

IPAddress serverIP(192, 168, 0, 3);
uint16_t serverPort = 11411;

ros::NodeHandle nh;
std_msgs::Int16 hitung;
ros::Publisher chatter("chatter", &hitung);

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  nh.getHardware() -> setConnection(serverIP, serverPort);
  Serial.print("IP = ");
  Serial.println(nh.getHardware()->getLocalIP());
  nh.initNode();
  nh.advertise(chatter);
  
  // put your setup code here, to run once:

}
int count;
void loop() {
  nh.spinOnce();
  if(nh.connected()){
    hitung.data = count;
    chatter.publish(&hitung);
    count++;
    if(count > 500) count = 0;  
    Serial.print("hello ");Serial.println(count);
  }
}
