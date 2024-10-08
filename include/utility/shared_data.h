#pragma once

#include "freertos/FreeRTOS.h"
#include "freeRTOS/queue.h"
#include "utility/data_types.h"

class SharedData {
public:
    static void init();

    // Orientation Output from IMU
    static bool sendOrientationData(OrientationData orientationData);
    static bool receiveOrientationData(OrientationData *orientationData);

private:
    static QueueHandle_t orientation_queue_;
};