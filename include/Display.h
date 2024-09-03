#pragma once

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <queue>
#include <mutex>

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1

class Display {
public:
    Display();
    void initialize();
    void update(const String& message);
    static void displayTask(void *parameter);

private:
    Adafruit_SSD1306 display;
    std::queue<String> messageQueue;
    std::mutex queueMutex;
};