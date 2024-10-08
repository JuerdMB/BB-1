#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "utility/utils.h"
#include "utility/shared_data.h"
#include "utility/Logger.h"

QueueHandle_t SharedData::orientation_data_queue_ = QueueHandle_t();
QueueHandle_t SharedData::encoder_data_queue_ = QueueHandle_t();
QueueHandle_t SharedData::control_data_queue_ = QueueHandle_t();

void SharedData::init()
{
    // Create a queue capable of holding 10 OrientationData items
    orientation_data_queue_ = xQueueCreate(10, sizeof(OrientationData));
    if (orientation_data_queue_ == NULL)
    {
        Logger::error("SharedData - Failed to create orientation queue.");
    }

    // Create a queue capable of holding 10 OrientationData items
    encoder_data_queue_ = xQueueCreate(10, sizeof(EncoderData));
    if (encoder_data_queue_ == NULL)
    {
        Logger::error("SharedData - Failed to create encoder data queue.");
    }

    // Create a queue capable of holding 10 OrientationData items
    control_data_queue_ = xQueueCreate(10, sizeof(ControlData));
    if (control_data_queue_ == NULL)
    {
        Logger::error("SharedData - Failed to create control data queue.");
    }
}

bool SharedData::sendOrientationData(OrientationData orientationData)
{
    // Send to queue without blocking
    if (xQueueSend(orientation_data_queue_, &orientationData, portMAX_DELAY) != pdPASS)
    {
        Logger::warn("SharedData - Orientation queue is full, data lost.");
        return false;
    }
    return true;
}

bool SharedData::receiveOrientationData(OrientationData *orientationData)
{
    if (xQueueReceive(orientation_data_queue_, orientationData, portMAX_DELAY) != pdPASS)
    {
        Logger::debug("SharedData - No orientation data available in queue.");
        return false;
    }
    return true;
}