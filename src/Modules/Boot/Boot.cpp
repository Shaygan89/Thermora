#include "Boot.h"
#include "Modules/Display/Display.h"
#include "Modules/DHT/DHT.h"
#include "Modules/NRF/NRF.h"
#include "Modules/SIM/SIM.h"
#include "Modules/Page System/Buttons.h"
#include <EEPROM.h>
#include "esp_system.h"

bool bootFinished = false;
bool uiTestMode = false;
int simCheckPhase = 0;

bool dhtOk = false;
bool nrfOK = false;
bool simOK = false;
bool simCardOK = false;
bool simConnectivityOK = false;

unsigned long startMillis = 0;

void Boot() {
    Serial.begin(115200);
    delay(200);
    Serial.println("Serial Begin");
    Serial.printf("Reset reason: %d\n", esp_reset_reason());

    EEPROM.begin(64);
    delay(10);

    EEPROM.get(0, phoneNumber);
    if (phoneNumber[0] != '0' || phoneNumber[1] != '9') {
    strcpy(phoneNumber, "09352441497");
    EEPROM.put(0, phoneNumber);
    EEPROM.commit();
    bootFinished = true;
    BSOD();
    }

    Buttons_Init();
    Serial.println("Button Initialize");

    delay(100);
    startMillis = millis();
    while(millis() - startMillis < 200) {
        Buttons_Update();
        if (ButtonBackPressed()) {
            uiTestMode = true;
        }
    }
    
    if (initDHT()) {
        dhtOk = true;
    } else {
        bootFinished = true;
        BSODcantRestart = true;
        BSOD();
        dhtOk = false;
    }
    Serial.println("DHT CHECK");
    
    Serial.println("Before NRF");

    bool result = initNRF();

    Serial.println("After NRF");

    if(result) {
        nrfOK = true;
    } else {
        bootFinished = true;
        BSODcantRestart = true;
        BSOD();
        nrfOK = false;
    }

    if (!uiTestMode) {
        Serial.println("NRF CHECK");

        if(SIM_ModuleTest()) {
            simOK = true;
        } else {
            bootFinished = true;
            BSODcantRestart = true;
            clearDisplay();
            printLine(0, 0, "Simcard Failure!");
            simOK = false;
        }

        Serial.println("SIM CHECK Phase 1");

        simCheckPhase = 1;

        if (!bootFinished) {
            if(SIM_SIMCardTest()) {
                simCardOK = true;
            } else {
                clearDisplay();
                printLine(0, 0, "No simCard!");
                bootFinished = true;
                simCardOK = false;
            }
        }

        Serial.println("SIM CHECK Phase 2");

        simCheckPhase = 2;

        if (!bootFinished) {
            if(SIM_NetworkTest()) {
                simConnectivityOK = true;
            } else {
                bootFinished = true;
                clearDisplay();
                printLine(0, 0, "Cannot get any");
                printLine(0, 1, "signals!");
                delay(3000);
                simConnectivityOK = false;
            }
        }
    }

    //SendNRF();

    //delay(500);
    bootFinished = true;
}