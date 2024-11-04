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
    orientation_data_queue_ = xQueueCreate(10, sizeof(Orientation));
    if (orientation_data_queue_ == NULL)
    {
        LOG_ERROR("SharedData - Failed to create orientation queue.");
    }

    // Create a queue capable of holding 10 OrientationData items
    encoder_data_queue_ = xQueueCreate(10, sizeof(EncoderData));
    if (encoder_data_queue_ == NULL)
    {
        LOG_ERROR("SharedData - Failed to create encoder data queue.");
    }

    // Create a queue capable of holding 10 OrientationData items
    control_data_queue_ = xQueueCreate(10, sizeof(ControlData));
    if (control_data_queue_ == NULL)
    {
        LOG_ERROR("SharedData - Failed to create control data queue.");
    }
}

bool SharedData::sendOrientationData(Orientation orientationData)
{
    // Send to queue without blocking
    if (xQueueSend(orientation_data_queue_, &orientationData, 0) != pdPASS)
    {
        LOG_DEBUG("SharedData - Orientation queue is full, removing from tail.");
        return false;
    }
    return true;
}

bool SharedData::receiveOrientationData(Orientation *orientationData)
{
    if (xQueueReceive(orientation_data_queue_, orientationData, 0) != pdPASS)
    {
        LOG_DEBUG("SharedData - No orientation data available in queue.");
        return false;
    }
    return true;
}