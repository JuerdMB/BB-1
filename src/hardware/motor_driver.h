#pragma once

class MotorDriver
{
public:
    MotorDriver();
    bool init();
    void setMotorSpeeds(int motorLeftSpeed, int motorRightSpeed);

private:
};