/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core2 sample source code
*                          配套  M5Core2 示例源代码
* Visit the website for more information: https://docs.m5stack.com/en/core/core2
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/core2
*
* describe: QRcode.  创建二维码
* date: 2021/7/26
*******************************************************************************
*/

#include <M5Core2.h>

void setup() {
  M5.begin(); //Init M5Core2.  初始化M5Core2
  M5.Lcd.qrcode("http://www.m5stack.com",0,0,150,6);  //Create a QR code with a width of 150 QR code with version 6 at (0, 0).  在(0,0)处创建一个宽为150二维码版本为6的二维码
  //Please select the appropriate QR code version according to the number of characters.  请根据字符数量选择合适的二维码版本
}

void loop() {
}
