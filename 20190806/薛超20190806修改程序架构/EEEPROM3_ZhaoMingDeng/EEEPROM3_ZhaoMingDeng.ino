#include <EEPROM.h>
#include <Keyboard.h>

//按键 1开机      2投影开     3投影关    4 播放space     5 停止ctrl s     6 暂停ctrl p     7、F9 音量加    8、F10音量减    9、关机F1
//接线 无线模块-RX 主机-10-继电器-开机线 投影-11-继电器-牛逼遥控器   照明灯---9
/**********************************************
  解除是
  8
  15
  10
  13
//**********************************************/

#define zhaoming 9           //暂停计时
#define computer 10          //开机
#define projector 11         //投影
//===================================CONFIG=========================== 
int N = 500;
unsigned long T = 114000;          //影片时长

//遥控器控制码
#define CTRLCODE_1   6  
#define CTRLCODE_2   170
#define CTRLCODE_3   178



