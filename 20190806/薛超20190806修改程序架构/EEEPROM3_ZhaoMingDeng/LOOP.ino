//***********************************
int Flag_pass = 0, pass;
int spaceTime = 0;//Times of Spaces;


int Flag_computer = 0, Flag_play = 0;
int nochar_count = 0;
unsigned long tim = 0 , now = 0, shichang = 0;
int anjian = 0;
//**********************************



void loop()
{
  /////////////////////////////////////////////////////////////////////////////////////////
  now = millis();
  if (Flag_play == 0) {
    tim = now;
  }
  if (shichang +  now - tim >= T)
  {
    digitalWrite(zhaoming, LOW);
    Flag_play = 0;
    shichang = 0;
  }
  else {
    //shichang = shichang + now -tim;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////
  if (Serial1.available() > 0)
  {
    anjian = 0;
//==================判断是否为照明灯遥控器->
    anjian = Serial1.read();
    if (anjian == CTRLCODE_1) //串口第1个数字
    {
      delay(5);
      anjian = Serial1.read();
      if (anjian == CTRLCODE_2) //串口第2个数字
      {
        delay(5);
        anjian = Serial1.read();
        if (anjian == CTRLCODE_3) //串口第3个数字
        {
          delay(5);       
//<-判断是否为照明灯遥控器==================

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
                if (!Flag_computer) {
                  digitalWrite(computer, LOW);
                  delay(100);            //延时100ms
                  digitalWrite(computer, HIGH); //
                  Flag_computer = 1;
                }
                Serial.println("//1#jian ");
              }
              break;
            case  48://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                digitalWrite(projector, LOW);            //开投影
                Serial.println("//2#jian");
              }
              break;
            case  240://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //3#jian
                digitalWrite(projector, HIGH);            //关投影
                Serial.println("//3#jian ");
              }
              break;
            case  12://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //4#jian
                if (pass == 1 || spaceTime < N)
                {
                  //Keyboard.press(' ');    //向电脑发送向播放的指令
                  delay(50);
                  //Keyboard.releaseAll();
                  tim = millis();
                  Flag_play = 1;


                  digitalWrite(zhaoming, HIGH);
                }
                Serial.println("//4#jian ");
                //**********************************************************************************************
                spaceTime = EEPROM.read(0);
                pass = EEPROM.read(1);
                if (pass == 0 && spaceTime < N)
                {
                  //Times of spaces plus 1;
                  spaceTime += 1;
                  EEPROM.write(0, spaceTime);

                }
                //**********************************************************************************************
              }
              break;
            case  63://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //5#jian
                if (pass == 1 || spaceTime < N)
                {
                  //Keyboard.press(KEY_LEFT_CTRL);
                  delay(50);
                  //Keyboard.press('s');    //向电脑发送向停止的指令
                  //delay(50);
                  //Keyboard.releaseAll();
                  Flag_play = 0;
                  digitalWrite(zhaoming, LOW);

                  shichang = 0;
                }
                Serial.println("//5#jian ");

              }
              break;

            case  60:
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //6#jian
                if (pass == 1 || spaceTime < N)
                {
                  //Keyboard.press(KEY_LEFT_CTRL);
                  delay(50);
                  //Keyboard.press('p');    //向电脑发送暂停的指令

                  //delay(50);
                  //Keyboard.releaseAll();


                  if ( Flag_play == 1)
                  {
                    shichang = shichang + now - tim;
                    Flag_play = 0;

                  }


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

                if (pass == 1 || spaceTime < N)
                {
                  //Keyboard.press(KEY_F10);      //向电脑发送音量减的指令
                  //delay(50);
                  //Keyboard.releaseAll();

                  //Keyboard.press(KEY_F10);      //向电脑发送音量减的指令
                  //delay(50);
                  //Keyboard.releaseAll();

                  //Keyboard.press(KEY_F10);      //向电脑发送音量减的指令
                  //delay(50);
                  //Keyboard.releaseAll();

                  //Keyboard.press(KEY_F10);      //向电脑发送音量减的指令
                  //delay(50);
                  //Keyboard.releaseAll();

                  //Keyboard.press(KEY_F10);      //向电脑发送音量减的指令
                  delay(50);
                  //Keyboard.releaseAll();
                }
                Serial.println("//7#jian ");
              }
              break;
            case  3://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //8#jian

                if (pass == 1 || spaceTime < N)
                {
                  //Keyboard.press(KEY_F9);   //向电脑发送音量减的指令
                  delay(50);
                  //Keyboard.releaseAll();

                  //Keyboard.press(KEY_F9);   //向电脑发送音量减的指令
                  //delay(50);
                  //Keyboard.releaseAll();

                  //Keyboard.press(KEY_F9);   //向电脑发送音量减的指令
                  //delay(50);
                  //Keyboard.releaseAll();

                  //Keyboard.press(KEY_F9);   //向电脑发送音量减的指令
                  //delay(50);
                  //Keyboard.releaseAll();

                  //Keyboard.press(KEY_F9);   //向电脑发送音量减的指令
                  //delay(50);
                  //Keyboard.releaseAll();
                }

                Serial.println("//8#jian ");
                //*****************************************************
                if (Flag_pass == 0)
                  Flag_pass = 1;
                //********************************************************
              }
              break;
            case  195://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //9#jian
                //Keyboard.press(KEY_F1);    //向电脑发送关机指令
                //delay(50);
                //Keyboard.releaseAll();
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
                Serial.println("//12#jian ");
              }
              break;
            case  255://串口第4个数字
              delay(5);
              anjian = Serial1.read();
              if (anjian == 0)
              {
                //13#jian
                //*****************************
                if (Flag_pass == 3)
                {

                  EEPROM.write(1 , 1);
                  Serial.print("JieMaChengGong");

                }
                else
                  Flag_pass = 0;
                //*****************************
                Serial.println("//13#jian ");
                Serial.print("ShiYongCiShu:");
                Serial.println(spaceTime);
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
                //********************************************************
                if (Flag_pass == 1)
                  Flag_pass = 2;
                else
                  Flag_pass = 0;
                //****************************************************
                Serial.println("//15#jian ");
              }
              break;
          }
        }
      }
    }
  }
}

