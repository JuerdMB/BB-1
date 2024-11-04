#include "motor_driver.h"
#include "config.h"
#include <Arduino.h>
#include "utility/Logger.h"

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

void MotorDriver::setMotorSpeeds(int motorLeftSpeed, int motorRightSpeed)
{
    // Bounds checking
    if (motorLeftSpeed < MOTORS_MIN_SPEED || motorLeftSpeed > MOTORS_MAX_SPEED)
    {
        int originalSpeed = motorLeftSpeed;
        motorLeftSpeed = constrain(motorLeftSpeed, MOTORS_MIN_SPEED, MOTORS_MAX_SPEED);
        LOG_INFO("BalanceController: Motor left speed out of bounds: %d, constraining to %d.", originalSpeed, motorLeftSpeed);
    }

    if (motorRightSpeed < MOTORS_MIN_SPEED || motorRightSpeed > MOTORS_MAX_SPEED)
    {
        int originalSpeed = motorRightSpeed;
        motorRightSpeed = constrain(motorRightSpeed, MOTORS_MIN_SPEED, MOTORS_MAX_SPEED);
        LOG_INFO("BalanceController: Motor right speed out of bounds: %d, constraining to %d.", originalSpeed, motorLeftSpeed);
    }

    if (motorLeftSpeed >= 0)
    {
        analogWrite(MOTOR_LEFT_A, motorLeftSpeed);
        analogWrite(MOTOR_LEFT_B, 0);
    }
    else
    {
        analogWrite(MOTOR_LEFT_A, 0);
        analogWrite(MOTOR_LEFT_B, abs(motorLeftSpeed));
    }

    if (motorRightSpeed >= 0)
    {
        analogWrite(MOTOR_RIGHT_A, motorRightSpeed);
        analogWrite(MOTOR_RIGHT_B, 0);
    }
    else
    {
        analogWrite(MOTOR_RIGHT_A, 0);
        analogWrite(MOTOR_RIGHT_B, abs(motorRightSpeed));
    }
}