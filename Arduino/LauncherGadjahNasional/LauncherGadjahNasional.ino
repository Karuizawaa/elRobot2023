/* Bismillah juara 1
 * 
 * KRAI - BARELANG V
 * Kendali launcher
 */

#include <ADS1X15.h>
#include <Servo.h>
#include <EEPROM.h>

#define SWCW  9
#define SWCCW 11
#define SAVEPOS 12

#define PWMM 6
#define CW   7
#define CCW  8

#define KP 0.3

#define TOTALTIANG 8

ADS1115 ADS(0x48);

unsigned long previousMillis = 0;
float setVel;

unsigned long int prevT;
volatile float vFilt, vPrev, sum;
unsigned long tunggmillis;

void setup() 
{
  // Pins D5 and D6 - 31.4 kHz
  TCCR0B = 0b00000001; // x1
  TCCR0A = 0b00000001; // phase correct
  pinMode(SWCW, INPUT_PULLUP);
  pinMode(SWCCW, INPUT_PULLUP);
  pinMode(SAVEPOS, INPUT_PULLUP);

  pinMode(PWMM, OUTPUT);
  pinMode(CW, OUTPUT);
  pinMode(CCW, OUTPUT);
  
  Serial.begin(115200);
  ADS.begin();
//  cariTiang();
}


void loop() 
{
  ADS.setGain(0);
  int16_t val_0 = ADS.readADC(0);
  float f = ADS.toVoltage(1);  // voltage factor
  Serial.println(val_0);
  
  closedloopctl(gotoTiang(5));
//  Serial.println(gotoTiang(4));
  delay(1);
}
