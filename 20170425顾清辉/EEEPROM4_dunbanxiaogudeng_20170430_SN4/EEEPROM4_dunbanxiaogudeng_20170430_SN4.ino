//按键 1开机      2投影开     3投影关    4 播放space     5 停止ctrl s     6 暂停ctrl p     7、F9 音量加    8、F10音量减    9、关机F1
//接线 无线模块-RX 主机-10-继电器-开机线 投影-11-继电器-牛逼遥控器   照明灯---9
/**********************************************
  解除是
  11
  5
  10
  14
  //**********************************************/
int N = 200;
///////////////////////////////////////////////////////
unsigned long T = 180000;          //影片时长
#include <EEPROM.h>
#include <Keyboard.h>
#include <DmxSimple.h>

#define zhaoming 9          //暂停计时
#define computer 10          //开机
#define projector 11         //投影

//***********************************
int Flag_pass = 0, pass;
int spaceTime = 0;//Times of Spaces;
//**********************************

void setup()
{

  pinMode(zhaoming, OUTPUT);
  pinMode(computer, OUTPUT);
  pinMode(projector, OUTPUT);
  digitalWrite(zhaoming, LOW);
  digitalWrite(computer, HIGH);
  digitalWrite(projector, HIGH);
  Serial1.begin(9600);
  Keyboard.begin();
  DmxSimple.write(1, 0);
  DmxSimple.write(2, 0);
  DmxSimple.write(3, 0);
  DmxSimple.write(9, 0);
  DmxSimple.write(10, 0);
  DmxSimple.write(11, 0);
  //**************首次EEPROM清零*********************
  // for ( int i = 0 ; i < 10; i++ )
  //  EEPROM.write(i, 0);
  //*****************************************************
}
int Flag_computer = 0, Flag_play = 0;
int nochar_count = 0;
unsigned long tim = 0 , now = 0, shichang = 0, nowpr = 0;
int anjian = 0;
int value = 0 ;
void loop()
{
  /////////////////////////////////////////////////////////////////////////////////////////
  now = millis();
  if (Flag_play == 0) {
    tim = now;
  }
  if (shichang +  now - tim >= 2000  && shichang +  now - tim <= 4000)
  {
    if ( ( ( (shichang +  now - tim - 2000) % 16) == 1) && (value < 128) )
    {
      if (nowpr != now)
      {
        value++;
        nowpr = now;
      }
    }

  }
  else if (shichang +  now - tim >= T)
  {
    digitalWrite(zhaoming, LOW);
    Flag_play = 0;
    shichang = 0;


    DmxSimple.write(1, 0);
    DmxSimple.write(2, 0);
    DmxSimple.write(3, 0);
    DmxSimple.write(9, 0);
    DmxSimple.write(10, 0);
    DmxSimple.write(11, 0);

    value = 0;
  }
  else {
    //shichang = shichang + now -tim;
    value = 0;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////
  DmxSimple.write(1, value);
  DmxSimple.write(9, value);
  /////////////////////////////////////////////////////////////////////////////////////////////
  if (Serial1.available() > 0)
  {
    anjian = 0;
    anjian = Serial1.read();
    if (anjian == 6) //串口第1个数字
    {
      delay(5);
      anjian = Serial1.read();
      if (anjian == 170) //串口第2个数字
      {
        delay(5);
        anjian = Serial1.read();
        if (anjian == 186 ) //串口第3个数字
        {
          delay(5);
          anjian = Serial1.read();
          switch (anjian)
          {
            case  192://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                ////1#按键
                //开机
                if (!Flag_computer) {
                  digitalWrite(computer, LOW);
                  delay(100);						//延时100ms
                  digitalWrite(computer, HIGH);	//
                  Flag_computer = 1;
                }
                Serial.println("//1#jian ");
              }
              break;
            case  48://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                digitalWrite(projector, LOW);            //开投影
                Serial.println("//2#jian");
              }
              break;
            case  240://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //3#jian
                digitalWrite(projector, HIGH);            //关投影
                Serial.println("//3#jian ");
              }
              break;
            case  12://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //4#jian
                if (pass == 1 || spaceTime < N)
                {
                  Keyboard.press(' ');		//向电脑发送向播放的指令
                  delay(50);
                  Keyboard.releaseAll();
                  tim = millis();
                  Flag_play = 1;

                  DmxSimple.write(1, 0);
                  DmxSimple.write(2, 255);
                  DmxSimple.write(3, 255);
                  DmxSimple.write(9, 0);
                  DmxSimple.write(10, 255);
                  DmxSimple.write(11, 255);

                  digitalWrite(zhaoming, HIGH);             //照明灯关，效果灯关。
                }
                Serial.println("//4#jian ");
                //**********************************************************************************************
                spaceTime = EEPROM.read(0);
                pass = EEPROM.read(1);
                if (pass == 0 && spaceTime < N)
                {
                  //Times of spaces plus 1;
                  spaceTime += 1;
                  EEPROM.write(0, spaceTime);

                }
                //**********************************************************************************************
              }
              break;
            case  63://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //5#jian
                if (pass == 1 || spaceTime < N)
                {
                  Keyboard.press(KEY_LEFT_CTRL);
                  delay(50);
                  Keyboard.press('s');		//向电脑发送向停止的指令
                  delay(50);
                  Keyboard.releaseAll();
                  Flag_play = 0;
                  digitalWrite(zhaoming, LOW);

                  shichang = 0;
                }
                Serial.println("//5#jian ");
                //********************************************************
                if (Flag_pass == 1)
                  Flag_pass = 2;
                else
                  Flag_pass = 0;
                //****************************************************
              }
              break;

            case  60:
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //6#jian
                if (pass == 1 || spaceTime < N)
                {
                  Keyboard.press(KEY_LEFT_CTRL);
                  delay(50);
                  Keyboard.press('p');		//向电脑发送暂停的指令

                  delay(50);
                  Keyboard.releaseAll();


                  if ( Flag_play == 1)
                  {
                    shichang = shichang + now - tim;
                    Flag_play = 0;

                  }


                }
                Serial.println("//6#jian ");
              }
              break;
            case  252://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //7#jian

                if (pass == 1 || spaceTime < N)
                {
                  Keyboard.press(KEY_F10);			//向电脑发送音量减的指令
                  delay(50);
                  Keyboard.releaseAll();

                  Keyboard.press(KEY_F10);			//向电脑发送音量减的指令
                  delay(50);
                  Keyboard.releaseAll();

                  Keyboard.press(KEY_F10);			//向电脑发送音量减的指令
                  delay(50);
                  Keyboard.releaseAll();

                  Keyboard.press(KEY_F10);			//向电脑发送音量减的指令
                  delay(50);
                  Keyboard.releaseAll();

                  Keyboard.press(KEY_F10);			//向电脑发送音量减的指令
                  delay(50);
                  Keyboard.releaseAll();
                }
                Serial.println("//7#jian ");
              }
              break;
            case  3://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //8#jian

                if (pass == 1 || spaceTime < N)
                {
                  Keyboard.press(KEY_F9);		//向电脑发送音量减的指令
                  delay(50);
                  Keyboard.releaseAll();

                  Keyboard.press(KEY_F9);		//向电脑发送音量减的指令
                  delay(50);
                  Keyboard.releaseAll();

                  Keyboard.press(KEY_F9);		//向电脑发送音量减的指令
                  delay(50);
                  Keyboard.releaseAll();

                  Keyboard.press(KEY_F9);		//向电脑发送音量减的指令
                  delay(50);
                  Keyboard.releaseAll();

                  Keyboard.press(KEY_F9);		//向电脑发送音量减的指令
                  delay(50);
                  Keyboard.releaseAll();
                }
                Serial.println("//8#jian ");
              }
              break;
            case  195://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
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
              if (anjian == 0)
              {
                //10#jian

                //*****************************
                if (Flag_pass == 2)
                  Flag_pass = 3;
                else
                  Flag_pass = 0;
                //*****************************
                Serial.println("//10#jian ");
              }
              break;
            case  51://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //11#jian
                //*****************************************************
                if (Flag_pass == 0)
                  Flag_pass = 1;
                //********************************************************

                Serial.println("//11#jian ");
              }
              break;
            case  15://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //12#jian
                Serial.println("//12#jian ");
              }
              break;
            case  255://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //13#jian
                Serial.println("//13#jian ");
              }
              break;
            case  207://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //14#jian
                //*****************************
                if (Flag_pass == 3)
                {

                  EEPROM.write(1 , 1);
                  Serial.print("解码成功");

                }
                else
                  Flag_pass = 0;
                //*****************************
                Serial.println("//14#jian ");
              }
              break;
            case  204://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
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


