/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core2 sample source code
*                          配套  M5Core2 示例源代码
* Visit the website for more information: https://docs.m5stack.com/en/unit/pahub
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/unit/pahub
*
* describe: PaHUB.
* date: 2021/8/31
*******************************************************************************
  Please connect to Port A, Use PaHUB Unit to expand multiple I2C devices and scan the I2C addresses of the slave devices in order.
  请连接端口A, 使用PaHUB Unit扩展多个I2C设备，并依次扫描从设备的I2C地址。
*/

#include <M5Core2.h>
#include "ClosedCube_TCA9548A.h"

#define FRONT 2

#define X_LOCAL 100
#define Y_LOCAL 35
#define X_OFFSET 160
#define Y_OFFSET 34

#define PaHub_I2C_ADDRESS	0x70

ClosedCube::Wired::TCA9548A tca9548a;

void setup()
{
	M5.begin();
  Wire.begin();
  tca9548a.address(PaHub_I2C_ADDRESS);  //Set the I2C address.  设置I2C地址
	M5.Lcd.setTextFont(4);
	M5.Lcd.setCursor(70, 0, 4);
	M5.Lcd.setTextColor(YELLOW,TFT_BLACK);
	M5.Lcd.println(("PaHUB Example"));
	M5.Lcd.setTextColor(TFT_WHITE,TFT_BLACK);
}

void loop()
{
	uint8_t returnCode = 0;
	uint8_t address;
  for( uint8_t channel=0; channel<TCA9548A_MAX_CHANNELS; channel++ ) {
    M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET*channel , FRONT);
    M5.Lcd.printf("                                                                ");
    M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET*channel , FRONT);
    M5.Lcd.printf("CH%d : ",channel);
    returnCode = tca9548a.selectChannel(channel);
    if( returnCode == 0 ) {
      for(address = 0x01; address < 0x7F; address++ ) {
        Wire.beginTransmission(address);
        returnCode = Wire.endTransmission();
        if (returnCode == 0) {
          Serial.print("I2C device = ");
          M5.Lcd.printf("0X%X  ",address);
        }
      }
    }
    delay(200);
  }
}
