#include "Display.h"
#include <Wire.h> 
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

byte loading1[] = {B00000,B00000,B00000,B00000,B00001,B00000,B00000,B00000};
byte loading2[] = {B00000,B00000,B00000,B00000,B00000,B00001,B00010,B00000};
byte loading3[] = {B00000,B00000,B00000,B00000,B00000,B00000,B01110,B00000};
byte loading4[] = {B00000,B00000,B10000,B10000,B10000,B10000,B01100,B00000};
byte loading5[] = {B00000,B01110,B10001,B10001,B10000,B10000,B00000,B00000};
byte loading6[] = {B00000,B01110,B10001,B00001,B00001,B00001,B00000,B00000};
byte loading7[] = {B00000,B00000,B00001,B00001,B00001,B00001,B00010,B00000};
byte loading8[] = {B00000,B00000,B00000,B00000,B00000,B00001,B00110,B00000};
byte loading9[] = {B00000,B00000,B00000,B00000,B00000,B00000,B01100,B00000};
byte loading10[] = {B00000,B00000,B00000,B00000,B00000,B10000,B01000,B00000};
byte loading11[] = {B00000,B00000,B00000,B10000,B10000,B10000,B00000,B00000};
byte loading12[] = {B00000,B01000,B10000,B10000,B10000,B00000,B00000,B00000};
byte loading13[] = {B00000,B01110,B10001,B10000,B00000,B00000,B00000,B00000};
byte loading14[] = {B00000,B01110,B10001,B00001,B00001,B00001,B00000,B00000};
byte loading15[] = {B00000,B01110,B00001,B00001,B00001,B00001,B01110,B00000};
byte loading16[] = {B00000,B00110,B00001,B10001,B10001,B10001,B01110,B00000};
byte loading17[] = {B00000,B00000,B10000,B10001,B10001,B10001,B01110,B00000};
byte loading18[] = {B00000,B01000,B10000,B10000,B10000,B10000,B01110,B00000};
byte loading19[] = {B00000,B01100,B10000,B10000,B10000,B10000,B00000,B00000};
byte loading20[] = {B00000,B01110,B10000,B00000,B00000,B00000,B00000,B00000};
byte loading21[] = {B00000,B00010,B00001,B00000,B00000,B00000,B00000,B00000};
byte loading22[] = {B00000,B00000,B00000,B00001,B00000,B00000,B00000,B00000};
byte loadingBar1[] = {B10000,B10000,B10000,B10000,B10000,B10000,B10000,B10000};
byte loadingBar2[] = {B01000,B01000,B01000,B01000,B01000,B01000,B01000,B01000};
byte loadingBar3[] = {B00100,B00100,B00100,B00100,B00100,B00100,B00100,B00100};
byte loadingBar4[] = {B00010,B00010,B00010,B00010,B00010,B00010,B00010,B00010};
byte loadingBar5[] = {B00001,B00001,B00001,B00001,B00001,B00001,B00001,B00001};
byte temp[] = {B00100,B01010,B01010,B01010,B01110,B11111,B11111,B01110};
byte humi[] = {B00000,B00100,B01010,B10001,B10001,B10001,B01110,B00000};
byte simFull[] = {B00000,B00010,B00010,B00110,B00110,B01110,B01110,B11110};
byte simGood[] = {B00000,B00000,B00000,B00100,B00100,B01100,B01100,B11100};
byte simBad[] = {B00000,B00000,B00000,B00000,B00000,B01000,B01000,B11000};
byte simWorse[] = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B10000};
byte upperLine[] = {B11111,B00000,B00000,B00000,B00000,B00000,B00000,B00000};

byte* loadingFrames[] = {loading1, loading2, loading3, loading4, loading5, loading6, loading7, loading8, loading9, loading10,
loading11, loading12, loading13, loading14, loading15, loading16, loading17, loading18, loading19, loading20, loading21, loading22,};

byte* loadingBarFrames[] = {loadingBar1,  loadingBar3, loadingBar5};

byte* customCharacterIndex[] = {temp, humi, simFull, simGood, simBad, simWorse, upperLine};

int i = 0;
int c = 0;

bool BSODcantRestart = false;

void initDisplay() {
    Wire.begin();
    lcd.init();
    lcd.backlight();
}

void printLine(int column, int line, String text)
{
    lcd.setCursor(column, line);
    lcd.print(text);
}

void loadingBarAnimation() {
    if (i == 2) {
        lcd.print(" ");
        if (c == 19) {
            c = 0;
        } else {
            c++;
        }
        lcd.clear();
    }

    if (i == 2){
        i = 0;
    } else {
        i++;
    }

    lcd.createChar(0, loadingBarFrames[i]);
    lcd.setCursor(c, 3);
    lcd.write(byte(0));

}

void resetBacklightTimer() {
    
}

void clearDisplay() {
    lcd.clear();
}

void printChar(int charNumber, int charCursor1, int charCursor2) 
{
    lcd.setCursor(charCursor1, charCursor2);
    lcd.write(byte(charNumber));
}

void createCharacter(int charNumber, int charIndex)
{
    lcd.createChar(charNumber, customCharacterIndex[charIndex]);
}






void BSOD() {
    delay(25);
    lcd.backlight();
    if (BSODcantRestart) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("):");
        delay(25);
        lcd.setCursor(0, 1);
        lcd.print("Something went wrong");
        lcd.setCursor(5, 3);
        lcd.print("Cannot Boot");
        while(1);
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("):");
        delay(25);
        lcd.setCursor(0, 1);
        lcd.print("Something went wrong");
        lcd.setCursor(0, 2);
        lcd.print(",we need to restart");
        lcd.setCursor(2, 3);
        lcd.print("Restarting in 10");
        delay(950);
        lcd.setCursor(2, 3);
        lcd.print("Restarting in 9 ");
        delay(950);
        lcd.setCursor(2, 3);
        lcd.print("Restarting in 8 ");
        delay(950);
        lcd.setCursor(2, 3);
        lcd.print("Restarting in 7 ");
        delay(950);
        lcd.setCursor(2, 3);
        lcd.print("Restarting in 6 ");
        delay(950);
        lcd.setCursor(2, 3);
        lcd.print("Restarting in 5 ");
        delay(950);
        lcd.setCursor(2, 3);
        lcd.print("Restarting in 4 ");
        delay(950);
        lcd.setCursor(2, 3);
        lcd.print("Restarting in 3 ");
        delay(950);
        lcd.setCursor(2, 3);
        lcd.print("Restarting in 2 ");
        delay(950);
        lcd.setCursor(2, 3);
        lcd.print("Restarting in 1 ");
        delay(950);
        lcd.setCursor(1, 3);
        lcd.print("   Restarting... ");
        delay(50);
        esp_restart();
    }
//   delay(25);
//   lcd.setCursor(0, 2);
//   lcd.print("and we need to");
//   delay(25);
//   lcd.setCursor(0, 3);
//   lcd.print("restart");
//   delay(6000);
//   esp_restart();
}