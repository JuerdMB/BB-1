#include "motor_driver.h"
#include "config.h"
#include <Arduino.h>

MotorDriver::MotorDriver()
{
}

bool MotorDriver::init()
{
    pinMode(MOTOR_LEFT_A, OUTPUT);
    pinMode(MOTOR_LEFT_B, OUTPUT);
    pinMode(MOTOR_RIGHT_A, OUTPUT);
    pinMode(MOTOR_RIGHT_B, OUTPUT);
    return true;
}

void MotorDriver::setMotorSpeeds(float left, float right)
{
    analogWrite(MOTOR_LEFT_A, left);
    analogWrite(MOTOR_LEFT_B, left);
    analogWrite(MOTOR_RIGHT_A, right);
    analogWrite(MOTOR_RIGHT_B, right);
}