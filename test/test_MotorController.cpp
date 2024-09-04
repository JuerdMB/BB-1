#include <AUnit.h>
#include "MotorController.h"

test(MotorControllerInitialization) {
    MotorController motorController(5, 6);
    motorController.initialize();
    assertEqual(digitalPinToBitMask(5), OUTPUT);
    assertEqual(digitalPinToBitMask(6), OUTPUT);
}

test(MotorControllerSetSpeed) {
    MotorController motorController(5, 6);
    motorController.initialize();
    motorController.setSpeed(128, 255);
    assertEqual(analogRead(5), 128);
    assertEqual(analogRead(6), 255);
}

void setup() {
    Serial.begin(115200);
    aunit::TestRunner::run();
}

void loop() {
    // Empty loop as tests run in setup
}
