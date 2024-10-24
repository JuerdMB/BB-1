#pragma once

#include <Arduino.h>
#include <stdarg.h>

enum LogLevel
{
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
};

class Logger
{
public:
    static void setLogLevel(LogLevel level);

    // Logging methods with variadic arguments
    static void debug(const char *format, ...);
    static void info(const char *format, ...);
    static void warn(const char *format, ...);    // Added warn method
    static void error(const char *format, ...);

private:
    static LogLevel logLevel;

    // Helper method to format and print messages
    static void logMessage(LogLevel level, const char *levelStr, const char *format, va_list args);
};