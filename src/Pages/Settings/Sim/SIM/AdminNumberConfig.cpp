#include "Modules/Page System/Buttons.h"
#include "Modules/Page System/Page System.h"
#include "Modules/Display/Display.h"
#include "Modules/SIM/SIM.h"
#include <EEPROM.h>

int currentSelectedDigit = 2;
int currentSelectedDigitCursor = 7;
bool previousNumberSave = false;

char previousPhoneNumber[12];

void AdminNumberSet() {
    printLine(0, 0, "Edit number:");
    printLine(5, 1, String(phoneNumber));
    createCharacter(6, 6);
    printChar(6, currentSelectedDigitCursor, 2);

    if (!previousNumberSave) {strcpy(previousPhoneNumber, phoneNumber); previousNumberSave = true;}

    if (ButtonOkPressed()) {
        printLine(5, 2, "             ");
        if (currentSelectedDigitCursor == 15) {
            currentSelectedDigit = 2;
            currentSelectedDigitCursor = 7;
            clearDisplay();
            EEPROM.put(0, phoneNumber);
            EEPROM.commit();
            previousNumberSave = false;
            clearDisplay();
            printLine(0, 0, "Sending confirmation");
            printLine(0, 1, "SMS...");
            sendSMS(phoneNumber, "You are ADMIN now, you can communicate with device sucessfully");
            SetPage(PAGE_SIMSETTINGS);
        }
        if (currentSelectedDigitCursor < 15) {
            currentSelectedDigit++;
            currentSelectedDigitCursor++;
        }
    }

    if (ButtonUpPressed()) {
        if (phoneNumber[currentSelectedDigit] < '9') {
        phoneNumber[currentSelectedDigit]++;
        } else if (phoneNumber[currentSelectedDigit] == '9') {
        phoneNumber[currentSelectedDigit] = '0';
        }
    }

    if (ButtonDownPressed()) {
        if (phoneNumber[currentSelectedDigit] > '0') {
        phoneNumber[currentSelectedDigit]--;
        } else if (phoneNumber[currentSelectedDigit] == '0') {
        phoneNumber[currentSelectedDigit] = '9';
        }
    }

    if (ButtonBackPressed()) {
        if (currentSelectedDigit == 2) {
        clearDisplay();
        strcpy(phoneNumber, previousPhoneNumber);
        previousNumberSave = false;
        SetPage(PAGE_SIMSETTINGS);
        } else {
            printLine(5, 2, "             ");
            currentSelectedDigit--;
            currentSelectedDigitCursor--;
        }
    }
}