#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "data_types.h"
#include "shared_data.h"
#include "Logger.h"

void SharedData::init() {
    // Create a queue capable of holding 10 OrientationData items
    orientation_queue_ = xQueueCreate(10, sizeof(OrientationData));
    
    if (orientation_queue_ == NULL) {
        Logger::error("SharedData - Failed to create orientation queue.");
    }
}

bool SharedData::sendOrientationData(OrientationData orientationData){
    // Send to queue without blocking
    if (xQueueSend(orientation_queue_, &orientationData, portMAX_DELAY) != pdPASS) {
        Logger::warn("SharedData - Orientation queue is full, data lost.");
        return false;
    }
    return true;
}

 bool SharedData::receiveOrientationData(OrientationData *orientationData){
    if(xQueueReceive(orientation_queue_, orientationData, portMAX_DELAY) != pdPASS){
        Logger::debug("SharedData - No orientation data available in queue.");
        return false;
    }
    return true;
 }