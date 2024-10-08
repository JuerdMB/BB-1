#pragma once

#include <Wire.h>
#include <Adafruit_ICM20948.h>

class IMU
{
public:
    IMU();
    bool init();

private:
    void setDataReadyCallback(void (*callback)());
    volatile bool data_ready_;
    Adafruit_ICM20948 icm_;
};

