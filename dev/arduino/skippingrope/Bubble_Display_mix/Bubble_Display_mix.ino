#include "SevSeg.h"
#define ENC_A 14
#define ENC_B 15
#define ENC_PORT PINC


//Create an instance of the object.
SevSeg myDisplay;

//Create global variables
int deciSecond = 0;
int count = 0;

void setup()
{
  // Setup encoder pins as inputs
  pinMode(ENC_A, INPUT);
  digitalWrite(ENC_A, HIGH);
  pinMode(ENC_B, INPUT);
  digitalWrite(ENC_B, HIGH);
  Serial.begin (250000);
  Serial.println("Start");

  int displayType = COMMON_CATHODE; //Your display is either common cathode or common anode


  //This pinout is for a bubble dispaly
  //Declare what pins are connected to the GND pins (cathodes)
  int digit1 = 8; //Pin 1
  int digit2 = 5; //Pin 10
  int digit3 = 11; //Pin 4
  int digit4 = 13; //Pin 6

  //Declare what pins are connected to the segments (anodes)
  int segA = 7; //Pin 12
  int segB = 6; //Pin 11
  int segC = 10; //Pin 3
  int segD = 1; //Pin 8
  int segE = 9; //Pin 2
  int segF = 4; //Pin 9
  int segG = 0; //Pin 7
  int segDP = 12; //Pin 5

  int numberOfDigits = 4; //Do you have a 1, 2 or 4 digit display?

  myDisplay.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);

  myDisplay.SetBrightness(10); //Set the display to 100% brightness level

}

void loop()
{
  static uint8_t counter = 0;      //this variable will be changed by encoder input
  int8_t tmpdata;
  /**/
  tmpdata = read_encoder();
  char tempString[10];
  sprintf(tempString, "%4d", count);
  myDisplay.DisplayString(tempString, 0);


  if ( tmpdata ) {
    Serial.print("Counter value: ");
    Serial.println(counter, DEC);
    counter += tmpdata;

    if (counter == 100) {
      count++;
    }
  }

  myDisplay.DisplayString(tempString, 0);

}

int8_t read_encoder()
{
  static int8_t enc_states[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
  static uint8_t old_AB = 0;
  /**/
  old_AB <<= 2;                   //remember previous state
  old_AB |= ( ENC_PORT & 0x03 );  //add current state
  return ( enc_states[( old_AB & 0x0f )]);
}

void display() {


  //Example ways of displaying a decimal number
  char tempString[10]; //Used for sprintf
  sprintf(tempString, "%4d", count); //Convert deciSecond into a string that is right adjusted

  //Produce an output on the display
  myDisplay.DisplayString(tempString, 0); //(numberToDisplay, decimal point location)
}

