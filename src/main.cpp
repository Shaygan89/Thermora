#include <Arduino.h>
#include "Modules/Display/Display.h"
#include "Modules/DHT/DHT.h"
#include "Modules/Boot/Boot.h"
#include "Modules/Page System/Page System.h"

TaskHandle_t animationTaskHandle;

void animationTask(void *pvParameters)
{
    printLine(0, 0, "Booting...");
    while(!bootFinished)
    {
        loadingBarAnimation();

        vTaskDelay(60 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void setup() {
  initDisplay();
  
  xTaskCreatePinnedToCore(
        animationTask,
        "LCD Animation",
        2048,
        NULL,
        1,
        NULL,
        0
  );

  Boot();
  clearDisplay();
  createCharacter(0, 0);
  createCharacter(1, 1);
  
}

void loop() {
  UpdateCurrentPage();
  updateDHT();
}
