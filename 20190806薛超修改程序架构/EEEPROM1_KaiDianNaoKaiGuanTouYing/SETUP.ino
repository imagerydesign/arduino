void setup()
{
  pinMode(computer, OUTPUT);
  pinMode(projector, OUTPUT);
  digitalWrite(computer, HIGH);
  digitalWrite(projector, HIGH);
  Serial1.begin(9600);
  Keyboard.begin();
  //**************首次EEPROM清零*********************
  // for ( int i = 0 ; i < 10; i++ )
  //  EEPROM.write(i, 0);
  //*****************************************************
}
