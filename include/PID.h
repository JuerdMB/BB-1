#pragma once

class PID{
    PID();
    ~PID();

    float compute(float input, float target);
};