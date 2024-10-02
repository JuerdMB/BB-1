#pragma once

class MotorDriver
{
public:
    MotorDriver();
    ~MotorDriver();
    void begin();
    void MotorDriverTask(void *pvParameters);

private:
    void setMotorSpeeds(int leftSpeed, int rightSpeed);
};