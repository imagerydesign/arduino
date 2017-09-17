//说明：一共要改两个方面的东西，一个是序列个数，另一个是灯光序列，先改后面一个，改完数一下几条再改第一个。
//举例说明{100.0,200.0,1.80}这条指令的意思就是在第100毫秒到200毫秒之间，第一通道由前一个值渐变到亮度80。一秒有1000毫秒。
//写灯光变化指令的时候，先用控制台检测一下，几号通道是负责什么的，大概需要多大的亮度。
#include <DmxSimple.h>
#include <EEPROM.h>
#include <Keyboard.h>

#define SEQNUM  6           //序列个数
#define CHANNELNUM  32

struct LIGHTSEQ
{
  double startTime;
  double stopTime;
  int channel;
  int value;
  // unsigned long lastTime;
};
unsigned short LightStatus[CHANNELNUM + 1] = {0};

struct LIGHTSEQ lightSeq[SEQNUM] = //起始时间 终止时间 通道号 变化值
{
  {100.0, 200.0, 1, 80},
  {300.0, 400.0, 2, 80},
  {500.0, 600.0, 3, 80},
  {700.0, 50000.0, 4, 0},
  {50001.0, 70000.0, 4, 40},
  {70001.0, 90000.0, 4, 40},
};
void setup()
{
  Serial1.begin(9600);
  for (int i = 0; i < CHANNELNUM; i++)
  {
    DmxSimple.write (i, 0);
  }
}
int nSeqNum = 0;
int anjian = 0;
bool bStop = true;
bool bPlaying = false;
double startTime = 0;
double now = 0;
double lastTime = 0;
//unsigned long realLastTime = 0;
int curValue = 0;
double hhe;
void loop()
{
  now = (double)millis ();
  if (bPlaying && nSeqNum < SEQNUM)
  {
    for (int i = nSeqNum; i < SEQNUM; i++)
    {
      if (lightSeq[i].startTime > now - startTime)
      {
        break;
      }
      if (lightSeq[i].stopTime < now - startTime)
      {
        curValue = lightSeq[i].value;
        LightStatus[lightSeq[i].channel] = lightSeq[i].value;
        nSeqNum++;
      }
      else
      {
        if (lightSeq[i].value > LightStatus[lightSeq[i].channel])
        {
          curValue = LightStatus[lightSeq[i].channel] + (int)((lightSeq[i].value - LightStatus[lightSeq[i].channel]) * (now - lightSeq[i].startTime - startTime) / (lightSeq[i].stopTime - lightSeq[i].startTime));
        }
        else
        {
          curValue = LightStatus[lightSeq[i].channel] - (int)((LightStatus[lightSeq[i].channel] - lightSeq[i].value) * (now - lightSeq[i].startTime - startTime) / (lightSeq[i].stopTime - lightSeq[i].startTime));
        }

      }
      DmxSimple.write (lightSeq[i].channel, curValue);
      Serial.println(lightSeq[i].startTime);
      Serial.println(now);
      Serial.println(LightStatus[lightSeq[i].channel]);
      Serial.println(lightSeq[i].value - LightStatus[lightSeq[i].channel]);
      Serial.println(curValue);
      Serial.println("\n");
      //LightStatus[lightSeq[i].channel] = curValue;
    }
    //lastTime = now;
  }
  else if (bStop)
  {
    for (int i = 0; i < CHANNELNUM; i++)
    {
      DmxSimple.write (i, 0);
    }
  }
  else if (nSeqNum >= SEQNUM)
  {
    bPlaying = false;
    bStop = true;
    startTime = 0;
    lastTime = 0;
    nSeqNum = 0;
  }

  if (Serial1.available() > 0)
  {
    anjian = Serial1.read();
    if (anjian == 6) //串口第1个数字
    {
      delay(5);
      anjian = Serial1.read();
      if (anjian == 170) //串口第2个数字
      {
        delay(5);
        anjian = Serial1.read();
        if (anjian == 178 ) //串口第3个数字
        {
          delay(5);
          anjian = Serial1.read();
          switch (anjian)
          {
            case  12://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //4#jian
                if (!bPlaying)
                {
                  bPlaying = true;
                  if (bStop)
                  {
                    startTime = (double)millis();
                    Serial.println(startTime);
                    lastTime = startTime;
                    bStop = false;
                  }
                }
                Serial.println("//4#jian ");
              }
            case  63://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //5#jian
                if (!bStop)
                {
                  bPlaying = false;
                  bStop = true;
                  startTime = 0;
                  lastTime = 0;
                  nSeqNum = 0;
                }
                Serial.println("//5#jian ");
              }
              break;
            case  60:
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //6#jian
                if (bPlaying)
                {
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
