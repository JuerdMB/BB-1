/********************************************************************************
   BB-1 Self balancing robot by Juerd Mispelblom Beyer
   V1

   CONNECTIONS:
   Arduino D3  - Motor Driver PWM 1 Input
   Arduino D4  - Motor Driver DIR 1 Input
   Arduino D9  - Motor Driver PWM 2 Input
   Arduino D10 - Motor Driver DIR 2 Input
   Arduino GND - Motor Driver GND

 ********************************************************************************/

#define desiredLoopDuration 5

#include <Arduino.h>
#include "Logger.h"
#include "IRS.h"
#include "Ros.h"

#define motorLeftPWM 5
#define motorRightPWM 6

ros::NodeHandle nh;

IRS irs(&nh);

void setup()
{
  Serial.begin(115200);
  irs.initialize();
}

void loop()
{

}