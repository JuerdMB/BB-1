#include <Arduino.h>
#include "config.h"
#include "utility/shared_data.h"
#include "utility/Logger.h"

#include "tasks/balancing_controller_task.h"
#include "tasks/communication_task.h"
#include "tasks/imu_reader_task.h"
#include "tasks/motion_controller_task.h"
#include "tasks/logger_task.h"

void setup()
{
    Serial.begin(115200);

    // Wait for serial connection to start
    vTaskDelay(START_DELAY);

    // Initialize SharedData and Logger queues
    SharedData::init();
    Logger::init();

    // Tasks
    xTaskCreatePinnedToCore(
        imuReaderTask,
        "IMU Reading Task",
        TASK_STACK_SIZE,
        nullptr,
        IMU_READER_TASK_PRIORITY,
        nullptr,
        MAIN_CORE
    );

    xTaskCreatePinnedToCore(
        loggerTask,
        "Diagnostics Task",
        TASK_STACK_SIZE,
        nullptr,
        LOGGER_TASK_PRIORITY,
        nullptr,
        COMM_CORE
    );

    // xTaskCreatePinnedToCore(
    //     balancingControllerTask,
    //     "Balancing Controller Task",
    //     TASK_STACK_SIZE,
    //     nullptr,
    //     BALANCING_CONTROLLER_TASK_PRIORITY,
    //     nullptr,
    //     MAIN_CORE
    // );

    // xTaskCreatePinnedToCore(
    //     motionControllerTask,
    //     "Motion Controller Task",
    //     TASK_STACK_SIZE,
    //     nullptr,
    //     MOTION_CONTROLLER_TASK_PRIORITY,
    //     nullptr,
    //     MAIN_CORE
    // );

    // xTaskCreatePinnedToCore(
    //     encoderReadingTask,
    //     "Encoder Reading Task",
    //     TASK_STACK_SIZE,
    //     nullptr,
    //     ENCODER_READING_TASK_PRIORITY,
    //     nullptr,
    //     MAIN_CORE
    // );

    // xTaskCreatePinnedToCore(
    //     communicationTask,
    //     "Communication Task",
    //     TASK_STACK_SIZE,
    //     nullptr,
    //     COMMUNICATION_TASK_PRIORITY,
    //     nullptr,
    //     COMM_CORE
    // );

    // Delete setup and loop tasks
    vTaskDelete(NULL);
}

void loop()
{
}