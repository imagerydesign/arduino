 
#include <DmxSimple.h>
#include <EEPROM.h>
#include <Keyboard.h>


#define SEQNUM  2               //序列个数
#define zhaoming 9          //暂停计时
#define computer 10          //开机
#define projector 11         //投影

struct LIGHTSEQ 
{
  unsigned long startTime;
  unsigned long stopTime;
  int channel;
  int value;
  int curValue;
};

struct LIGHTSEQ lightSeq[SEQNUM] = //起始时间 终止时间 通道号 变化值 
{
  {0,0,1,255,0},
  {1000,18000,2,255,0},
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
}

int nSeqNum = 0;
int anjian = 0;
bool bStop=true;
bool bPlaying = false;
unsigned long startTime = 0;
unsigned long now = 0;
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
        curValue = lightSeq[i].curValue + lightSeq[i].value * (now - startTime) / (lightSeq[i].stopTime - lightSeq[i].startTime);
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
                        }
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
          }
        }
      }
    }
  }
  
}
