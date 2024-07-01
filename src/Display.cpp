#include "Display.h"
#include "Logger.h"

Display::Display() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void Display::initialize() {
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
        Logger::getInstance().log(LOG_LEVEL_ERROR, "SSD1306 allocation failed");
        for(;;);
    }
    display.display();
    delay(2000); // Pause for 2 seconds
    display.clearDisplay();
}

void Display::displayTask(void *parameter) {
    Display* displayInstance = static_cast<Display*>(parameter);
    // Show stuff on the display
}