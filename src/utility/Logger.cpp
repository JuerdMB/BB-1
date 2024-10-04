#include "Logger.h"

LogLevel Logger::logLevel = DEFAULT_LOG_LEVEL;

void Logger::setLogLevel(LogLevel level)
{
    logLevel = level;
}

void Logger::logMessage(LogLevel level, const char *levelStr, const char *format, va_list args)
{
    if (logLevel <= level)
    {
        // Get the current time in milliseconds
        unsigned long timecode = millis();

        // Print timecode and log level
        Serial.print('[');
        Serial.print(timecode);
        Serial.print("][");
        Serial.print(levelStr);
        Serial.print("] ");

        // Format the message
        char buffer[256];
        vsnprintf(buffer, sizeof(buffer), format, args);
        Serial.println(buffer);
    }
}

void Logger::debug(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    logMessage(LOG_LEVEL_DEBUG, "DEBUG", format, args);
    va_end(args);
}

void Logger::info(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    logMessage(LOG_LEVEL_INFO, "INFO", format, args);
    va_end(args);
}

void Logger::warn(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    logMessage(LOG_LEVEL_WARN, "WARN", format, args);
    va_end(args);
}

void Logger::error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    logMessage(LOG_LEVEL_ERROR, "ERROR", format, args);
    va_end(args);
}