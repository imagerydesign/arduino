
#include <DmxSimple.h>
#include <EEPROM.h>
#include <Keyboard.h>

struct LIGHTSEQ
{
  double startTime;
  double stopTime;
  int channel;
  int value;
  // unsigned long lastTime;
};
//========================================CONFIG===============================================
#define SEQNUM  7           //序列个数
#define CHANNELNUM  32      //通道个数

struct LIGHTSEQ lightSeq[SEQNUM] = //起始时间 终止时间 通道号 变化值
{
  {100.0, 100.0, 1, 0},
  {200.0, 100.0, 2, 255},
  {300.0, 300.0, 3, 255},
  {400.0, 400.0, 4, 255},
  {500.0, 600.0, 5, 255},
  {700.0, 8000.0, 1, 40},
  {8000.0, 114000.0, 1, 40},
};

//遥控器控制码
#define CTRLCODE_1   6  
#define CTRLCODE_2   170
#define CTRLCODE_3   186


