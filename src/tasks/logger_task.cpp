#include "utility/Logger.h"
#include "config.h"

void loggerTask(void *parameters)
{
    LogMessage logMsg;

    while (true)
    {
        // Wait for a log message
        if (xQueueReceive(Logger::message_queue_, &logMsg, LOGGER_READ_TIMEOUT) == pdPASS)
        {
            // Print the log message
            Serial.print('[');
            Serial.print(logMsg.timestamp);
            Serial.print("][");
            Serial.print(logMsg.levelStr);
            Serial.print("][");
            Serial.print(logMsg.fileName);
            Serial.print("] ");
            Serial.println(logMsg.message);
        }
    }
}