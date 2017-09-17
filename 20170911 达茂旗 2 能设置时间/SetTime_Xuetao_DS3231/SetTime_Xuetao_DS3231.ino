
#include <DS3231.h>
#include <Wire.h>

DS3231 Clock;
bool Century = false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;

byte year, month, date, DoW, hour, minute, second;

void setup() {

  Wire.begin();
  Clock.setSecond(0);//秒
  Clock.setMinute(59);//分
  Clock.setHour(23);  //小时
  Clock.setDate(11);  //日
  Clock.setMonth(9);  //月
  Clock.setYear(17);  //年

  Serial.begin(115200);
}
void ReadDS3231()
{
  int second, minute, hour, date, month, year, temperature;
  second = Clock.getSecond();
  minute = Clock.getMinute();
  hour = Clock.getHour(h12, PM);
  date = Clock.getDate();
  month = Clock.getMonth(Century);
  year = Clock.getYear();


  Serial.print("20");
  Serial.print(year, DEC);
  Serial.print('-');
  Serial.print(month, DEC);
  Serial.print('-');
  Serial.print(date, DEC);
  Serial.print(' ');
  Serial.print(hour, DEC);
  Serial.print(':');
  Serial.print(minute, DEC);
  Serial.print(':');
  Serial.print(second, DEC);
  Serial.print('\n');
}
void loop() {
  ReadDS3231(); delay(1000);

}

