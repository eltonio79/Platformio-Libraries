/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core2 sample source code
*                          配套  M5Core2 示例源代码
* Visit the website for more information: https://docs.m5stack.com/en/unit/rs485
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/unit/rs485
*
* describe: rs485.
* date: 2021/8/30
*******************************************************************************
  Please connect to Port C,Use RS485 Unit for serial communication, continuously send "Hello", and display the received content on the screen.
  请连接端口 C,采用RS485单元串行通信，连续发送“Hello”，接收到的内容显示在屏幕上。
*/

#include <M5Core2.h>
#define RX_PIN      13
#define TX_PIN      14

#define X_OFF 160
#define Y_OFF 30

int i=0,s=0;

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(1);
  M5.Lcd.drawString("RS485 Unit test", 75, 3, 4);
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);  //Set the baud rate of serial port 2 to 115200,8 data bits, no parity bits, and 1 stop bit, and set RX to 13 and TX to 14.  设置串口二的波特率为115200,8位数据位,没有校验位,1位停止位,并设置RX为13,TX为14
}


void loop() {
  Serial2.write("Hello\n");

  if(Serial2.available()){
    M5.Lcd.print(char(Serial2.read()));
 }
  delay(100);
}
