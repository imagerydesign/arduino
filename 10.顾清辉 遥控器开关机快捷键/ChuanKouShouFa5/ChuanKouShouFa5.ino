
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

unsigned char hexdata[10] = {0x0D,0x2A,0x70,0x6F,0x77,0x3D,0x6F,0x6E,0x23,0x0D};

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

                           Serial.write(hexdata, 10);
                            

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
                           Serial.write(0x0D);
                           Serial.write(0x2A);
                           Serial.write(0x70);
                           Serial.write(0x6F);
                           Serial.write(0x77);
                           Serial.write(0x3D);
                           Serial.write(0x6F);
                           Serial.write(0x66);
                           Serial.write(0x66);
                           Serial.write(0x23);
                           Serial.write(0x0D);

                        
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
  

