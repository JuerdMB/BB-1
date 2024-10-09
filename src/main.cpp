/********************************************************************************
   BB-1 Self balancing robot by Juerd Mispelblom Beyer
   V1
 ********************************************************************************/

#include <Arduino.h>
#include "config.h"
#include "utility/shared_data.h"
#include "tasks/balancingControllerTask.h"
#include "tasks/communicationTask.h"
#include "tasks/diagnosticsTask.h"
#include "tasks/encoderReadingTask.h"
#include "tasks/imuReadingTask.h"
#include "tasks/motionControllerTask.h"

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
        imuReadingTask,
        "IMU Reading Task",
        TASK_STACK_SIZE,
        nullptr,
        IMU_READER_TASK_PRIORITY,
        nullptr,
        1 // Core 1
    );

    xTaskCreatePinnedToCore(
        balancingControllerTask,
        "Balancing Controller Task",
        TASK_STACK_SIZE,
        nullptr,
        BALANCING_CONTROLLER_TASK_PRIORITY,
        nullptr,
        1 // Core 1
    );

    xTaskCreatePinnedToCore(
        motionControllerTask,
        "Motion Controller Task",
        TASK_STACK_SIZE,
        nullptr,
        MOTION_CONTROLLER_TASK_PRIORITY,
        nullptr,
        0 // Core 0
    );

    xTaskCreatePinnedToCore(
        encoderReadingTask,
        "Encoder Reading Task",
        TASK_STACK_SIZE,
        nullptr,
        ENCODER_READING_TASK_PRIORITY,
        nullptr,
        0 // Core 0
    );

    xTaskCreatePinnedToCore(
        communicationTask,
        "Communication Task",
        TASK_STACK_SIZE,
        nullptr,
        COMMUNICATION_TASK_PRIORITY,
        nullptr,
        0 // Core 0
    );

    xTaskCreatePinnedToCore(
        diagnosticsTask,
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