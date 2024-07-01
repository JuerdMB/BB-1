#include "MotorController.h"
#include "Arduino.h"

MotorController::MotorController(int motorLeftPWM, int motorRightPWM) : motorLeftPWM(motorLeftPWM), motorRightPWM(motorRightPWM)
{
}
void MotorController::initialize()
{
    pinMode(motorLeftPWM, OUTPUT);
    pinMode(motorRightPWM, OUTPUT);
}

void MotorController::setSpeed(float left, float right)
{
    analogWrite(motorLeftPWM, left);
    analogWrite(motorRightPWM, right);
}