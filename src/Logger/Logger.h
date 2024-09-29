#pragma once

#include <Arduino.h>
#include "config.h"

enum LogLevel
{
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
}; static LogLevel logLevel = DEFAULT_LOG_LEVEL;

void setLogLevel(LogLevel level);
void logDebug(const char *message);
void logInfo(const char *message);
void logError(const char *message);