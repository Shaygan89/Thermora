#include <Arduino.h>
#include "Modules/Display/Display.h"
#include "Modules/DHT/DHT.h"
#include "Modules/Boot/Boot.h"
#include "Modules/Page System/Page System.h"
#include "Modules/Page System/Buttons.h"

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

void touchTask(void *pvParameters)
{
    while(1)
    {
        // Update all buttons
        Buttons_Update();
        vTaskDelay(2 / portTICK_PERIOD_MS);
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

  xTaskCreatePinnedToCore(
        touchTask,
        "touch reading",
        1024,
        NULL,
        1,
        NULL,
        0
  );
  
}

void loop() {
  UpdateCurrentPage();
  updateDHT();
}
