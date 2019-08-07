unsigned short LightStatus[CHANNELNUM + 1] = {0};

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
    if (anjian == CTRLCODE_1) //串口第1个数字
    {
      delay(5);
      anjian = Serial1.read();
      if (anjian == CTRLCODE_2) //串口第2个数字
      {
        delay(5);
        anjian = Serial1.read();
        if (anjian == CTRLCODE_3) //串口第3个数字
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
