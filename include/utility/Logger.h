#pragma once
#include <Arduino.h>
#include <stdarg.h>

#define LOG_DEBUG(format, ...) Logger::debug(__FILE__, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) Logger::info(__FILE__, format, ##__VA_ARGS__)
#define LOG_WARN(format, ...) Logger::warn(__FILE__, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) Logger::error(__FILE__, format, ##__VA_ARGS__)

enum LogLevel
{
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
};

struct LogMessage
{
    unsigned long timestamp;
    LogLevel level;
    char levelStr[10];
    char fileName[100];
    char message[256];
};

class Logger
{
public:
    static void init();
    static void setLogLevel(LogLevel level);

    // Logging methods with variadic arguments
    static void debug(const char *fileName, const char *format, ...);
    static void info(const char *fileName, const char *format, ...);
    static void warn(const char *fileName, const char *format, ...);
    static void error(const char *fileName, const char *format, ...);
    
    // Queue that holds all log messages
    static QueueHandle_t message_queue_;


private:
    
    static LogLevel logLevel;

    // Helper method to format and print messages
    static void enqueueMessage(LogLevel level, const char *levelStr, const char *fileName, const char *format, va_list args);
    static void loggerTask(void* parameters);
};