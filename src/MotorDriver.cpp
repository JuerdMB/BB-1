#include "MotorDriver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "definitions.h"
#include "IMU.h"
#include "PID.h"

MotorDriver::MotorDriver() : PID_balance(PID()), PID_steer(PID()), PID_speed(PID())
{
}

void MotorDriver::start()
{
    // Pin the MotorDriver task to core 1
    xTaskCreatePinnedToCore(MotorDriverTask, "MotorDriver_Task", 4096, this, 10, NULL, 0);
}

void MotorDriver::init(){
    // init all stuff
}

void MotorDriver::MotorDriverTask(void *motorDriverInstance)
{
    // Cast motorDriverInstance parameter to MotorDriver* type
    MotorDriver *motorDriverPtr = static_cast<MotorDriver *>(motorDriverInstance);
    // Call the actual run function
    motorDriverPtr->run();
}

void MotorDriver::run()
{
    this->init();

    while (true)
    {
        // orientation3D orientation = sharedData->getOrientation();

        // float balance_output = PID_balance(orientation.p, 0);
        // float steer_output = PID_steer(orientation.h, 0);
        // float speed_output = PID_speed(velocity, 0);
    }
}