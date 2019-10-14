#define HWKG1 15           //红外开关接15号引脚
#define HWKG2 16           //红外开关接16号引脚
//unsigned long starttime = 0,endtime = 0;
//unsigned int time=0;
int Flag = 0;
void setup()
{
  pinMode(HWKG1,INPUT_PULLUP);                      //定义HWKG为带上拉输入引脚
  pinMode(HWKG2,INPUT_PULLUP);                      //定义HWKG为带上拉输入引脚
  
  Keyboard.begin();
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(HWKG1) == LOW && digitalRead(HWKG2) == HIGH && Flag == 0 )              //开关被挡住
       {
        Flag = 1;
       // starttime = millis();                    //开始计时
    
      }
    else if(digitalRead(HWKG1) == HIGH  && digitalRead(HWKG2) == HIGH && Flag == 1)
  {
    Flag = 2;
    
  }
  else if(digitalRead(HWKG1) == HIGH  && digitalRead(HWKG2) == LOW  && Flag == 2)
  {
     Flag = 3;
    /*
    endtime = millis();
    time = endtime - starttime;
    if (time >= 5000 )                      //一直有遮挡超过5秒，发一次按键
    {
      Flag = 0;
      Keyboard.press(' ');	//按空格键
      delay(50);
      Keyboard.releaseAll();
    }
    */
  }
   else if(digitalRead(HWKG1) == HIGH  && digitalRead(HWKG2) == HIGH && Flag == 3)
  {
     Flag = 0;
     Keyboard.press(' ');	//按空格键
    delay(50);
    Keyboard.releaseAll();
  }
  
}
