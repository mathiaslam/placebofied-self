// Digital input pin definitions

#define POS1  15
#define POS2  2
#define POS3  3
#define POS4  4
#define POS5  5
#define POS6  6
#define POS7  7
#define POS8  8
#define POS9  9
#define POS10 10

int position = 0;

void setup() {
    Serial.begin(9600);
  // The switch pins
  pinMode(POS1,   INPUT_PULLUP);
  pinMode(POS2,   INPUT_PULLUP);
  pinMode(POS3,   INPUT_PULLUP);
  pinMode(POS4,   INPUT_PULLUP);
  pinMode(POS5,   INPUT_PULLUP);
  pinMode(POS6,   INPUT_PULLUP);
  pinMode(POS7,   INPUT_PULLUP);
  pinMode(POS8,   INPUT_PULLUP);
  pinMode(POS9,   INPUT_PULLUP);
  pinMode(POS10,  INPUT_PULLUP);


}

void loop() 
{
  if (digitalRead(POS1) == LOW && position != 1)
  {
    Serial.println("pos 1");
    position = 1;
  }
  if (digitalRead(POS2) == LOW && position != 2)
  {
    Serial.println("pos 2");
    position = 2;
  }
  if (digitalRead(POS3) == LOW && position != 3)
  {
    Serial.println("pos 3");
      position = 3;
  }
  if (digitalRead(POS4) == LOW && position != 4)
  {
    Serial.println("pos 4");
     position = 4;
  }
  if (digitalRead(POS5) == LOW && position != 5)
  {
    Serial.println("pos 5");
     position = 5;
  }
  if (digitalRead(POS6) == LOW && position != 6)
  {
    Serial.println("pos 6");
     position = 6;
  }
  if (digitalRead(POS7) == LOW && position != 7)
  {
    Serial.println("pos 7");
     position = 7;
  }
  if (digitalRead(POS8) == LOW && position != 8)
  {
    Serial.println("pos 8");
     position = 8;
  }
  if (digitalRead(POS9) == LOW && position != 9)
  {
    Serial.println("pos 9");
     position = 9;
  }
  if (digitalRead(POS10) == LOW && position != 10)
  {
    Serial.println("pos 10");
     position = 10;
  }
  delay(20);
}
