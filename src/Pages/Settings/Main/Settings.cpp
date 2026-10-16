#include "Modules/Display/Display.h"
#include "Modules/Page System/Buttons.h"
#include "Modules/Page System/Page System.h"

void Settings() {
    printLine(0, 0, "Settings   ");

    if (currentOption == 0) {
        printLine(0, 2, "SIMcard Config ");
        printLine(0, 3, "Display");
    } else if (currentOption == 1) {
        printLine(0, 2, "Display");
    }

    if (currentOption == 0 || currentOption == 1) {
        printLine(18, 2, "<-");
    }

    if (ButtonBackPressed()) {
        clearDisplay();
        SetPage(PAGE_HOME);
    }
    if (ButtonOkPressed()) {
        clearDisplay();
        SetPage(PAGE_SIMSETTINGS);
    }
    if(ButtonUpPressed()) {
        if (currentOption < 1) {
            currentOption += 1;
            clearDisplay();
        }
    }
    if(ButtonDownPressed()) {
        if (currentOption > 0) {
            currentOption -= 1;
            clearDisplay();
        }
    }
}