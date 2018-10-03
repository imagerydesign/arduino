
//遥控按键 A B
//接线 无线模块-RX 继电器-电脑主机 10

#define computer 2          //电脑主机
void setup()
{
  pinMode(computer, OUTPUT);
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

                            Serial.print(111);//开机
                            
                             digitalWrite(computer,LOW);
                             delay(100);						//延时100ms
                             digitalWrite(computer,HIGH);
                        }
                        break;
            case  12:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                           
                             Serial.print(111);//关机
                             digitalWrite(computer,LOW);
                             delay(100);						//延时100ms
                             digitalWrite(computer,HIGH);
                        }
                        break;

          }
        }
      }
    }
  }
}
  

