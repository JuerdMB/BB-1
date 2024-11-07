#pragma once

class PID
{
public:
    PID(float kP, float kI, float kD);
    PID();
    bool setGains(float kP, float kI, float kD);
    float compute(float input, float setPoint);

private:
    float kP_;
    float kI_;
    float kD_;
};
