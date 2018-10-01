// The library toggles digital pin 4 in the sampling loop which allows
// measurement of the actual sampling frequency.
// If you call .sample() continuously like this:
// while(1)dtmf.sample(sensorPin);
// you can put a frequency counter on pin 4 to determine what the
// sampling frequency is on your Arduino. Note that the frequency
// counter will show half the actual rate. My meter showed 4.463kHz
// so the sampling rate is 8926Hz
#include <DTMF.h>
#define computer 2          //开机
#define projector 3         //投影
int sensorPin = A0;
int led = 13;


// NOTE that N MUST NOT exceed 160
// This is the number of samples which are taken in a call to
// .sample. The smaller the value of N the wider the bandwidth.
// For example, with N=128 at a sample rate of 8926Hz the tone
// detection bandwidth will be 8926/128 = 70Hz. If you make N
// smaller, the bandwidth increases which makes it harder to detect
// the tones because some of the energy of one tone can cross into
// an adjacent (in frequency) tone. But a larger value of N also means
// that it takes longer to collect the samples.
// A value of 64 works just fine, as does 128.
// NOTE that the value of N does NOT have to be a power of 2.
float n=128.0;
// sampling rate in Hz
float sampling_rate=8926.0;

// Instantiate the dtmf library with the number of samples to be taken
// and the sampling rate.
DTMF dtmf = DTMF(n,sampling_rate);

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(computer, OUTPUT);
  pinMode(projector, OUTPUT);
  Serial.begin(115200);
  //yaokong
  Serial1.begin(9600);
  Keyboard.begin();
}
int flag_projector = 0;
int nochar_count = 0;
float d_mags[8];
int anjian = 0;
void loop()
{
  
  //yaokeng
  if (Serial1.available() > 0) 
  {
    anjian = 0;
    anjian = Serial1.read();
    if(anjian == 6)
    {
      delay(5);
      anjian = Serial1.read();
      if(anjian == 160)
      {
        delay(5);
        anjian = Serial1.read();
        if(anjian == 142)
        {
          delay(5);
          anjian = Serial1.read();
          switch(anjian)
          {
            case  192:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            ////1#按键 
                             //开机
                             digitalWrite(computer,HIGH);
                             delay(100);						//延时100ms
                             digitalWrite(computer,LOW);	//
                             
                             Serial.println("//1#anjian ");
                        }
                        break;
            case  48:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //2#按键  
                           
                            if (flag_projector)
                            {
                               digitalWrite(projector,LOW);             //关投影
                               flag_projector = 0;
                            }
                            else
                            {
                              
                               digitalWrite(projector,HIGH);             //开投影
                               flag_projector = 1;
                            }
                            
                             Serial.println("//2#jian ");
                        }
                        break;
            case  240:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //3#jian 
                            Keyboard.press(KEY_LEFT_CTRL);
                            Keyboard.press(' ');		//向电脑发送向播放的指令
                            delay(50);		
                            Keyboard.releaseAll();
                            Serial.println("//3#jian ");
                        }
                        break;
            case  12:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //4#jian 
                             Keyboard.press(KEY_LEFT_CTRL);
                             //Keyboard.press('S');		//向电脑发送向停止的指令
                              Keyboard.press('f');	
                            delay(150);		
                            Keyboard.releaseAll();
                            Serial.println("//4#jian ");
                        }
                        break;
            case  63:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //5#jian 
                             Keyboard.press(KEY_LEFT_CTRL);
                             Keyboard.press('P');		//向电脑发送向停止的指令
                             	
                            delay(50);		
                            Keyboard.releaseAll();
                            Serial.println("//5#jian ");
                        }
                        break;
            case  60:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //6#jian 
                        }
                        break;
            case  252:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //7#jian 
                        }
                        break;
            case  3:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //8#jian 
                        }
                        break;
            case  195:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //9#jian 
                        }
                        break;
            case  243:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //10#jian 
                        }
                        break;
            case  51:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //11#jian 
                        }
                        break;
            case  15:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //12#jian 
                        }
                        break;
            case  255:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //13#jian 
                        }
                        break;
            case  207:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //14#jian 
                        }
                        break;
            case  204:
                        delay(5);
                        anjian = Serial1.read();
                        if(anjian == 0)
                        {
                            //15#jian 
                        }
                        break;
          }
        }
      }
    }
  }
  
  
  
  
  //*****************************************************************************************************************************
  
  
  
  
  //******************************************************************************************************************************
  char thischar;
  
  // This reads N samples from sensorpin (must be an analog input)
  // and stores them in an array within the library. Use while(1)
  // to determine the actual sampling frequency as described in the
  // comment at the top of this file
  /* while(1) */dtmf.sample(sensorPin);
  
  // The first argument is the address of a user-supplied array
  // of 8 floats in which the function will return the magnitudes
  // of the eight tones.
  // The second argument is the value read by the ADC when there
  // is no signal present. A voltage divider with precisely equal
  // resistors will presumably give a value of 511 or 512.
  // My divider gives a value of 506.
  // If you aren't sure what to use, set this to 512
  dtmf.detect(d_mags,506);

  // detect the button
  // If it is recognized, returns one of 0123456789ABCD*#
  // If unrecognized, returns binary zero

  // Pass it the magnitude array used when calling .sample
  // and specify a magnitude which is used as the threshold
  // for determining whether a tone is present or not
  //
  // If N=64 magnitude needs to be around 1200
  // If N=128 the magnitude can be set to 1800
  // but you will need to play with it to get the right value
  thischar = dtmf.button(d_mags,1800.);
  if(thischar) {
    
    
    
    /****************************************
   *****************DTMF************************** */
   switch(thischar)
   {
       case '1':
              Serial.print("!  ");
              break;
       case '2':
              Serial.print("@  ");
              break; 
       case '3':
              Serial.print("#  ");
              break;
       case '4':
              Serial.print("!  ");
              break;
       case '5':
              Serial.print("@  ");
              break; 
       case '6':
              Serial.print("#  ");
              break;       
       case '7':
              Serial.print("!  ");
              break;
       case '8':
              Serial.print("@  ");
              break; 
       case '9':
              Serial.print("#9  ");
              break;
       case '0':
              Serial.print("!0  ");
              break;
       case 'A':
              Serial.print("@A  ");
              break; 
       case 'B':
              Serial.print("#B  ");
              break; 
        case 'C':
              Serial.print("#C  ");
              break;
       case 'D':
              Serial.print("!D  ");
              break;
       case '#':
              Serial.print("@#  ");
              break;
       case '*':
              Serial.print("@*  ");
              break;          
   }
   // Serial.print(thischar);
    nochar_count = 0;
    //***************************************************************************************************
    //********************************************************************************************
    
    
    
    
    
    // Print the magnitudes for debugging
//#define DEBUG_PRINT
#ifdef DEBUG_PRINT
    for(int i = 0;i < 8;i++) {
      Serial.print("  ");
      Serial.print(d_mags[i]);
    }
    Serial.println("");
#endif
  } else {
    // print a newline 
    if(++nochar_count == 50)Serial.println("");
    // don't let it wrap around
    if(nochar_count > 30000)nochar_count = 51;
  }
}
