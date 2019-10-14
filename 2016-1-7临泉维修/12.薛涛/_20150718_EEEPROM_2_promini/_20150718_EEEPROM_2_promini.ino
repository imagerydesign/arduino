/*
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
void setup()
{
  pinMode(computer, OUTPUT);
  pinMode(projector, OUTPUT);
  digitalWrite(computer, HIGH);
  digitalWrite(projector, HIGH);
  Serial.begin(9600);

   //for ( int i = 0 ; i < EEPROM.length() ; i++ )
   //EEPROM.write(i, 0);
  digitalWrite(13, HIGH);// turn the LED on when we're done
}
int flag_projector = 0;
int nochar_count = 0;
int anjian = 0;
int spaceTime = 0;//Times of Spaces;//4#按键;
int address = 0;//Address to store times of spaces
void loop()
{
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
                digitalWrite(projector, LOW);            //开投影
                delay(20000);
                digitalWrite(computer, LOW);
                delay(100);						//延时100ms
                digitalWrite(computer, HIGH);	//开机
                Serial.println("//1#jian ");//1#按键
              }
              break;
            case  48://串口第4个数字
              delay(5);
              anjian = Serial.read();
              if (anjian == 0)
              {
                //shut down computor and project
                digitalWrite(computer, LOW);
                delay(100);						//延时100ms
                digitalWrite(computer, HIGH);	//
                delay(5000);
                digitalWrite(projector, HIGH);            //关投影
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
                  delay(100);						//延时100ms
                  digitalWrite(computer, HIGH);	//
                  delay(5000);
                  digitalWrite(projector, HIGH);            //关投影
                  Serial.println("//shut down computor project ");
                }
                else
                {

                  /*
                  Keyboard.press(' ');		//向电脑发送向播放的指令
                  delay(50);
                  Keyboard.releaseAll();
                   */
                  
                  Serial.println("//4#jian ");
                  //Times of spaces plus 1;
                  spaceTime += 1;
                  EEPROM.write(address, spaceTime);
                  //delay;
                  delay(10);
                 

                  digitalWrite(13, LOW);
                  delay(100);
                  digitalWrite(13, HIGH);
                }
              }
              break;


            /*
                          case  63://串口第4个数字
                          delay(5);
                          anjian = Serial1.read();
                          if (anjian == 0)
                          {
                            //5#jian
                            Keyboard.press(KEY_LEFT_CTRL);
                            Keyboard.press('s');		//向电脑发送向停止的指令
                            delay(50);
                            Keyboard.releaseAll();
                            Serial.println("//5#jian ");
                          }
                          break;
                        case  60://串口第4个数字
                          delay(5);
                          anjian = Serial1.read();
                          if (anjian == 0)
                          {
                            //6#jian
                            Keyboard.press(KEY_LEFT_CTRL);
                            Keyboard.press('p');		//向电脑发送向停止的指令

                            delay(50);
                            Keyboard.releaseAll();
                            Serial.println("//6#jian ");
                          }
                          break;
                        case  252://串口第4个数字
                          delay(5);
                          anjian = Serial1.read();
                          if (anjian == 0)
                          {
                            //7#jian

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

                            Serial.println("//7#jian ");
                          }
                          break;
                        case  3://串口第4个数字
                          delay(5);
                          anjian = Serial1.read();
                          if (anjian == 0)
                          {
                            //8#jian

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

                            Serial.println("//8#jian ");
                          }
                          break;


            */


            case  195://串口第4个数字
              delay(5);
              anjian = Serial.read();
              if (anjian == 0)
              {
                //9#jian
                Serial.println("//9#jian ");
              }
              break;
            case  243://串口第4个数字
              delay(5);
              anjian = Serial.read();
              if (anjian == 0)
              {
                //10#jian
                Serial.println("//10#jian ");
              }
              break;
            case  51://串口第4个数字
              delay(5);
              anjian = Serial.read();
              if (anjian == 0)
              {
                //11#jian
                Serial.println("//11#jian ");
              }
              break;
            case  15://串口第4个数字
              delay(5);
              anjian = Serial.read();
              if (anjian == 0)
              {
                //12#jian
                Serial.println("//12#jian ");
              }
              break;
            case  255://串口第4个数字
              delay(5);
              anjian = Serial.read();
              if (anjian == 0)
              {
                //13#jian
                Serial.println("//13#jian ");
              }
              break;
            case  207://串口第4个数字
              delay(5);
              anjian = Serial.read();
              if (anjian == 0)
              {
                //14#jian
                Serial.println("//14#jian ");
              }
              break;
            case  204://串口第4个数字
              delay(5);
              anjian = Serial.read();
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


