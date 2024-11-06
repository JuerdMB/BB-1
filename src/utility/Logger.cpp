#include "utility/Logger.h"
#include "config.h"

LogLevel Logger::logLevel = LOG_LEVEL_DEBUG;
QueueHandle_t Logger::message_queue_ = nullptr;

void Logger::init()
{
    message_queue_ = xQueueCreate(LOGGER_MESSAGE_QUEUE_SIZE, sizeof(LogMessage));

    if (message_queue_ == nullptr)
    {
        // Handle error
        Serial.println("Failed to create log queue");
        return;
    }
}

void Logger::setLogLevel(LogLevel level)
{
    logLevel = level;
}

void Logger::enqueueMessage(LogLevel level, const char *levelStr, const char *fileName, const char *format, va_list args)
{
    // Only enqueue if message is of relevant LogLevel and queue was succesfully created
    if (logLevel <= level && message_queue_ != nullptr)
    {
        LogMessage message;
        message.level = level;
        message.timestamp = millis();
        strncpy(message.levelStr, levelStr, sizeof(message.levelStr) - 1);
        strncpy(message.fileName, fileName, sizeof(message.fileName) - 1);

        // Format the message
        vsnprintf(message.message, sizeof(message.message), format, args);

        // Enqueue the log message
        xQueueSend(message_queue_, &message, LOGGER_ENQUEUE_TIMEOUT);
    }
}

void Logger::debug(const char *fileName, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    enqueueMessage(LOG_LEVEL_DEBUG, "DEBUG", fileName, format, args);
    va_end(args);
}

void Logger::info(const char *fileName, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    enqueueMessage(LOG_LEVEL_INFO, "INFO", fileName, format, args);
    va_end(args);
}

void Logger::warn(const char *fileName, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    enqueueMessage(LOG_LEVEL_WARN, "WARN", fileName, format, args);
    va_end(args);
}

void Logger::error(const char *fileName, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    enqueueMessage(LOG_LEVEL_ERROR, "ERROR", fileName, format, args);
    va_end(args);
}