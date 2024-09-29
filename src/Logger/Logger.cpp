#include "Logger.h"
#include <stdarg.h>

void setLogLevel(LogLevel level)
{
    logLevel = level;
}

void logDebug(const char *message) {
    if(logLevel<=LOG_LEVEL_DEBUG){
        Serial.print("[DEBUG] ");
        Serial.println(message);
    }
}
void logInfo(const char *message) {
    if(logLevel<=LOG_LEVEL_INFO){
        Serial.print("[INFO] ");
        Serial.println(message);
    }
}
void logError(const char *message) {
    if(logLevel<=LOG_LEVEL_ERROR){
        Serial.print("[ERROR] ");
        Serial.println(message);
    }
}