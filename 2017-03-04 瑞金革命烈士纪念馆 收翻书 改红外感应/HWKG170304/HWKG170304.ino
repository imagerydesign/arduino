#include "Mouse.h"
#define HWKG1 9           //红外开关1接9号引脚
#define HWKG2 10           //红外开关2接10号引脚
unsigned int mouseP=0;
void setup() {
  // put your setup code here, to run once:
 Mouse.begin();
 //鼠标移到左下角
 Mouse.move(10-512 , 600-384);
 mouseP=0;
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(HWKG1) == LOW  )//开关1被挡住
  {
        //如果鼠标在右下角，把它移到左下角
        if(mouseP == 1)
        {
          Mouse.move(-900 , 0);
        }

        delay(50);
        Mouse.move(20 , 20);

        delay(50);
        Mouse.move(20 , 20);

        delay(50);
        Mouse.move(-20 , -20);

        delay(50);
        Mouse.move(-20 , -20);


         
         mouseP=0;
        delay(300);
        



  }
  if(digitalRead(HWKG2) == LOW  )//开关2被挡住
  {
        //如果鼠标在左下角，把它移到右下角
        if(mouseP == 0)
        {
          Mouse.move(900 , 0);
        }

        delay(50);
        Mouse.move(20 , 20);

        delay(50);
        Mouse.move(20 , 20);

        delay(50);
        Mouse.move(-20 , -20);

        delay(50);
        Mouse.move(-20 , -20);


         
         mouseP=1;
        delay(300);
        



  }
  
}
