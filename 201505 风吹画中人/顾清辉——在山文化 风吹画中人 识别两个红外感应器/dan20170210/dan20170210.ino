#define HWKG 11           //红外开关接11号引脚
#include <Keyboard.h>
unsigned long starttime = 0 , endtime = 0;
unsigned int time=0;
int Flag = 0;
void setup()
{
  
  pinMode(HWKG,INPUT_PULLUP);		//定义HWKG为带上拉输入引脚

  Keyboard.begin();
  Serial.begin(9600);
}

void loop()
{
    if(digitalRead(HWKG) == LOW  && Flag == 0)//开关被挡住
  {
    Flag = 1;
    starttime = millis();                    //开始计时
    
  }
  else if((digitalRead(HWKG) == HIGH ) && Flag == 1)
  {
    Flag = 0;
    Keyboard.press(' ');	//按空格键
    delay(50);
    Keyboard.releaseAll();
  }
  else if( (digitalRead(HWKG) == LOW ) && (Flag == 1))
  {
    endtime = millis();
    time = endtime - starttime;
    if (time >= 5000 )                      //一直有遮挡超过5秒，发一次按键
    {
      Flag = 0;
      Keyboard.press(' ');	//按空格键
      delay(50);
      Keyboard.releaseAll();
    }
  }
  
}
