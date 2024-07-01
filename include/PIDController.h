#pragma once

class PIDController {
private:
    float Kp, Ki, Kd;
    float integral;
    float previousError;

public:
    PIDController(float Kp, float Ki, float Kd);
    float compute(float current, float target, float deltaTime);
    void setTunings(float Kp, float Ki, float Kd);
};
