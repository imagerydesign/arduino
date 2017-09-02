#include "Mouse.h"
#define HWKG1 9           //红外开关1接9号引脚
#define HWKG2 10           //红外开关2接10号引脚
unsigned int i, mouseP = 0;
void setup() {
  // put your setup code here, to run once:
  Mouse.begin();
  //鼠标移到左下角1.3

}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(HWKG1) == LOW  ) //开关1被挡住
  {
    for (i = 0; i < 15; i++)
    {
      Mouse.move(-127 , 127);
      delay(50);
    }

    /*  //如果鼠标在右下角，把它移到左下角
      if(mouseP == 1)
      {
        Mouse.move(4000 , 0);
      }
    */
    Mouse.move(100 , -100);
    delay(500);
    Mouse.move(-20 , 20);

    /*delay(500);
      Mouse.move(-20 , 20);

      delay(500);
      Mouse.move(20 , -20);
    */
    delay(500);
    Mouse.move(20 , -20);



    mouseP = 0;
 




  }
  if (digitalRead(HWKG2) == LOW  ) //开关2被挡住


  {

    for (i = 0; i < 15; i++)
    {
      Mouse.move(127 , 127);
      delay(50);
    }
    /*//如果鼠标在左下角，把它移到右下角
      if(mouseP == 0)
      {
       Mouse.move(-4000 , 0);
      }
    */
    Mouse.move(-100 , -100);
    delay(500);
    Mouse.move(20 , 20);
    /*
        delay(500);
        Mouse.move(20 , 20);

        delay(500);
        Mouse.move(-20 , -20);
    */
    delay(500);
    Mouse.move(-20 , -20);



    mouseP = 1;





  }

}
