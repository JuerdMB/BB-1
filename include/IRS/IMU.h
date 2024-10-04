#pragma once

class IMU
{
public:
    IMU();
    void init();
    bool isDataReady();

private:
    void setupInterruptServiceRoutine();
    volatile bool data_ready_;
};