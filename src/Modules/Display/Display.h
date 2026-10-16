#pragma once

#include <Arduino.h>

void initDisplay();
void printLine(int column, int line, String text);
void loadingBarAnimation();
void resetBacklightTimer();
void clearDisplay();
void BSOD();
void printChar(int charNumber, int charCursor1, int charCursor2);
void createCharacter(int charNumber, int charIndex);

extern bool BSODcantRestart;