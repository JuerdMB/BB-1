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

#include <Arduino.h>
#include "IMU.h"

IMU imu;


void setup()
{
  Serial.begin(115200); // Ensure this line is present

  imu.start();
  // motorDriver.start();
}

void loop()
{
  // Empty loop. All is done inside the assigned tasks.
}