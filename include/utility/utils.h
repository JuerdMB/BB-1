#pragma once

#include <Arduino.h>

struct Vector3{
    float x;
    float y;
    float z;
};

struct Orientation
{
    double roll;
    double pitch;
    double yaw;
    uint32_t timestamp;
};

struct RawIMUdata
{
    Vector3 accelerometer;
    Vector3 gyroscope;
    Vector3 magnetometer;
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

struct ControlData{
    Vector3 linear;
    Vector3 angular;
};