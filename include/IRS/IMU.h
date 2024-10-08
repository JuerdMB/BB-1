#pragma once

#include <Wire.h>
#include <Adafruit_ICM20948.h>

class IMU
{
public:
    IMU();
    bool init();

    void readRawData();
    void updateFilteredOrientation();
    void publishFilteredOrientation();

private:
    void setDataReadyCallback(void (*callback)());
    volatile bool data_ready_;
    Adafruit_ICM20948 icm_;

    uint32_t last_imu_update_;
};
