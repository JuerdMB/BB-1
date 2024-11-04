#include "utility/Logger.h"

LogLevel Logger::logLevel = LOG_LEVEL_DEBUG;

void Logger::setLogLevel(LogLevel level)
{
    logLevel = level;
}

void Logger::logMessage(LogLevel level, const char *levelStr, const char *functionName, const char *format, va_list args)
{
    if (logLevel <= level)
    {
        unsigned long timecode = millis();

        // Print timecode, log level, and function name
        Serial.print('[');
        Serial.print(timecode);
        Serial.print("][");
        Serial.print(levelStr);
        Serial.print("][");
        Serial.print(functionName);
        Serial.print("] ");

        // Format the message
        char buffer[256];
        vsnprintf(buffer, sizeof(buffer), format, args);
        Serial.println(buffer);
    }
}

void Logger::debug(const char *functionName, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    logMessage(LOG_LEVEL_DEBUG, "DEBUG", functionName, format, args);
    va_end(args);
}

void Logger::info(const char *functionName, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    logMessage(LOG_LEVEL_INFO, "INFO", functionName, format, args);
    va_end(args);
}

void Logger::warn(const char *functionName, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    logMessage(LOG_LEVEL_WARN, "WARN", functionName, format, args);
    va_end(args);
}

void Logger::error(const char *functionName, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    logMessage(LOG_LEVEL_ERROR, "ERROR", functionName, format, args);
    va_end(args);
}