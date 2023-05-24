/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 */

#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int64.h>


#define encA 3
#define encB 4
#define PWMM 6
#define CW   7
#define CCW  8

#define KP 4.3
#define KI 2.3

long int encoder, lastEncoder;
String kirim;
unsigned long previousMillis = 0;
float setVel;

unsigned long int prevT;
volatile float vFilt, vPrev, sum;

ros::NodeHandle  nh;

void setVelCB (const std_msgs::Float32& msg){
  setVel = msg.data;
}

ros::Subscriber<std_msgs::Float32> subVel ("radps1", setVelCB);


std_msgs::Int64 encmsgs;
ros::Publisher pubEnc("enc1", &encmsgs);

char hello[13] = "hello world!";

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(pubEnc);
  nh.subscribe(subVel);
}

void loop()
{
  pubEnc.publish( &encmsgs );
  nh.spinOnce();
  delay(500);
}
