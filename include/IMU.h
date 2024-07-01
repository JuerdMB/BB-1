#pragma once

#include "Arduino.h"
#include "MPU9250.h"
#include "Wire.h"

#define ALPHA_PITCH .95
#define ALPHA_ROLL .95
#define ALPHA_YAW .95

class IMU
{
private:
    MPU9250 mpu;
    float pitch, pitch_previous, roll, roll_previous, yaw, yaw_previous;

public:
    IMU();
    bool initialize();
    void calibrate();
    bool update(float deltaTime);
    float getPitch();
    float getYaw();
};