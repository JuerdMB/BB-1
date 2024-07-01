#include "Logger.h"
#include <stdarg.h>

Logger::Logger() : logLevel(LOG_LEVEL_INFO) {}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex);
    logLevel = level;
}

void Logger::log(LogLevel level, const char* message) {
    if (level >= logLevel) {
        std::lock_guard<std::mutex> lock(logMutex);
        printLog(level, message);
    }
}

void Logger::printLog(LogLevel level, const char* message) {
    switch (level) {
        case LOG_LEVEL_DEBUG: Serial.print("[DEBUG] "); break;
        case LOG_LEVEL_INFO: Serial.print("[INFO] "); break;
        case LOG_LEVEL_WARN: Serial.print("[WARN] "); break;
        case LOG_LEVEL_ERROR: Serial.print("[ERROR] "); break;
    }
    Serial.println(message);
}