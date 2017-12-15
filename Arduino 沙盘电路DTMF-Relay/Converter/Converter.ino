void setup() {
  pinMode (2, INPUT);
  pinMode (3, INPUT);
  pinMode (4, INPUT);
  pinMode (5, INPUT);
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (9, OUTPUT);
  pinMode (10, OUTPUT);
  pinMode (11, OUTPUT);
  pinMode (12, OUTPUT);
  pinMode (13, OUTPUT);
Serial.begin(9600);
}

void loop() {
  int i=0,code=0,num=1;
  for (i=0;i<4;i++)
  {
    if (HIGH == digitalRead (i+2))
    {
      code +=num;
    }
    num *= 2;
  }
   Serial.println(code);
  if (code == 0)
  {
    digitalWrite (13, LOW);
  }
  else if (code < 9)
  {
    digitalWrite (5+code, HIGH);
  }
  else 
  {
    digitalWrite (code-3, LOW);
  }
  // put your main code here, to run repeatedly:

}
