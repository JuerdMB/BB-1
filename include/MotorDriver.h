#pragma once

#include "PID.h"

class MotorDriver
{
public:
    MotorDriver();
    void start();
    void run();

private:
    // Initialization functions
    static void MotorDriverTask(void *motorDriverInstance);
    void init();

    // Runtime functions
    void setMotorSpeeds(int leftSpeed, int rightSpeed);

    // Objects
    PID PID_balance;
    PID PID_steer;
    PID PID_speed;
};