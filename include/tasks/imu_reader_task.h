#pragma once

#include <Arduino.h>

// Externally accessible task handle
extern TaskHandle_t imuReadingTaskHandle;

void imuReaderTask(void* parameters);

// ISR for IMU interrupt
void IRAM_ATTR imuInterruptHandler();