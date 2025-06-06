/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core2 sample source code
*                          配套  M5Core2 示例源代码
* Visit the website for more information: https://docs.m5stack.com/en/core/core2
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/core2
*
* describe: RFID.
* date: 2021/8/19
*******************************************************************************
  Please connect to Port A,Use the RFID Unit to read the Fudan card ID and display the ID on the screen.
  请连接端口A,使用RFID Unit 读取ID卡并在屏幕上显示。
*/

#include <M5Core2.h>
#include "MFRC522_I2C.h"

MFRC522 mfrc522(0x28);   // Create MFRC522 instance.  创建MFRC522实例

void setup() {
  M5.begin(); //Init M5Core2.  初始化M5Core2
  M5.lcd.setTextSize(2);  //Set the text size to 2.  设置文字大小为2
  M5.Lcd.println("MFRC522 Test");
  Wire.begin(); //Wire init, adding the I2C bus.  Wire初始化, 加入i2c总线

  mfrc522.PCD_Init(); // Init MFRC522.  初始化 MFRC522
  M5.Lcd.println("Please put the card\n\nUID:");
}

void loop() {
  M5.Lcd.setCursor(40,47);
  if (!mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial()) {  //如果没有读取到新的卡片
    delay(200);
    return;
  }
  M5.Lcd.fillRect(42,47,320,20,BLACK);
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    M5.Lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    M5.Lcd.print(mfrc522.uid.uidByte[i], HEX);
  }
  M5.Lcd.println("");
}