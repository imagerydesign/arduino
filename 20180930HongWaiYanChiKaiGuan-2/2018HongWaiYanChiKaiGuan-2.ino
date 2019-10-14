int inputPin = 8;
int outputPin = 12;

void setup() {
  pinMode (inputPin, INPUT);
  pinMode (outputPin, OUTPUT);
}

void loop() {
  int val = digitalRead (inputPin);
  if (val == HIGH)
  {
    digitalWrite (outputPin, HIGH);
    delay (200);
    digitalWrite (outputPin, LOW);
    delay (4800);
  }
}

