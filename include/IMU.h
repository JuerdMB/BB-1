#pragma once

#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

class IMU {
public:
    IMU();
    bool initialize();
    float getPitch();
    float getYaw();
    bool update(float deltaTime);
    void calibrate();

private:
    Adafruit_ICM20948 icm;
    float pitch;
    float yaw;
    float roll;
    float pitch_previous;
    float roll_previous;
    float yaw_previous;

    const float ALPHA_PITCH = 0.98; // Tuning parameter for complementary filter
    const float ALPHA_YAW = 0.98;   // Tuning parameter for complementary filter
};