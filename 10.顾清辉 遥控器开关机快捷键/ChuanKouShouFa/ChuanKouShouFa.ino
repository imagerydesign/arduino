
*/
以下是之前的代码，有个地方要改一下：

把“发送快捷键A”改成向串口发送 开投影的代码：

开机代码为：
0D 2A 70 6F 77 3D 6F 6E 23 0D

把“发送快捷键B”改成向串口发送 关闭投影的代码:
关机代码为：
0D 2A 70 6F 77 3D 6F 66 66 23 0D
*/



//遥控按键 A B
//接线 无线模块-RX 继电器-电脑主机 10

#define computer 10          //电脑主机
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
                            //A-jian 
                             //Keyboard.press('a');		//向电脑发送向
                            //delay(50);		
                            //Keyboard.releaseAll();
                            Serial.print(0D 2A 70 6F 77 3D 6F 6E 23 0D);//开机
                            
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
                            //B-jian 
                             //Keyboard.press('b');//向电脑发送向
                             	
                            //delay(50);		
                            //Keyboard.releaseAll();
                            //Serial.println("//b-jian ");
                             Serial.print(0D 2A 70 6F 77 3D 6F 66 66 23 0D);//关机
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
  

