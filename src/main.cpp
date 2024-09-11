/********************************************************************************
   BB-1 Self balancing robot by Juerd Mispelblom Beyer

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
#include "I2Cscanner.h"

#define motorLeftPWM 5
#define motorRightPWM 6

Logger &logger = Logger::getInstance();

IRS irs;

void setup()
{
  Serial.begin(115200); // Ensure this line is present

  logger.setLogLevel(LOG_LEVEL_DEBUG);

  logger.log(LOG_LEVEL_DEBUG, "System starting...");

  irs.initialize();

  // Setup tasks
  xTaskCreatePinnedToCore(IRS_Task, "IRS_Task", 10000, (void *)&irs, 1, NULL, 1); // Core 1: IRS Task
                                                                                  // xTaskCreatePinnedToCore(Motor_Control_Task, "MotorControl_Task", 10000, NULL, 1, NULL, 0);  // Core 0: Motor Control
}

void loop()
{
  // Empty loop. All is done inside the assigned tasks.
}