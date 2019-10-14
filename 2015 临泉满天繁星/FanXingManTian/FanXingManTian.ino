
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
    ledVal[i] = 0;
  }
 Serial.begin(9600); 
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
            {
              Serial.println(micros());
              if( (micros()/10) % 2 == 0)
                 {
                    Serial.println(micros()/10%2);
                   digitalWrite(LED1,HIGH);
                 }
           
              else
                digitalWrite(LED1,LOW);
            }
            if(Flash % 3 < 1)
           {
              if( micros() % 3 == 0)
                digitalWrite(LED3,HIGH);
              else
                digitalWrite(LED3,LOW);
            }
            if(Flash % 5 < 2)
            {
              if( micros() % 3 == 0)
                digitalWrite(LED6,HIGH);
              else
                digitalWrite(LED6,LOW);
            }
             if(Flash % 7 < 2)
            {
              if( micros() % 3 == 0)
                digitalWrite(LED7,HIGH);
              else
                digitalWrite(LED7,LOW);
            }
            if(Flash % 11 < 3)
            {
             if( micros() % 3 == 0)
                digitalWrite(LED11,HIGH);
              else
                digitalWrite(LED11,LOW);
            }
            if(Flash % 13 < 5)
            {
              if( micros() % 3 == 0)
                digitalWrite(LED12,HIGH);
              else
                digitalWrite(LED12,LOW);
           }
          }
  
  
  

  numb++;
  delay(2);

}



void breath(int LED, int FLAG)
{
    if(Flag[FLAG] == 0)
  {
    ledVal[FLAG]++;
    if (ledVal[FLAG] >= 255)
      Flag[FLAG] = 1;
    else if(ledVal[FLAG] >= 0)
     analogWrite(LED,ledVal[FLAG]);
  }
  else
  {
    ledVal[FLAG]--;
    if (ledVal[FLAG] <= (-255))
      Flag[FLAG] = 0;
      else if(ledVal[FLAG] >= 0)
     analogWrite(LED,ledVal[FLAG]);
  }

}
