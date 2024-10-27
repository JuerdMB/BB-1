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
    Vector3<float> accelerometer;
    Vector3<float> gyroscope;
    Vector3<float> magnetometer;
};

// IMU Data Structure
struct IMUData
{
    float pitchAngle;
    float pitchRate;
};

// Wheel Encoder Data Structure
struct EncoderData
{
    float leftWheelSpeed;
    float rightWheelSpeed;
};

struct ControlData
{
    Vector3<float> linear;
    Vector3<float> angular;
};

template <typename T>
struct Vector3
{
private:
    T x;
    T y;
    T z;

public:
    Vector3(T x, T y, T z);
    Vector3();
};