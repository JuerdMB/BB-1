#include <Arduino.h>
#include "config.h"
#include "utility/shared_data.h"
#include "tasks/balancing_controller_task.h"
#include "tasks/communication_task.h"
#include "tasks/diagnostics_task.h"
#include "tasks/encoder_reader_task.h"
#include "tasks/imu_reader_task.h"
#include "tasks/motion_controller_task.h"

void setup()
{
    Serial.begin(115200);

    // Initialize Shared Data Queues
    SharedData::init();

    // Create tasks
    xTaskCreatePinnedToCore(
        imuReaderTask,
        "IMU Reading Task",
        TASK_STACK_SIZE,
        nullptr,
        IMU_READER_TASK_PRIORITY,
        nullptr,
        1 // Core 1
    );

    // xTaskCreatePinnedToCore(
    //     balancingControllerTask,
    //     "Balancing Controller Task",
    //     TASK_STACK_SIZE,
    //     nullptr,
    //     BALANCING_CONTROLLER_TASK_PRIORITY,
    //     nullptr,
    //     1 // Core 1
    // );

    // xTaskCreatePinnedToCore(
    //     motionControllerTask,
    //     "Motion Controller Task",
    //     TASK_STACK_SIZE,
    //     nullptr,
    //     MOTION_CONTROLLER_TASK_PRIORITY,
    //     nullptr,
    //     0 // Core 0
    // );

    // xTaskCreatePinnedToCore(
    //     encoderReadingTask,
    //     "Encoder Reading Task",
    //     TASK_STACK_SIZE,
    //     nullptr,
    //     ENCODER_READING_TASK_PRIORITY,
    //     nullptr,
    //     0 // Core 0
    // );

    // xTaskCreatePinnedToCore(
    //     communicationTask,
    //     "Communication Task",
    //     TASK_STACK_SIZE,
    //     nullptr,
    //     COMMUNICATION_TASK_PRIORITY,
    //     nullptr,
    //     0 // Core 0
    // );

    // xTaskCreatePinnedToCore(
    //     diagnosticsTask,
    //     "Diagnostics Task",
    //     TASK_STACK_SIZE,
    //     nullptr,
    //     DIAGNOSTICS_TASK_PRIORITY,
    //     nullptr,
    //     0 // Core 0
    // );

    // Delete setup and loop tasks
    vTaskDelete(NULL);
}

void loop()
{
}