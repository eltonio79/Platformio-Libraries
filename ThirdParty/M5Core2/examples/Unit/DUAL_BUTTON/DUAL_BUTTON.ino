/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core2 sample source code
*                          配套  M5Core2 示例源代码
* Visit the website for more information: https://docs.m5stack.com/en/core/core2
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/core2
*
* describe: Button_Two.  双按键
* date: 2021/8/9
*******************************************************************************
  Please connect to Port B,Read the button status of BUTTON Unit and display it on the screen
  请连接端口B,读取按键的状态并在显示屏上显示
  if you don't have M5GO BOTTOM, you need change the pinMode and the digitalRead to 33、32, But you will not be able to use any I2C operations.
  如果你没有M5GO BOTTOM，你需要改变pinMode和digitalRead到 33,32,但是你将不能使用任何I2C操作.
*/
#include <M5Core2.h>

int last_value1 = 0,last_value2 = 0;
int cur_value1 = 0,cur_value2 = 0;

void setup() {
  M5.begin(); //Init M5Core2.  初始化 M5Core2
  pinMode(36, INPUT); //set pin mode to input.设置引脚模式为输入模式
  pinMode(26, INPUT);
  M5.Lcd.setTextColor(YELLOW);  //Set the font color to yellow.  设置字体颜色为黄色
  M5.Lcd.setTextSize(2);  //Setting the Font size.  设置字号大小
  M5.Lcd.setCursor(80, 0);  //Set the cursor position to (80,0).  将光标位置设置为(80,0)
  M5.Lcd.println("Button example");
  M5.Lcd.setTextColor(WHITE);
}

void loop() {
  cur_value1 = digitalRead(36); // read the value of BUTTON.  读取22号引脚的值
  cur_value2 = digitalRead(26);
  M5.Lcd.setCursor(90,25); M5.Lcd.print("Btn.1  Btn.2");
  M5.Lcd.setCursor(0,45); M5.Lcd.print("Value: ");
  M5.Lcd.setCursor(0,85); M5.Lcd.print("State: ");
  if(cur_value1 != last_value1){
    M5.Lcd.fillRect(85,45,75,85,BLACK); //Draw a black rectangle 75 by 85 at (85,45).  在(85,45)处绘制宽75,高85的黑色矩形
    if(cur_value1==0){
      M5.Lcd.setCursor(95,45); M5.Lcd.print("0"); // display the status
      M5.Lcd.setCursor(95,85); M5.Lcd.print("pre");
    }
    else{
      M5.Lcd.setCursor(95,45); M5.Lcd.print("1"); // display the status
      M5.Lcd.setCursor(95,85); M5.Lcd.print("rel");
    }
    last_value1 = cur_value1;
  }
  if(cur_value2 != last_value2){
    M5.Lcd.fillRect(170,45,75,85,BLACK);
    if(cur_value2==0){
      M5.Lcd.setCursor(185,45); M5.Lcd.print("0"); // display the status
      M5.Lcd.setCursor(185,85); M5.Lcd.print("pre");
    }
    else{
      M5.Lcd.setCursor(185,45); M5.Lcd.print("1"); // display the status
      M5.Lcd.setCursor(185,85); M5.Lcd.print("rel");
    }
    last_value2 = cur_value2;
  }
}
