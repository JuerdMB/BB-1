#pragma once

#include <Arduino.h>

struct Orientation
{
    double roll;
    double pitch;
    double yaw;
    uint32_t timestamp;
};

struct RawIMUdata
{
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
    float mx;
    float my;
    float mz;
};

// IMU Data Structure
struct IMUData {
    float pitchAngle;
    float pitchRate;
};

// Wheel Encoder Data Structure
struct EncoderData {
    float leftWheelSpeed;
    float rightWheelSpeed;
};

struct Vector3{
    float x;
    float y;
    float z;
};

struct ControlData{
    Vector3 linear;
    Vector3 angular;
};