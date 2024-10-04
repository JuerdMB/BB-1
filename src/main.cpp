/********************************************************************************
   BB-1 Self balancing robot by Juerd Mispelblom Beyer
   V1
 ********************************************************************************/

#include <Arduino.h>
#include "shared_data.h"
#include "IMU.h"
#include "MotorDriver.h"
#include "Logger.h"

IMU imu;
MotorDriver motorDriver;

void setup()
{
  Serial.begin(115200);
  
  // Initialize shared data structures
  SharedData::init();

  // Start IMU & MotorDriver task
  imu.start();
  motorDriver.start();
}

void loop()
{
}