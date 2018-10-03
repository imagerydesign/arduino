/******************************************************************************
----------------本例程仅供学习使用，未经作者允许，不得用于其他用途。-----------
------------------------版权所有，仿冒必究！-----------------------------------
----------------1.开发环境:Arduino IDE,代码仅适合windows电脑-------------------
----------------2.测试使用开发板型号：Arduino Leonardo-------------------------
----------------3.单片机使用晶振：16M------------------------------------------
----------------4.淘宝网址：Ilovemcu.taobao.com--------------------------------
----------------------------epic-mcu.taobao.com--------------------------------
----------------5.作者：神秘藏宝室---------------------------------------------
******************************************************************************/
#define Hongwai 2			//向左按键
#define Buzzer 3			//向右按键

int Flag_up = 1;

void setup() 
{
  pinMode(Hongwai, INPUT_PULLUP);
  pinMode(Buzzer, OUTPUT);
  Keyboard.begin();
}
 
void loop() 
{
  if( ScanKey() == 1 && Flag_up)			//向左按键按下
  {
    Keyboard.press('A');		//向电脑发送向左按  键 按 下 的 指令
    digitalWrite(Buzzer,HIGH );
    delay(50);		
    Keyboard.releaseAll();						//向电脑发送按键    释放的指令
    Flag_up = 0;
  }
  
  else if(ScanKey() == 2)	//向右按键按下
  {
   // Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('S');	//向电脑发送向右按键按下的指令
    digitalWrite(Buzzer, LOW );
    delay(50);
    Keyboard.releaseAll();						//向电脑发送按键释放的指令
    Flag_up = 1;
  }
  
}

unsigned char ScanKey()			//按键扫描程序，返回键值
{
  
  
  if(Flag_up  && digitalRead(Hongwai) == HIGH )		//当Flag_up = 1并且按键按下时
  {
    //Flag_up = 0;										//清空Flag_up
    delay(20);											//延时去抖动
    if(Flag_up  && digitalRead(Hongwai) == HIGH )			//按键按下
    {
      return 1;											//返回键值1
    }
  }  
 else if(!Flag_up  && digitalRead(Hongwai) ==  LOW)			//按键按下
 {
   delay(20);
      if(digitalRead(Hongwai) == LOW)			//按键按下
    {
      return 2;											//返回键值1
    }										//返回键值1
 }
 else
  {
  return 0;
  }													//返回键值0
}








