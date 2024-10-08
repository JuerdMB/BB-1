#include "MotorControlSystem/MotorDriver.h"
#include "config.h"
#include <Arduino.h>

MotorDriver::MotorDriver()
{
}

bool MotorDriver::init()
{
    pinMode(MOTOR_LEFT_PIN, OUTPUT);
    pinMode(MOTOR_RIGHT_PIN, OUTPUT);
    return true;
}

void MotorDriver::setMotorSpeeds(float left, float right)
{
    analogWrite(MOTOR_LEFT_PIN, left);
    analogWrite(MOTOR_RIGHT_PIN, right);
}