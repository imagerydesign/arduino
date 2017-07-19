/* 
* Arduino 远程唤醒电脑
 * Ricardo Dias
 * [url]http://ricardo-dias.com/[/url]
 * 内容翻译：shenhaiyu
 *
 * 本代码实现的功能是：一旦有按钮按下，
 * 立刻发送 "魔法包" 给待唤醒的局域网电脑。
 */ 
 
#include <Ethernet.h> 
#include <UdpRaw.h> 
 
// Arduino设置
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Arduino 的 MAC 地址
byte ip[] = { 192, 168, 1, 112 }; // Arduino 的 IP
byte gw[] = { 192, 168, 1, 254 }; // 网关 IP
int localPort = 8888; // 本地监听端口

// 目标主机
byte targetIp[] = { 192, 168, 1, 255 };
int targetPort = 5456;
byte wolMac[] = { 0x00,0x00,0x00,0x36,0x45,0xC1 }; // 目标电脑 MAC 地址

void setup() {
  Ethernet.begin(mac,ip,gw);
  UdpRaw.begin(localPort);

  // 当连接到 Pin 2 的按钮按下时，调用 sendPkt() 过程。
  attachInterrupt(0, sendPkt, RISING);
}

void loop() {
  delay(1);
}

void sendPkt(){
  // “魔法包”包括连续6个 0xFF 和 16个 MAc地址

  byte all[102];
  int i,c1,j=0;

  for(i = 0; i < 6; i++,j++){
    all[j] = 0xFF;
  }
  for(i = 0; i < 16; i++){
    for( c1 = 0; c1 < 6; c1++,j++)
      all[j] = wolMac[c1];
  }

  UdpRaw.sendPacket(all,102,targetIp,targetPort);
}

