/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core2 sample source code
*                          配套  M5Core2 示例源代码
* Visit the website for more information: https://docs.m5stack.com/en/core/core2
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/core2
*
* describe: NTP TIME.
* date: 2021/8/3
*******************************************************************************/

#include <M5Core2.h>
#include <WiFi.h>
#include "time.h"

// Set the name and password of the wifi to be connected.  配置所连接wifi的名称和密码
const char* ssid       = "M5";
const char* password   = "123456";

const char* ntpServer = "time1.aliyun.com"; //Set the connect NTP server.  设置连接的NTP服务器
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

void printLocalTime(){  //Output current time.  输出当前时间
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){ //Return 1 when the time is successfully obtained.  成功获取到时间返回1
    M5.Lcd.println("Failed to obtain time");
    return;
  }
  M5.Lcd.println(&timeinfo, "%A, %B %d \n%Y %H:%M:%S");  //Screen prints date and time.  屏幕打印日期和时间
}

void setup(){
  M5.begin(); //Init M5Core2.  初始化 M5Core2
  M5.Lcd.setTextSize(2);  //Set the font size to 2.  设置字号大小为2
  M5.Lcd.printf("\nConnecting to %s", ssid);
  WiFi.begin(ssid, password); //Connect wifi and return connection status.  连接wifi并返回连接状态
  while(WiFi.status() != WL_CONNECTED) { //If the wifi connection fails.  若wifi未连接成功
    delay(500); //delay 0.5s.  延迟0.5s
    M5.Lcd.print(".");
  }
  M5.Lcd.println("\nCONNECTED!");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); //init and get the time.  初始化并设置NTP
  printLocalTime();
  WiFi.disconnect(true);  //Disconnect wifi.  断开wifi连接
  WiFi.mode(WIFI_OFF);  //Set the wifi mode to off.  设置wifi模式为关闭
  delay(20);
}

void loop(){
  delay(1000);
  M5.Lcd.setCursor(0,47); //Set the cursor at (0,0).  设置光标位于(0,0)处
  printLocalTime();
}