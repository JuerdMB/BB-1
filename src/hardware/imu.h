#pragma once

#include <Wire.h>
#include <Adafruit_ICM20948.h>

class IMU
{
public:
    IMU();
    bool init();

    void retrieveRawData();
    void updateFilteredOrientation();
    void publishFilteredOrientation();

private:
    Adafruit_ICM20948 icm_;
    uint32_t last_imu_update_;
};

