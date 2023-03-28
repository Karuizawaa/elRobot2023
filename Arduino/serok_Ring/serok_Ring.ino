#include "ros.h"
#include "std_msgs/UInt8.h"
#include "std_msgs/Bool.h"
#include "Servo.h"

//PIN OUT
#define OPT 8
#define PUL 7
#define DIR 6
#define LED 13

//motor transfer ke launcher
#define PWMMAX 150
#define PWMM1 5
#define CW1   31
#define CCW1  33
#define LSDPN 25
#define LIMF 44
#define LIMB 46

#define SPL 800


Servo falcon;

uint8_t caseRobot;
bool l1;
long int sekarang; //posisi stepper sekarang
unsigned long curr;
short int lantai, prevLantai;
float falconSmoothed, falconPrev, setPoint;

void recCase(const std_msgs::UInt8& rec) {
  caseRobot = rec.data;
}

void lsat(const std_msgs::Bool& btlsat) {
  if(btlsat.data == 1){
    lantai++;
  }
  l1 = btlsat.data;
}

ros::NodeHandle nh;
ros::Subscriber<std_msgs::UInt8> subsCase ("case", recCase);
ros::Subscriber<std_msgs::Bool> sublsat ("lsatu", lsat);




void setup() {
  pinMode(OPT, INPUT);
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(LED, OUTPUT);

  pinMode(LIMF, INPUT_PULLUP);
  pinMode(LIMB, INPUT_PULLUP);
  pinMode(PWMM1, OUTPUT);
  pinMode(CW1, OUTPUT);
  pinMode(CCW1, OUTPUT);
  
  falcon.attach(12);

  nh.initNode();
  nh.subscribe(subsCase);
  nh.subscribe(sublsat);
//  kalibrasi();
}

void loop() {
  ROSCON();
  nh.spinOnce();
  if(caseRobot = 0){
    toStep(0,600);
    lantai = 0;
    digitalWrite(LED, 0);
  }
  if(caseRobot == 3){
    digitalWrite(LED, 1);
    toStep(lantai*SPL, 600);
    if(lantai > 10) lantai = 0;
    if(lantai != prevLantai){
      //dorong kedepan
      prevLantai = lantai;
    }
  }
}
