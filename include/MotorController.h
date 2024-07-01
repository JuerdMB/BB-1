#pragma once

class MotorController
{
private:
    int motorLeftPWM, motorRightPWM;

public:
    MotorController(int motorLeftPWM, int motorRightPWM);
    void initialize();
    void setSpeed(float left, float right);
};