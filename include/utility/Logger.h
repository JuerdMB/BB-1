#pragma once
#include <Arduino.h>
#include <stdarg.h>

#define LOG_DEBUG(format, ...) Logger::debug(__PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) Logger::info(__PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LOG_WARN(format, ...) Logger::warn(__PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) Logger::error(__PRETTY_FUNCTION__, format, ##__VA_ARGS__)

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
    static void debug(const char *functionName, const char *format, ...);
    static void info(const char *functionName, const char *format, ...);
    static void warn(const char *functionName, const char *format, ...);
    static void error(const char *functionName, const char *format, ...);

private:
    static LogLevel logLevel;

    // Helper method to format and print messages
    static void logMessage(LogLevel level, const char *levelStr, const char *functionName, const char *format, va_list args);
};