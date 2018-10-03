
/*
波 特 率：19200
数 据 位：8
停 止 位：1
奇偶校验：0
投影机开：BEEF02060013CEAA0000000000
投影机关：BEEF02060013CEAA0000000000
开机
0D 2A 70 6F 77 3D 6F 6E 23 0D
关机
0D 2A 70 6F 77 3D 6F 66 66 23 0D

一号键 开主机 开投影 音响通电
二号键 都关闭
*/
#include <SoftwareSerial.h>
#include <EEPROM.h>

 SoftwareSerial mySerial(10, 11); // 投影RX, TX
#define computer 2          //开机
#define Speaker 4         //音响
#define projector 3         //红外投影
int sensorPin = A0;
void setup()
{
 
  pinMode(computer, OUTPUT);
  pinMode(Speaker, OUTPUT);
  Serial.begin(115200);
  
  Serial1.begin(9600);
  mySerial.begin(19200);
  Keyboard.begin();
}
//int flag_projector = 0;
int Flag_computer = 0;
int nochar_count = 0;
//开机
//0D 2A 70 6F 77 3D 6F 6E 23 0D
//关机
//0D 2A 70 6F 77 3D 6F 66 66 23 0D
//unsigned char hexdata[13] = {  0xBE,0xEF,0x02,0x06,0x00,0x13,0xCE,0xAA,0x00,0x00,0x00,0x00,0x00};
unsigned char hexopen[10] = {  0x0D ,0x2A  ,0x70  ,0x6F  ,0x77  ,0x3D  ,0x6F  ,0x6E  ,0x23  ,0x0D};
unsigned char hexclose[11] = {  0x0D  ,0x2A  ,0x70  ,0x6F  ,0x77  ,0x3D  ,0x6F  ,0x66  ,0x66  ,0x23  ,0x0D};

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
      if(anjian == 160)
      {
        delay(5);
        anjian = Serial1.read();
        if(anjian == 142)
        {
          delay(5);
          anjian = Serial1.read();
          switch(anjian)
          {
            case  192:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            ////1#按键 
                             //开机
                             if(Flag_computer==0)
                             {
                             digitalWrite(computer,HIGH);
                                       
                             delay(100);						//延时100ms
                             digitalWrite(computer,LOW);	//
                             Flag_computer = 1;  
                           
                             //投影机开：BEEF02060013CEAA0000000000
                             mySerial.write(hexopen, 10);
                            }
                             //音响通电
                               digitalWrite(Speaker,HIGH);    
                          //开红外投影           
                               digitalWrite(projector,HIGH); 
                             Serial.println("//1#anjian ");
                        }
                        break;
            case  48:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //2#按键  
                           
                          
                              
                              
                             //关机
                             if(Flag_computer==1)
                             {
                             digitalWrite(computer,HIGH);
                                       
                             delay(100);						//延时100ms
                             digitalWrite(computer,LOW);	//
                             Flag_computer = 0;  
                           
                             //投影机关：BEEF0206003EC4D70000000000 
                              mySerial.write(hexclose, 11);
                            }
                            //音响关电
                               digitalWrite(Speaker,LOW);    
                          //关红外投影           
                               digitalWrite(projector,LOW); 
                         
                            
                             Serial.println("//2#按键");
                        }
                        break;
            case  240:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //3#jian 
                        //  digitalWrite(projector,LOW);             //关红外投影
                            Serial.println("//3#jian ");
                        }
                        break;
            case  12:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //4#jian 
                            Keyboard.press(KEY_LEFT_CTRL);
                            Keyboard.press(' ');		//向电脑发送向播放的指令
                            delay(50);		
                            Keyboard.releaseAll();
                            Serial.println("//4#jian ");
                        }
                        break;
            case  63:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //5#jian 
                             Keyboard.press(KEY_LEFT_CTRL);
                             Keyboard.press('S');		//向电脑发送向停止的指令
                             // Keyboard.press('f');	
                            delay(50);		
                            Keyboard.releaseAll();
                            Serial.println("//5#jian ");
                        }
                        break;
            case  60:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //6#jian 
                             Keyboard.press(KEY_LEFT_CTRL);
                             Keyboard.press('P');		//向电脑发送向停止的指令
                             	
                            delay(50);		
                            Keyboard.releaseAll();
                            Serial.println("//6#jian ");
                        }
                        break;
           
            case  252:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //7#jian 
                           Keyboard.press(KEY_LEFT_CTRL);
                             Keyboard.press(KEY_F1);			//向电脑发送音量减的指令
                             	
                            delay(50);		
                            Keyboard.releaseAll();
                            Serial.println("//7#jian ");
                        }
                        break;                        
            case  3:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //8#jian 
                           Keyboard.press(KEY_LEFT_CTRL);
                             Keyboard.press(KEY_F2);		//向电脑发送音量减的指令
                             	
                            delay(50);		
                           // Keyboard.releaseAll();
                            Serial.println("//8#jian ");
                        }
                        break;
            case  195:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //9#jian 
                             Serial.println("//9#jian ");
                        }
                        break;
            case  243:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //10#jian 
                             Serial.println("//10#jian ");
                        }
                        break;
            case  51:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //11#jian 
                             Serial.println("//11#jian ");
                        }
                        break;
            case  15:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //12#jian 
                             Serial.println("//12#jian ");
                        }
                        break;
            case  255:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //13#jian 
                             Serial.println("//13#jian ");
                        }
                        break;
            case  207:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //14#jian 
                             Serial.println("//14#jian ");
                        }
                        break;
            case  204:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //15#jian 
                             Serial.println("//15#jian ");
                        }
                        break;
          }
        }
      }
    }
  }
}
  

