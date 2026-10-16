#include "Buttons.h"
#include "Modules/Display/Display.h"
#include <Arduino.h>

// Pin numbers
#define BACK_PIN  14
#define UP_PIN    12
#define DOWN_PIN  13
#define OK_PIN    27

const uint32_t DEBOUNCE_TIME = 5;

struct Button
{
    uint8_t pin;

    bool currentState;
    bool lastReading;

    unsigned long lastChangeTime;

    bool pressedEvent;
};

Button backButton = {BACK_PIN};
Button upButton   = {UP_PIN};
Button downButton = {DOWN_PIN};
Button okButton   = {OK_PIN};

void UpdateButton(Button &btn)
{
    bool reading = digitalRead(btn.pin);

    // Input changed
    if(reading != btn.lastReading)
    {
        btn.lastChangeTime = millis();
    }

    // Stable for debounce period
    if((millis() - btn.lastChangeTime) > DEBOUNCE_TIME)
    {
        if(reading != btn.currentState)
        {
            btn.currentState = reading;

            // TTP223: touched = HIGH
            if(btn.currentState == HIGH)
            {
                btn.pressedEvent = true;
            }
        }
    }

    btn.lastReading = reading;
}

void Buttons_Init()
{
    // TTP223 outputs its own signal
    pinMode(BACK_PIN, INPUT);
    pinMode(UP_PIN, INPUT);
    pinMode(DOWN_PIN, INPUT);
    pinMode(OK_PIN, INPUT);

    // TTP223 idle state is LOW
    backButton.currentState = LOW;
    backButton.lastReading = LOW;

    upButton.currentState = LOW;
    upButton.lastReading = LOW;

    downButton.currentState = LOW;
    downButton.lastReading = LOW;

    okButton.currentState = LOW;
    okButton.lastReading = LOW;
}

void Buttons_Update()
{
    UpdateButton(backButton);
    UpdateButton(upButton);
    UpdateButton(downButton);
    UpdateButton(okButton);
}

bool ButtonBackPressed()
{
    if(backButton.pressedEvent)
    {
        Serial.println("BACK");
        resetBacklightTimer();
        backButton.pressedEvent = false;
        return true;
    }

    return false;
}

bool ButtonUpPressed()
{
    if(upButton.pressedEvent)
    {
        Serial.println("UP");
        resetBacklightTimer();
        upButton.pressedEvent = false;
        return true;
    }

    return false;
}

bool ButtonDownPressed()
{
    if(downButton.pressedEvent)
    {
        Serial.println("DOWN");
        resetBacklightTimer();
        downButton.pressedEvent = false;
        return true;
    }

    return false;
}

bool ButtonOkPressed()
{
    if(okButton.pressedEvent)
    {
        Serial.println("OK");
        resetBacklightTimer();
        okButton.pressedEvent = false;
        return true;
    }

    return false;
}