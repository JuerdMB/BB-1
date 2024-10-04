/********************************************************************************
   BB-1 Self balancing robot by Juerd Mispelblom Beyer
   V1
 ********************************************************************************/

#include <Arduino.h>
#include "utility/shared_data.h"
#include "tasks/irs_task.h"
#include "tasks/mcs_task.h"

void setup()
{
  Serial.begin(115200);

  // Initialize Shared Data Structures
  SharedData::init();

  // Start IRS Task
  xTaskCreatePinnedToCore(
      irs_task,
      "IRS Task",
      4096,
      NULL,
      5,
      NULL,
      1);

  // Start Motor Control Task
  xTaskCreatePinnedToCore(
      mcs_task,
      "MSC Task",
      4096,
      NULL,
      10,
      NULL,
      0);
}

void loop()
{
}