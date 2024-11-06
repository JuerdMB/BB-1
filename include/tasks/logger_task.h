#pragma once

#include <Arduino.h>
#include "utility/Logger.h"

// Externally accessible task handle
extern TaskHandle_t loggerTaskHandle;

void loggerTask(void* parameters);