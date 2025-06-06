/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core2 sample source code
*                          配套  M5Core2 示例源代码
* Visit the website for more information: https://docs.m5stack.com/en/module/comx_gps
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/module/comx_gps
*
* describe: comx_gps.
* date: 2021/9/2
*******************************************************************************
  Use COM.GPS Module to get the coordinate data and time of the current location.
  使用 COM.GPS 模块获取当前位置的坐标数据和时间。
*/

#include <M5Core2.h>
#include <TinyGPS++.h>


// A sample NMEA stream.
const char *gpsStream =
  "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n";

// The TinyGPS++ object
TinyGPSPlus gps;


static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial2.available() > 0)
      gps.encode(Serial2.read());
  } while (millis() - start < ms);
  M5.Lcd.clear();
}

void displayInfo()
{
  M5.Lcd.setCursor(0, 40, 4);
  M5.Lcd.print(F("Latitude:    ")); 
  if (gps.location.isValid())
  {
    M5.Lcd.print(gps.location.lat(), 6);
    
  }
  else
  {
    M5.Lcd.print(F("INVALID"));
  }
  
  M5.Lcd.println();
  M5.Lcd.print(F("Longitude:    ")); 
  if (gps.location.isValid())
  {
    M5.Lcd.print(gps.location.lng(), 6);   
  }
  else
  {
    M5.Lcd.print(F("INVALID"));
  }
  
  M5.Lcd.println();
  M5.Lcd.print(F("Altitude:    ")); 
  if (gps.altitude.isValid())
  {
    M5.Lcd.print(gps.altitude.meters());
  }
  else
  {
    M5.Lcd.print(F("INVALID"));
  }

  M5.Lcd.println();
  M5.Lcd.print(F("Satellites:    "));
  if (gps.satellites.isValid())
  {
    M5.Lcd.print(gps.satellites.value());
  }
  else
  {
    M5.Lcd.print(F("INVALID"));
  }

  M5.Lcd.println();
  M5.Lcd.print(F("Date: "));
  if (gps.date.isValid())
  {
    M5.Lcd.print(gps.date.month());
    M5.Lcd.print(F("/"));
    M5.Lcd.print(gps.date.day());
    M5.Lcd.print(F("/"));
    M5.Lcd.print(gps.date.year());
  }
  else
  {
    M5.Lcd.print(F("INVALID"));
  }

  M5.Lcd.println();
  M5.Lcd.print(F("Time: "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) M5.Lcd.print(F("0"));
    M5.Lcd.print(gps.time.hour());
    M5.Lcd.print(F(":"));
    if (gps.time.minute() < 10) M5.Lcd.print(F("0"));
    M5.Lcd.print(gps.time.minute());
    M5.Lcd.print(F(":"));
    if (gps.time.second() < 10) M5.Lcd.print(F("0"));
    M5.Lcd.print(gps.time.second());
    M5.Lcd.print(F("."));
    if (gps.time.centisecond() < 10) M5.Lcd.print(F("0"));
    M5.Lcd.print(gps.time.centisecond());
  }
  else
  {
    M5.Lcd.print(F("INVALID"));
  }

}


void setup()
{
  M5.begin(true, true, true, false, kMBusModeInput);
  /*   kMBusModeOutput,powered by USB or Battery
  kMBusModeInput,powered by outside input need to fill in this Otherwise M5Core2 will not work properly
  由外部供电时此项必填,否则M5Core2将无法正常工作 */
  Serial2.begin(9600, SERIAL_8N1, 13, 14);
  M5.Lcd.setTextColor(GREEN, BLACK);

//  while (*gpsStream)
//    if (gps.encode(*gpsStream++))
//      displayInfo();
  
}

void loop()
{
  displayInfo();
  smartDelay(1000);
}
