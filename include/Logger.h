#pragma once

#include <Arduino.h>
#include <queue>
#include <mutex>

enum LogLevel {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
};

class Logger {
public:
    static Logger& getInstance();

    void log(LogLevel level, const char* message);
    void setLogLevel(LogLevel level);

private:
    Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    void printLog(LogLevel level, const char* message);

    LogLevel logLevel;
    std::mutex logMutex;
};