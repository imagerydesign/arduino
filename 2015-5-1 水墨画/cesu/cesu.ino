

#define KEY1 2        //前面的开关是2#引脚
#define KEY2 3        //后面的开关是3#引脚
 
unsigned long starttime = 0 , endtime = 0;
unsigned int time=0;
int Level1 = ;
int Level2 = ;
int Level3 = ;
int Flag = 0;
void setup()
{
  
  pinMode(KEY1,INPUT_PULLUP);		//定义KEY为带上拉输入引脚
  pinMode(KEY2,INPUT_PULLUP);		//定义KEY为带上拉输入引脚
   Keyboard.begin();
  Serial.begin(9600);
}
void loop()
{
   if(digitalRead(KEY1) == LOW && Flag = 0)			//前面开关被挡住
  {
        Flag = 1;
        starttime = millis();                    //开始计时
  
  }
  if(digitalRead(KEY2) == LOW && Flag = 1)			//后面开关被挡住
  {
        Flag = 0;
        endtime = millis();                    //结束计时
        if(endtime > starttime)
        {
          time = endtime - starttime;
          if(time > 0 && time < Level1)
          {
            Keyboard.press(KEY_RIGHT_ARROW);	//
            delay(150);
            Keyboard.releaseAll();
          }
          else if(time > Level1 && time < Level2)
          {
            Keyboard.press(KEY_RIGHT_ARROW);	//
            delay(150);
            Keyboard.releaseAll();
          }
          else if(time > Level2 )
          {
            Keyboard.press(KEY_RIGHT_ARROW);	//
            delay(150);
            Keyboard.releaseAll();
          }
        }
  }
  Serial.print("Time: ");
  time = millis();
  //prints time since program started
  Serial.println(time);
  // wait a second so as not to send massive amounts of data
  delay(1000);
}
