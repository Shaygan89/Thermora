#include "Modules/Display/Display.h"
#include "Modules/Page System/Buttons.h"
#include "Modules/Page System/Page System.h"
#include "Modules/SIM/SIM.h"

void SimSettingsPage() {
    printLine(0, 0, "SIMcard             ");
    if (currentOption == 0) {
        printLine(0, 1, "                 ");
        printLine(18, 3, "<-");
        printLine(0, 2, "ADMIN: ");
        printLine(6, 2, String(phoneNumber));
        printLine(0, 3, "Set ADMIN number");
    } else if (currentOption == 1) {
        printLine(0, 1, "                 ");
        printLine(18, 2, "<-");
        printLine(0, 2, "Set ADMIN number");
        printLine(0, 3, "Send Test SMS");
    } else if (currentOption == 2) {
        printLine(0, 1, "                    ");
        printLine(18, 2, "<-");
        printLine(0, 2, "Send Test SMS");
        printLine(0, 3, "Make Test Call");
    } else if (currentOption == 3) {
        printLine(0, 1, "                    ");
        printLine(18, 3 , "<-");
        printLine(0, 2, "Send Test SMS");
        printLine(0, 3, "Make Test Call");
    }

    if (ButtonBackPressed()) {
        currentOption = 0;
        clearDisplay();
        SetPage(PAGE_SETTINGS);
    }
    if (ButtonOkPressed()){
        if (currentOption == 0 || currentOption == 1) {
            currentOption = 0;
            clearDisplay();
            SetPage(PAGE_ADMINNUMBERSET);
        } else if (currentOption == 2) {
            clearDisplay();
            printLine(0, 0, "Working on your   ");
            printLine(0, 1, "request...");
            if (sendSMS(phoneNumber, "Test Message from HUB")) {
                printLine(8, 3, "Done");
                delay (1000);
                clearDisplay();
            } else {
                printLine(0, 0, "Something went wrong");
                printLine(0, 1, "while working on");
                printLine(0, 2, "your request.");
                delay (7000);
                clearDisplay();
            }
        } else if (currentOption == 3) {
            clearDisplay();
            printLine(0, 0, "Working on your   ");
            printLine(0, 1, "request...");
            if (MakeCall(phoneNumber)) {
                printLine(8, 3, "Done");
                delay (1000);
                clearDisplay();
            } else {
                printLine(0, 0, "Something went wrong");
                printLine(0, 1, "while working on");
                printLine(0, 2, "your request.");
                delay (7000);
                clearDisplay();
            }
        }
    }
    if (ButtonUpPressed()) {
        if (currentOption < 3) {
            clearDisplay();
            currentOption++;
        }
    }
    if (ButtonDownPressed()) {
        if (currentOption > 0) {
            clearDisplay();
            currentOption--;
        }
    }
}
