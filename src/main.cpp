/********************************************************************************
   BB-1 Self balancing robot by Juerd Mispelblom Beyer
   V1
 ********************************************************************************/

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

  // Initialize hardware components
  // Communication::init();
  // MotorDriver::init();
  // IMU::init();
  // WheelEncoders::init();
  SharedData::init();

  // Create tasks
    xTaskCreatePinnedToCore(
        imu_reader_task,
        "IMU Reading Task",
        TASK_STACK_SIZE,
        nullptr,
        IMU_READER_TASK_PRIORITY,
        nullptr,
        1 // Core 1
    );

    xTaskCreatePinnedToCore(
        balancing_controller_task,
        "Balancing Controller Task",
        TASK_STACK_SIZE,
        nullptr,
        BALANCING_CONTROLLER_TASK_PRIORITY,
        nullptr,
        1 // Core 1
    );

    xTaskCreatePinnedToCore(
        motion_controller_task,
        "Motion Controller Task",
        TASK_STACK_SIZE,
        nullptr,
        MOTION_CONTROLLER_TASK_PRIORITY,
        nullptr,
        0 // Core 0
    );

    xTaskCreatePinnedToCore(
        encoder_reader_task,
        "Encoder Reading Task",
        TASK_STACK_SIZE,
        nullptr,
        ENCODER_READING_TASK_PRIORITY,
        nullptr,
        0 // Core 0
    );

    xTaskCreatePinnedToCore(
        communication_task,
        "Communication Task",
        TASK_STACK_SIZE,
        nullptr,
        COMMUNICATION_TASK_PRIORITY,
        nullptr,
        0 // Core 0
    );

    xTaskCreatePinnedToCore(
        diagnostics_task,
        "Diagnostics Task",
        TASK_STACK_SIZE,
        nullptr,
        DIAGNOSTICS_TASK_PRIORITY,
        nullptr,
        0 // Core 0
    );
}

void loop()
{
}