#pragma once

class MotorDriver
{
public:
    MotorDriver();
    bool init();
    void setMotorSpeeds(float left, float right);

private:
};