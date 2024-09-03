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
#include "IMU.h"
#include "MotorController.h"
#include "PIDController.h"
#include "Display.h"

#define motorLeftPWM 5
#define motorRightPWM 6

#define ICM_CS 10
#define ICM_SCK 13
#define ICM_MISO 12
#define ICM_MOSI 11


// float speed_setpoint;  // TODO zet controle op basis van pitch om in controle op basis van snelheid
float speed_setpoint;
float pitch_setpoint;
float yaw_setpoint;

IMU imu;
PIDController pitchPIDController(1000., 15000., 1000. /*Tune*/);
PIDController yawPIDController(1000., 15000., 1000. /*Tune*/);
MotorController motorController(motorLeftPWM, motorRightPWM);
Display display;

unsigned long previousTime;

void setup()
{
  Serial.begin(115200);
  imu.initialize();
  // motorController.initialize();
  // display.initialize();

  // Create tasks for secondary core
  // xTaskCreatePinnedToCore(controlTask, "Control Task", 10000, NULL, 1, &controlTaskHandle, 0);
  // xTaskCreatePinnedToCore(Display::displayTask, "Display Task", 10000, &display, 1, &displayTaskHandle, 1);
}

void loop()
{
  // Calculate time step
  long currentTime = millis();
  float deltaTime = (currentTime - previousTime) / 1000.0;
  previousTime = currentTime;

  // Read sensors and compute orientation
  if (imu.update(deltaTime))
  {
    float pitch = imu.getPitch();
    float yaw = imu.getYaw();

    Serial.print("Pitch:");
    Serial.print(pitch);
    Serial.print("Yaw:");
    Serial.print(yaw);

    // Calculate base motorspeed with pitch PID controller
    // float pitchCorrection = pitchPIDController.compute(pitch, pitch_setpoint, deltaTime);
    // float yawCorrection = yawPIDController.compute(yaw, yaw_setpoint, deltaTime);

    // float leftMotorSpeed = pitchCorrection - yawCorrection;
    // float rightMotorSpeed = pitchCorrection + yawCorrection;

    // motorController.setSpeed(leftMotorSpeed, rightMotorSpeed);

    // Constrain program to specified rate
    // unsigned int loopDuration = millis()-currentTime;
    // if(loopDuration < desiredLoopDuration)
    // delay(desiredLoopDuration-loopDuration);
  }
}