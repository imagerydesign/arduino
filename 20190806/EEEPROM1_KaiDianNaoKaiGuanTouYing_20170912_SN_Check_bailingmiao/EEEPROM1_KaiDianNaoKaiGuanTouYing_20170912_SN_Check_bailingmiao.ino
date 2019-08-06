//按键 1开机      2投影开     3投影关    4 space     5 ctrl s     6 ctrl p     7、F9 音量加    8、F10音量减   //9、关机F1
//接线 无线模块-RX 主机-10-继电器-开机线 投影-11-继电器-牛逼遥控器
/**********************************************
  解除是
  7
  5
  10
  12
  //**********************************************/

#include <EEPROM.h>
#include <Keyboard.h>
#define computer 10          //开机
#define projector 11         //投影


//=============================================CONFIG===========================
unsigned long T = 60000;          //开投影后冷却关机
int N = 500;

//遥控器控制码
#define CTRLCODE_1   6  
#define CTRLCODE_2   170
#define CTRLCODE_3   186
