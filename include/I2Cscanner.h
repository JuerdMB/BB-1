#pragma once

#include <Wire.h>
#include <Arduino.h>

class I2CScanner
{

public:
  I2CScanner()
  {
    // empty constructor
  }

  void init()
  {
    Wire.begin();

    Serial.println("I2C Scanner");
  }

  void run()
  {
    byte error, address;
    int nDevices = 0;

    Serial.println("Scanning...");

    for (address = 1; address < 127; address++)
    {
      Wire.beginTransmission(address);
      error = Wire.endTransmission();

      if (error == 0)
      {
        Serial.print("I2C device found at address 0x");
        if (address < 16)
          Serial.print("0");
        Serial.println(address, HEX);
        nDevices++;
      }
    }

    if (nDevices == 0)
      Serial.println("No I2C devices found\n");
    else
      Serial.println("done\n");

    delay(5000); // Wait 5 seconds between scans
  }
};
