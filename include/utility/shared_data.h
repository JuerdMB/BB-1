#pragma once

#include "freertos/FreeRTOS.h"
#include "freeRTOS/queue.h"
#include "utility/utils.h"

class SharedData {
public:
    static void init();

    // Orientation Output from IMU task
    static bool sendOrientationData(OrientationData orientationData);
    static bool receiveOrientationData(OrientationData *orientationData);

    // Encoder Output from encoder task
    static bool sendEncoderData(EncoderData encoderData);
    static bool receiveEncoderData(EncoderData *encoderData);

    // Control output from micro-ros callbacks
    static bool sendControlData(ControlData controlData);
    static bool receiveControlData(ControlData *controlData);

private:
    static QueueHandle_t orientation_data_queue_;
    static QueueHandle_t encoder_data_queue_;
    static QueueHandle_t control_data_queue_;
};