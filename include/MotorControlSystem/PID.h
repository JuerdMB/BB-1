#pragma once

class PID{
    public:
    PID();
    float compute(float input, float setPoint);
    private:
};