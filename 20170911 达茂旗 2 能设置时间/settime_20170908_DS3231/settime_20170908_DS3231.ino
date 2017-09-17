//按键 1开机      2投影开     3投影关    4 space     5 ctrl s     6 ctrl p     7、F9 音量加    8、F10音量减   //9、关机F1
//接线 无线模块-RX 主机-10-继电器-开机线 投影-11-继电器-牛逼遥控器
/**********************************************
  解除是
  7
  5
  10
  12
  //**********************************************/
unsigned long T = 60000;          //开投影后冷却关机

//int N=800;
byte AYear, AMonth, ADate;
//到期的时间
byte DYear = 17, DMonth = 9, DDate = 13;

#include <DS3231.h>
#include <Wire.h>

#include <EEPROM.h>
#include <Keyboard.h>
#define computer 10          //开机
#define projector 11         //投影

DS3231 Clock;
bool Century = false;

//***********************************
int Flag_pass = 0, pass;
int spaceTime = 0;//Times of Spaces;
//**********************************

void setup()
{
  pinMode(computer, OUTPUT);
  pinMode(projector, OUTPUT);
  digitalWrite(computer, HIGH);
  digitalWrite(projector, HIGH);
  Serial1.begin(9600);
  Keyboard.begin();


  Wire.begin();
  //*************首次设置现在的时间*********************
  Clock.setYear(17);
  Clock.setMonth(9);
  Clock.setYear(8);

  //*****************************************************
}
int Flag_projector = 0 , Flag_computer = 0;
int nochar_count = 0;
unsigned long tim = 0 , now = 0;

int anjian = 0;
void loop()
{
  /////////////////////////////////////////////////////////////////////////////////////////
  now = millis();
  if (now - tim >= T )
  {
    if (Flag_projector == 1)
    {
      Flag_projector = 2;
    }
    else if (Flag_projector == 3)
    {
      Flag_projector = 0;
    }
  }

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
                // if (!Flag_computer){
                digitalWrite(computer, LOW);
                delay(100);						//延时100ms
                digitalWrite(computer, HIGH);	//
                Flag_computer = 1;
                // }
                Serial.println("//1#jian ");
              }
              break;
            case  48://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {

                if (Flag_projector == 0) {
                  digitalWrite(projector, LOW);            //开投影
                  Flag_projector = 1;
                  tim = millis();
                  now = tim;
                }
                Serial.println("//2#jian");
              }
              break;
            case  240://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //3#jian
                if (Flag_projector == 2) {
                  digitalWrite(projector, HIGH);            //关投影
                  Flag_projector = 3;
                  tim = millis();
                  tim = now;
                }
                Serial.println("//3#jian ");
              }
              break;
            case  12://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //4#jian

                AYear = Clock.getYear();
                AMonth = Clock.getMonth(Century);
                ADate = Clock.getDate();
                Serial.print("AYear =  ");
                Serial.println(AYear);
                Serial.print("AMonth =  ");
                Serial.println(AMonth);
                Serial.print("ADate =  ");
                Serial.println(ADate);
                if (AYear < DYear || (AYear == DYear) && (AMonth < DMonth || (AMonth = DMonth && ADate <= DDate) ) )

                  // if(pass == 1 || spaceTime < N)
                {
                  //Keyboard.press(' ');		//向电脑发送向播放的指令
                  delay(50);
                  Keyboard.releaseAll();

                }
                Serial.println("//4#jian ");
                /**********************************************************************************************
                  spaceTime = EEPROM.read(0);
                  pass = EEPROM.read(1);
                  if(pass == 0 && spaceTime < N)
                  {
                  //Times of spaces plus 1;
                    spaceTime += 1;
                    EEPROM.write(0, spaceTime);

                  }
                  //**********************************************************************************************/
              }
              break;
            case  63://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //5#jian
                AYear = Clock.getYear();
                AMonth = Clock.getMonth(Century);
                ADate = Clock.getDate();
                Serial.print("AYear =  ");
                Serial.println(AYear);
                Serial.print("AMonth =  ");
                Serial.println(AMonth);
                Serial.print("ADate =  ");
                Serial.println(ADate);
                if (AYear < DYear || (AYear == DYear) && (AMonth < DMonth || (AMonth = DMonth && ADate <= DDate) ) )

                  // if(pass == 1 || spaceTime < N)
                {
                  //Keyboard.press(KEY_LEFT_CTRL);
                  // Keyboard.press('s');		//向电脑发送向停止的指令
                  delay(50);
                  Keyboard.releaseAll();
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

                //if(pass == 1 || spaceTime < N)
                {
                  //Keyboard.press(KEY_LEFT_CTRL);
                  // Keyboard.press('P');		//向电脑发送向停止的指令

                  delay(50);
                  // Keyboard.releaseAll();
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
                //*****************************************************
                if (Flag_pass == 0)
                  Flag_pass = 1;
                //********************************************************

                Serial.println("//7#jian ");
              }
              break;
            case  3://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //8#jian

                Serial.print("使用次数：");
                Serial.print(spaceTime);
                Serial.println("次");
                Serial.println("//8#jian ");
              }
              break;
            case  195://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //9#jian
                //  Keyboard.press(KEY_F1);    //向电脑发送关机指令
                delay(50);
                // Keyboard.releaseAll();
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


                Serial.println("//11#jian ");
              }
              break;
            case  15://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //12#jian
                //*****************************
                if (Flag_pass == 3)
                {

                  EEPROM.write(1 , 1);
                  Serial.print("解码成功");

                }
                else
                  Flag_pass = 0;
                //*****************************
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


