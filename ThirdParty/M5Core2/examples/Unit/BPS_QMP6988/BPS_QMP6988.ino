/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core2 sample source code
*                          配套  M5Core2 示例源代码
* Visit the website for more information: https://docs.m5stack.com/en/core/core2
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/core2
*
* describe: BPS_QMP6988.  压力传感器
* date: 2021/8/10
******************************************************************************
  Please connect to Port A,Read atmospheric pressure and display them on the display screen
  请连接端口A,读取大气压强并在显示屏上显示
*/
#include <M5Core2.h>
#include "Wire.h" //The BPS uses I2C comunication.
#include "UNIT_ENV.h"

QMP6988 qmp6988;

void setup() {
  M5.begin(true,false,true,true); //Init M5Core2 And the I2C port(21,22).  初始化 M5Core2和I2C端口(21,22)
}

void loop() {
  while (!qmp6988.init()){ //Init qmp6988.True if the init was successful, otherwise false.   初始化qmp6988,如果初始化成功返回1
    M5.lcd.setTextSize(1);  //Set the text size to 1.  设置文字大小为1
    M5.Lcd.println("\nCould not find a valid qmp6988 sensor, check wiring!");
  }
  M5.lcd.setTextSize(2);  //Set the text size to 2.  设置文字大小为2
  M5.lcd.setCursor(0,30);  //Set the cursor at (0,30).  设置光标在(0,30)处
  M5.lcd.fillScreen(BLACK); //Fill the screen with black (to clear the screen).  将屏幕填充满黑色(用来清屏)
  M5.Lcd.printf("Pressure:%0.2f",qmp6988.calcPressure());  //Screen print format string.  屏幕打印格式化字符串
  delay(2000);  //Delay 2s.  延迟2s
}