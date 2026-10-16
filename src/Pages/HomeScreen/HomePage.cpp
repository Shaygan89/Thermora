#include "Modules/Display/Display.h"
#include "Modules/Page System/Buttons.h"
#include "Modules/Page System/Page System.h"
#include "Modules/DHT/DHT.h"
//#include "SIM/SIM.h"

int gsmSignal = 0;

void HomeScreen() {
    printLine(0, 0, "HomeScreen      ");
    printLine(1, 3, String(temperature, 1));
    printChar(0, 0, 3);
    printLine(7, 3, String(humidity, 0));
    printChar(1, 6, 3);

    // static unsigned long lastUpdate = 0;

    // if (millis() - lastUpdate >= 1000) {
    //     lastUpdate = millis();
    //     gsmSignal = SIM_GetSignalLevel();

    //     Serial.println(gsmSignal);
    // }

    // if (gsmSignal == 4) {
    //     createCharacter(2, 2);
    // } else if (gsmSignal == 3) {
    //     createCharacter(2, 3);
    // } else if (gsmSignal == 2) {
    //     createCharacter(2, 4);
    // } else if (gsmSignal == 1) {
    //     createCharacter(2, 5);
    // } else {
    //     printLine(19, 0, "x");
    // }

    // if (gsmSignal != 0) {
    //     printChar(2, 19, 0);
    // }

    if (ButtonOkPressed()) {
        // clearDisplay();
        // SetPage(PAGE_SETTINGS);
    }
}
