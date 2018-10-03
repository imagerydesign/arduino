//按键 A a B b
//接线 无线模块-RX 

void setup()
{
  Serial1.begin(9600);
  Keyboard.begin();
}
int anjian = 0;
void loop()
{
  

  if (Serial1.available() > 0) 
  {
    anjian = 0;
    anjian = Serial1.read();
    if(anjian == 6)
    {
      delay(5);
      anjian = Serial1.read();
      if(anjian == 170)
      {
        delay(5);
        anjian = Serial1.read();
        if(anjian == 170)
        {
          delay(5);
          anjian = Serial1.read();
          switch(anjian)
          {
           
            case  3:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //A-jian 
                             Keyboard.press('a');		//向电脑发送向
                            delay(50);		
                            Keyboard.releaseAll();
                            Serial.println("//A-jian ");
                        }
                        break;
            case  12:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //B-jian 
                             Keyboard.press('b');//向电脑发送向
                             	
                            delay(50);		
                            Keyboard.releaseAll();
                            Serial.println("//B-jian ");
                        }
                        break;

          }
        }
      }
    }
  }
}
  

