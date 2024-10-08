#pragma once

#include <Arduino.h>

struct OrientationData
{
    double roll;
    double pitch;
    double yaw;
    uint32_t timestamp;
};

struct IMUdata
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