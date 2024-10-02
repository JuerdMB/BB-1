/********************************************************************************
   BB-1 Self balancing robot by Juerd Mispelblom Beyer
   V1
 ********************************************************************************/

#include <Arduino.h>
#include "IMU/IMU.h"
#include "MotorDriver/MotorDriver.h"

IMU imu;
MotorDriver motorDriver;

void setup()
{
  Serial.begin(115200);
  imu.begin();
  motorDriver.begin();
}

void loop()
{
  // Empty loop. All is done inside the assigned tasks.
}