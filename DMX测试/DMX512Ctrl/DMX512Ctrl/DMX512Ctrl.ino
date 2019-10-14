
#include <DmxSimple.h>
#include <EEPROM.h>
#include <Keyboard.h>


#define SEQNUM  4           //序列个数
#define zhaoming 9          //暂停计时
#define computer 10          //开机
#define projector 11         //投影

struct LIGHTSEQ 
{
  int startTime;
  int stopTime;
  int channel;
  int value;
  int curValue;
};

struct LIGHTSEQ lightSeq[SEQNUM] = //起始时间 终止时间 通道号 变化值 
{
  {1, 1, 2, 255, 0},   
  {1, 1, 3, 255, 0}, 
  {1, 1, 4, 255, 0}, 
  {2, 3, 1, 255, 0}, 
};

void setup() 
{
  pinMode(zhaoming, OUTPUT);
  pinMode(computer, OUTPUT);
  pinMode(projector, OUTPUT);
  digitalWrite(zhaoming,LOW);
  digitalWrite(computer,HIGH);
  digitalWrite(projector,HIGH);
  Serial1.begin(9600);
  Keyboard.begin();
  
  for (int i=0;i<256;i++)
  {
    DmxSimple.write (i, 0);
  }
/*  for (int i=0;i<SEQNUM;i++)
  {
    if (lightSeq[i].stopTime - lightSeq[i].startTime == 0)
    {
      lightSeq[i].stepValue = lightSeq[i].value;
    }
    else 
    {
      lightSeq[i].stepValue = lightSeq[i].value / ((lightSeq[i].stopTime - lightSeq[i].startTime)/0.04);
    }
  }*/
}

int nSeqNum = 0;
int anjian = 0;
bool bStop=true;
bool bPlaying = false;
bool Flag_computer = false;
int startTime = 0;
int now = 0;
int curValue = 0;
void loop()
{
  now = millis ();
  if (bPlaying && nSeqNum<SEQNUM)
  {
    for (int i=nSeqNum;i<SEQNUM;i++)
    {
      if (lightSeq[i].startTime > now - startTime)
      {
        break;
      }
      if (lightSeq[i].stopTime < now - startTime)
      {
        curValue = lightSeq[i].value;
        nSeqNum++;
      }
      else 
      {
        curValue = lightSeq[i].value * (now - startTime) / (lightSeq[i].stopTime - lightSeq[i].startTime);
      }
      DmxSimple.write (lightSeq[i].channel, curValue);
      lightSeq[i].curValue = curValue;
      
    }
  }
  else if (bStop)
  {
    digitalWrite(zhaoming,LOW);
    for (int i=0;i<256;i++)
    {
      DmxSimple.write (i, 0);
    }
  }

  if (Serial1.available() > 0) 
  {
    anjian = 0;
    anjian = Serial1.read();
    if(anjian == 6)//串口第1个数字
    {
      delay(5);
      anjian = Serial1.read();
      if(anjian == 170)//串口第2个数字
      {
        delay(5);
        anjian = Serial1.read();
        if(anjian == 186 )//串口第3个数字
        {
          delay(5);
          anjian = Serial1.read();
          
          switch(anjian)
          {
            case  192://串口第4个数字
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            ////1#按键 
                             //开机
                             if (!Flag_computer){
                             digitalWrite(computer,LOW);
                             delay(100);            //延时100ms
                             digitalWrite(computer,HIGH); //
                             Flag_computer = false;
                             }
                             Serial.println("//1#jian ");
                        }
                        break;
            case  48://串口第4个数字
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        { 
                             digitalWrite(projector,LOW);             //开投影   
                             Serial.println("//2#jian");
                        }
                        break;
            case  240://串口第4个数字
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //3#jian 
                          digitalWrite(projector,HIGH);             //关投影
                            Serial.println("//3#jian ");
                        }
                        break;
            case  12://串口第4个数字
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //4#jian 
                            if(!bPlaying)
                            {
                            Keyboard.press(' ');    //向电脑发送向播放的指令
                            delay(50);    
                            Keyboard.releaseAll();
                            bPlaying = 1;
                            if (bStop)
                            {
                              startTime = millis();
                              bStop = false;
                            }
                            digitalWrite(zhaoming,HIGH);              //照明灯关，效果灯关。
                            }
                            Serial.println("//4#jian ");
                            //**********************************************************************************************
/*                            spaceTime = EEPROM.read(0);
                            pass = EEPROM.read(1);
                            if(pass == 0 && spaceTime < N)
                            {
                              //Times of spaces plus 1;
                                spaceTime += 1;
                                EEPROM.write(0, spaceTime);

                            }
 */
                            //**********************************************************************************************
                        }
                        break;
            case  63://串口第4个数字
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //5#jian 
                            if(bPlaying)
                            {
                             Keyboard.press(KEY_LEFT_CTRL);
                             delay(50);
                             Keyboard.press('s');   //向电脑发送向停止的指令
                            delay(50);    
                            Keyboard.releaseAll();
                            bPlaying = false;
                            bStop = true;
                            digitalWrite(zhaoming,LOW);
                            }
                            Serial.println("//5#jian ");
                            //********************************************************
                            /*
                               if(Flag_pass == 1)
                                Flag_pass = 2;
                            else
                                Flag_pass = 0;
                                */
                                //****************************************************
                        }
                        break;

               case  60:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //6#jian 
                           if(bPlaying)
                           {
                               Keyboard.press(KEY_LEFT_CTRL);
                               delay(50);
                               Keyboard.press('p');   //向电脑发送暂停的指令
                               delay(50);    
                               Keyboard.releaseAll();
                               bPlaying = false;
                           }
                            Serial.println("//6#jian ");
                        }
                        break;
            case  252://串口第4个数字
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //7#jian 
                            
                            if(bPlaying)
                            {
                            Keyboard.press(KEY_F10);      //向电脑发送音量减的指令
                            delay(50);    
                            Keyboard.releaseAll();
                            
                            Keyboard.press(KEY_F10);      //向电脑发送音量减的指令
                            delay(50);    
                            Keyboard.releaseAll();
                            
                            Keyboard.press(KEY_F10);      //向电脑发送音量减的指令
                            delay(50);    
                            Keyboard.releaseAll();
                            
                            Keyboard.press(KEY_F10);      //向电脑发送音量减的指令
                            delay(50);    
                            Keyboard.releaseAll();
                            
                            Keyboard.press(KEY_F10);      //向电脑发送音量减的指令
                            delay(50);    
                            Keyboard.releaseAll();
                            }
                            Serial.println("//7#jian ");
                        }
                        break;                        
            case  3://串口第4个数字
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //8#jian 
                            
                            if(bPlaying)
                            {
                            Keyboard.press(KEY_F9);   //向电脑发送音量减的指令
                            delay(50);    
                            Keyboard.releaseAll();
                            
                            Keyboard.press(KEY_F9);   //向电脑发送音量减的指令
                            delay(50);    
                            Keyboard.releaseAll();
                            
                            Keyboard.press(KEY_F9);   //向电脑发送音量减的指令
                            delay(50);    
                            Keyboard.releaseAll();
                            
                            Keyboard.press(KEY_F9);   //向电脑发送音量减的指令
                            delay(50);    
                            Keyboard.releaseAll();
                            
                            Keyboard.press(KEY_F9);   //向电脑发送音量减的指令
                            delay(50);    
                            Keyboard.releaseAll();
                            }
                            Serial.println("//8#jian ");
                        }
                        break;
            case  195://串口第4个数字
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //9#jian 
                             Keyboard.press(KEY_F1);    //向电脑发送关机指令
                            delay(50);    
                            Keyboard.releaseAll();
                            Flag_computer = 0;
                             
                             Serial.println("//9#jian ");
                        }
                        break;
            case  243://串口第4个数字
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //10#jian 
                            
                            //*****************************
                            /*
                            if(Flag_pass == 2)
                                Flag_pass = 3;
                            else
                                Flag_pass = 0;
                                */
                            //*****************************
                             Serial.println("//10#jian ");
                        }
                        break;
            case  51://串口第4个数字
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //11#jian 
                             //*****************************************************
                             /*
                            if(Flag_pass == 0)
                            Flag_pass = 1;*/
               //********************************************************            
             
                             Serial.println("//11#jian ");
                        }
                        break;
            case  15://串口第4个数字
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //12#jian 
                             Serial.println("//12#jian ");
                        }
                        break;
            case  255://串口第4个数字
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //13#jian 
                             Serial.println("//13#jian ");
                        }
                        break;
            case  207://串口第4个数字
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //14#jian 
                                  //*****************************
/*                            if(Flag_pass == 3)
                            {
                                
                                EEPROM.write(1 ,1);
                                Serial.print("解码成功");
                               
                            }
                            else
                                Flag_pass = 0;
                                */
                            //*****************************
                             Serial.println("//14#jian ");
                        }
                        break;
            case  204://串口第4个数字
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
