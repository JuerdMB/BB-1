#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "definitions.h"

class SharedData {
public:
    static void init();

    static void setOrientation(const orientation3D& orientation);
    static orientation3D getOrientation();

private:
    static orientation3D orientation_;
    static SemaphoreHandle_t orientation_mutex_;
};