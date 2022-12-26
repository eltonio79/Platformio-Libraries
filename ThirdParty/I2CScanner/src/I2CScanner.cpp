#include "I2CScanner.h"
#include <Arduino.h>
#include <Wire.h>
#include <M5Core2.h>

void I2CScanner()
{
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextDatum(TL_DATUM);    //Set the alignment of the coord
    M5.Lcd.drawString("I2C scanner. Scanning ...", 10, 10, 4);    // Print the string 'hello' in font 2 at (160, 120)
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    Serial.println();
    Serial.println("I2C scanner. Scanning ...");

    byte count = 0;
    uint16_t yTextPos = 0;
    //Wire.begin();
    for (byte i = 0; i < 120; i++)
    {
        Wire.beginTransmission(i); // Begin I2C transmission Address (i)
        if (Wire.endTransmission() == 0)  // Receive 0 = success (ACK response) 
        {
            count++;
            yTextPos = 10 + (count * (M5.Lcd.fontHeight(4) + 5));

            M5.Lcd.setTextColor(WHITE);
            M5.Lcd.drawString("Found address:", 10, yTextPos, 4);
            M5.Lcd.setTextColor(GREEN);
            M5.Lcd.drawString("(0x", 193, yTextPos, 4);
            M5.Lcd.drawString(String(i, HEX), 230, yTextPos, 4);
            M5.Lcd.drawString(")", 257, yTextPos, 4);

            Serial.print("Found address: ");
            Serial.print(i, DEC);
            Serial.print(" (0x");
            Serial.print(i, HEX); // 7 bit address
            Serial.println(")");

            vTaskDelay(5 / portTICK_PERIOD_MS);
        }

        M5.Lcd.progressBar(YELLOW, 10, 203, 297, M5.Lcd.fontHeight(4), map(i, 0, 119, 0, 100));
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }

    yTextPos = 13 + ((count + 1) * (M5.Lcd.fontHeight(4) + 5));

    M5.Lcd.setTextColor(CYAN);
    M5.Lcd.drawString("Found ", 10, yTextPos, 4);
    M5.Lcd.drawString(String(count), 90, yTextPos, 4);
    M5.Lcd.drawString(" I2C device(s).", 105, yTextPos, 4);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.drawString(String(count), 90, yTextPos, 4);
    Serial.print("Found ");
    Serial.print(count, DEC); // numbers of devices
    Serial.println(" device(s).");
}
