#include <EEPROM.h>
#include <Keyboard.h>

/*
  按键：1开机      2投影开     3投影关    4 播放space（响应）     5 停止ctrl s（响应）     6 暂停ctrl p（响应）     7、F9 音量加    8、F10音量减    9、F1关机
  接线：RX-无线模块、9-继电器-照明灯
*/

/*
  需要修改的地方：解除按键没法在第一页里修改和定义
  ——20190807
*/

/*
  当前解除码是
  8
  15
  10
  13
*/

#define zhaoming 9           //暂停计时

//===================================CONFIG===========================
//计次数
int N = 10;

//影片时长
unsigned long T = 5000;

//遥控器控制码
#define CTRLCODE_1   6
#define CTRLCODE_2   170
#define CTRLCODE_3   178
