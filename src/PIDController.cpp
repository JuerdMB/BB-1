#include "PIDController.h"

PIDController::PIDController(float Kp, float Ki, float Kd) : Kp(Kp), Ki(Ki), Kd(Kd), integral(0), previousError(0) {
    // Empty constructor
}

float PIDController::compute(float current, float target, float deltaTime) {
    float error = target - current;
    integral += error * deltaTime;
    float derivative = (error - previousError) / deltaTime;
    previousError = error;
    
    return Kp * error + Ki * integral + Kd * derivative;
}

void PIDController::setTunings(float Kp, float Ki, float Kd){
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
}