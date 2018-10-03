/*
/////////////////////////////////////////////////
先开投影，锁死，30S后开机，开机两分钟内不能关机
先关电脑，锁死，5S后关投影，三分钟内不能再开
2015-7-18
///////////////////////////
两行斜线中间内容为今天修改
////////////////////////////
//////////////////////////////////////////////////

改为使用pro mini来控制投影、主机的开关；用leonardo来发送快捷键；
两套分别接各自的无线接收模块，但两套用同一个遥控器，也就是说响应同一套无线的控制码。

1增加开机关机互锁
2开机2分钟之内不能关机（因为投影机启动需要时间，处于启动中的投影机不响应关机命令，但这时候主机会相应关机命令）
 关机2分钟之内不能开机（因为投影机关机之后需要冷却，2分钟之内不响应开机命令，但这时候主机会相应关机命令）
2016-7-16

开投影后延迟20秒开主机 带暂停 带space键50次 限制 到次数之后 播放键就会变成关闭主机和关闭投影机
遥控器按键对应的功能 1号投影开 开机   2号关机 关投影  4号快捷键space   5号快捷键ctrl s  6号快捷键ctrl p  7号f9音量加  8号f10音量减
2015-7-1

用无线遥控模块给leonardo发送信号，leonardo根据信号控制外部继电器控制外部设备，主机开机之后作为键盘来给主机发送快捷键控制软件的一些功能。
用arduino的EEEPROM功能限制对方的使用次数，便于我方收尾款。
初步的思路是：space是整个功能中最重要的一个按键，累计一下对方使用spaces这个快捷键的次数，达到20次之后，全部的快捷键就会被替换成删除D盘所有文件的命令。
删除D盘所有文件的快捷键命令，还需要你查一下,使用的操作系统是XP。
2015-6-15

遥控器按键对应的功能 1号开关机  2号投影开  3号投影关 4号快捷键space  5号快捷键ctrl s  6号快捷键ctrl p 7号f9音量加  8号f10音量减
接线 无线模块-RX引脚 主机-10引脚-继电器-开机线 投影-11引脚-继电器-投影遥控模块
2015-4-19
*/

#include <EEPROM.h>
#define computer 10          //开机
#define projector 11         //投影
///////////////////TIME/////////////////////
int Flag_computer = 0;
unsigned long time , now;
int seco, hour, pass;
/////////////////////////////////////////
void setup()
{
  pinMode(computer, OUTPUT);
  pinMode(projector, OUTPUT);
  digitalWrite(computer, HIGH);
  digitalWrite(projector, HIGH);
  Serial.begin(9600);

  digitalWrite(13, HIGH);// turn the LED on when we're done
}
int flag_projector = 0;
int nochar_count = 0;

int anjian = 0;
int spaceTime = 0;//Times of Spaces;
int address = 0;//Address to store times of spaces
void loop()
{
  ///////////////// 计时//////////////////////////////
  now = millis();
  if (Flag_computer == 2)
  {
    if ((now - time >= 30000) && (now - time <= 150000)   ) //按下开机键，投影开后30秒
    {
      digitalWrite(computer, LOW);
      delay(200);//延时200ms
      digitalWrite(computer, HIGH);//开机

      Flag_computer = 4;

    }
    else if (now < time)
      time = 0;
  }
  else if (Flag_computer == 4)
  {
    if (now - time >= 150000)         //按下开机键，投影开后150秒
    {
      Flag_computer = 1;
      time = now;
    }

    else if (now < time)
      time = 0;
  }
  else if (Flag_computer == 3)
  {

    if ((now - time >= 5000) && (now - time <= 150000)  ) //按下关机键后5秒
    {
      digitalWrite(projector, HIGH);            //关投影

      Flag_computer = 5;

    }
    else if (now < time)
      time = 0;
  }
  else  if (Flag_computer == 5)
  {
    if (now - time >= 150000)         //按下关机键后210秒
    {
      Flag_computer = 0;
      time = now;
    }

    else if (now < time)
      time = 0;

  }
  ////////////////////////////////////////////////////////////////


  if (Serial.available() > 0)
  {
    anjian = 0;
    anjian = Serial.read();
    if (anjian == 6) //串口第1个数字
    {
      delay(5);
      anjian = Serial.read();
      if (anjian == 234) //串口第2个数字
      {
        delay(5);
        anjian = Serial.read();
        if (anjian == 186) //串口第3个数字
        {
          delay(5);
          anjian = Serial.read();
          switch (anjian)
          {
            case  192://串口第4个数字
              delay(5);
              anjian = Serial.read();
              if (anjian == 0)
              {


                //////////////////////////////////////////////////
                if (Flag_computer == 0)
                {
                  digitalWrite(projector, LOW);            //开投影
                  time = millis();                          //开始计时
                  Flag_computer = 2;

                }
                /////////////////////////////////////////////////////////////
                Serial.println("//1#jian ");//1#按键

              }
              break;
            case  48://串口第4个数字
              delay(5);
              anjian = Serial.read();
              if (anjian == 0)
              {



                ////////////////////////////////////////////////
                if (Flag_computer == 1)
                {

                  digitalWrite(computer, LOW);
                  delay(200);						//延时200ms
                  digitalWrite(computer, HIGH);	//

                  time = millis();                          //开始计时
                  Flag_computer = 3;

                }
                ///////////////////////////////////////////////////////////////




                Serial.println("//2#jian");
              }
              break;
            case  240://串口第4个数字 3#按键
              delay(5);
              anjian = Serial.read();
              if (anjian == 0)
              {
                //3#jian
                Serial.println("//3#jian ");
              }
              break;
            case  12://串口第4个数字
              delay(5);
              anjian = Serial.read();
              if (anjian == 0)
              {
                //4#jian
                //Read space times:
                spaceTime = EEPROM.read(address);
                delay(10);
                //30 times;
                if (spaceTime > 50)
                {
                  //shut down computor and project
                  digitalWrite(computer, LOW);
                  delay(200);//延时200ms
                  digitalWrite(computer, HIGH);	//
                  delay(5000);
                  digitalWrite(projector, HIGH);  //关投影
                  Serial.println("//shut down computor project ");
                }
                else
                {


                  Serial.println("//4#jian ");
                  //Times of spaces plus 1;
                  spaceTime += 1;
                  EEPROM.write(address, spaceTime);

                }
              }
              break;
          }
        }
      }
    }
  }
}


