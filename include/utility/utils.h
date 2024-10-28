#pragma once

#include <Arduino.h>

struct Orientation
{
    Orientation(float roll_in, float pitch_in, float yaw_in) : roll(roll_in), pitch(pitch_in), yaw(yaw_in), timestamp(0){}
    Orientation() : roll(0.f), pitch(0.f), yaw(0.f), timestamp(0){}
    float roll;
    float pitch;
    float yaw;
    uint32_t timestamp;
};

struct RawIMUdata
{
    RawIMUdata() : accelerometer(Vector3<float>()), gyroscope(Vector3<float>()), magnetometer(Vector3<float>()) {}
    RawIMUdata(Vector3<float> acc_in, Vector3<float> gyr_in, Vector3<float> mag_in) : accelerometer(acc_in), gyroscope(gyr_in), magnetometer(mag_in) {}
    Vector3<float> accelerometer;
    Vector3<float> gyroscope;
    Vector3<float> magnetometer;
};

// IMU Data Structure
struct IMUData
{
    IMUData() : pitchAngle(0), pitchRate(0.f) {}
    float pitchAngle;
    float pitchRate;
};

// Wheel Encoder Data Structure
struct EncoderData
{
    EncoderData() : leftWheelSpeed(0.f), rightWheelSpeed(0.f){} 
    float leftWheelSpeed;
    float rightWheelSpeed;
};

struct ControlData
{
    ControlData() : linear(Vector3<float>()), angular(Vector3<float>()){}
    Vector3<float> linear;
    Vector3<float> angular;
};

template <typename T>
struct Vector3
{
    Vector3(T x_in, T y_in, T z_in): x(x_in), y(y_in), z(z_in){}
    Vector3(): x((T)0.), y((T)0.), z((T)0.){}
    T x;
    T y;
    T z;
};