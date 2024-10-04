#include "shared_data.h"

orientation3D SharedData::orientation_ = orientation3D();
SemaphoreHandle_t SharedData::orientation_mutex_ = NULL;

void SharedData::init() {
    orientation_mutex_ = xSemaphoreCreateMutex();
}

void SharedData::setOrientation(const orientation3D& orientation) {
    xSemaphoreTake(orientation_mutex_, portMAX_DELAY);
    orientation_ = orientation;
    xSemaphoreGive(orientation_mutex_);
}

orientation3D SharedData::getOrientation() {
    xSemaphoreTake(orientation_mutex_, portMAX_DELAY);
    orientation3D orientation = orientation_;
    xSemaphoreGive(orientation_mutex_);
    return orientation;
}