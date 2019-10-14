/******************************************************************************
----------------本例程仅供学习使用，未经作者允许，不得用于其他用途。-----------
------------------------版权所有，仿冒必究！-----------------------------------
----------------1.开发环境:Arduino IDE-----------------------------------------
----------------2.测试使用开发板型号：Arduino Leonardo or Arduino UNO R3-------
----------------3.单片机使用晶振：16M------------------------------------------
----------------4.淘宝网址：Ilovemcu.taobao.com--------------------------------
----------------------------epic-mcu.taobao.com--------------------------------
----------------5.作者：神秘藏宝室---------------------------------------------
******************************************************************************/
#define LED1 2
#define LED2 3      //
#define LED3 4
#define LED4 5      //
#define LED5 6      //
#define LED6 7
#define LED7 8
#define LED8 9      //
#define LED9 10      //
#define LED10 11    // shiftOut
#define LED11 12
#define LED12 13
//float sinVal;
int ledVal[12] ;
int numb = 1;
int Flag[12];
int Flash = 0;

void setup()
{
  pinMode(LED1,OUTPUT);		//IO输出
  pinMode(LED2,OUTPUT);	
  pinMode(LED3,OUTPUT);		//IO输出
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);		//IO输出
  pinMode(LED6,OUTPUT);
  pinMode(LED7,OUTPUT);		//IO输出
  pinMode(LED8,OUTPUT);
  pinMode(LED9,OUTPUT);		//IO输出
  pinMode(LED10,OUTPUT);
  pinMode(LED11,OUTPUT);		//IO输出
  pinMode(LED12,OUTPUT);
  for (int i = 0;i<12;i++)
  {
    Flag[i] = 0;
  }
}

void loop()
{
  
          breath(LED2,1);
         
          if(numb % 2 == 0)
          {
             breath(LED4 ,3);
          }
         
          
          if(numb % 3 == 0)
          {
            breath(LED5,4);
          }
         
          
          if(numb % 5 == 0)
          {
            breath(LED8,7);
          }
         
          
          if(numb % 7 == 0)
          {
            breath(LED9,8);
          }
         
          if(numb % 11== 0)
          {
            breath(LED10,9);
          }
          if(numb == 500)
          {
            Flash++;
            numb = 0;
            if(Flash % 2 < 1)
            //{
             // if( micros() % 2 == 0)
                digitalWrite(LED1,HIGH);
              else
                digitalWrite(LED1,LOW);
           // }
            if(Flash % 3 < 1)
          // {
            //  if( micros() % 2 == 0)
                digitalWrite(LED3,HIGH);
              else
                digitalWrite(LED3,LOW);
           // }
            if(Flash % 5 < 2)
           // {
           //   if( micros() % 2 == 0)
                digitalWrite(LED6,HIGH);
              else
                digitalWrite(LED6,LOW);
           // }
             if(Flash % 7 < 2)
           // {
            //  if( micros() % 2 == 0)
                digitalWrite(LED7,HIGH);
              else
                digitalWrite(LED7,LOW);
           // }
            if(Flash % 11 < 3)
         //   {
          //    if( micros() % 2 == 0)
                digitalWrite(LED11,HIGH);
              else
                digitalWrite(LED11,LOW);
         //   }
            if(Flash % 13 < 5)
         //   {
         //     if( micros() % 2 == 0)
                digitalWrite(LED12,HIGH);
              else
                digitalWrite(LED12,LOW);
        //    }
          }
  
  
  

  numb++;
  delay(2);
 /* 
  for(int x=0; x<180; x++)
  {
    sinVal = sin(x*(3.1412/180));
    ledVal = int(sinVal*255);
 
  analogWrite(LED12,ledVal);				//PWM调光，输出PWM,占空比为PotBuffer/255
  delay(15);
   }*/
}



void breath(int LED, int FLAG)
{
    if(Flag[FLAG] == 0)
  {
    ledVal[FLAG]++;
    if (ledVal[FLAG] >= 255)
      Flag[FLAG] = 1;
    
  }
  else
  {
    ledVal[FLAG]--;
    if (ledVal[FLAG] <= 0)
      Flag[FLAG] = 0;
  }
   analogWrite(LED,ledVal[FLAG]);
  // return FLAG;
  /**/
}
