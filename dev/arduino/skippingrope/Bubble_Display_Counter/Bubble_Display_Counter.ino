/*
 March 6, 2014
 Spark Fun Electronics
 Nathan Seidle
 Updates by Joel Bartlett
 
 This code is originally based Dean Reading's Library deanreading@hotmail.com
 http://arduino.cc/playground/Main/SevenSegmentLibrary
 He didn't have a license on it so I hope he doesn't mind me making it public domain: 
 This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 This sketch provides a simple counter example for the HP Bubble display from SparkFun.
 https://www.sparkfun.com/products/12710
 
 Pinout for HP Bubble Display:
 1:  Cathode 1
 2:  Anode E
 3:  Anode C
 4:  Cathode 3
 5:  Anode dp
 6:  Cathode 4
 7:  Anode G
 8:  Anode D
 9:  Anode F
 10: Cathode 2
 11: Anode B
 12: Anode A
 */

#include "SevSeg.h"
#define ENC_A 14
#define ENC_B 15
#define ENC_PORT PINC
 

//Create an instance of the object.
SevSeg myDisplay;

//Create global variables
unsigned long timer;
int deciSecond = 0;
int count;
char tempString[5] = {}; //Used for sprintf

void setup()
{

  /* Setup encoder pins as inputs */
  pinMode(ENC_A, INPUT);
  digitalWrite(ENC_A, HIGH);
  pinMode(ENC_B, INPUT);
  digitalWrite(ENC_B, HIGH);
  Serial.begin (115200);
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
       int segD = 3; //Pin 8
       int segE = 9; //Pin 2
       int segF = 4; //Pin 9
       int segG = 2; //Pin 7
       int segDP= 12; //Pin 5
   
  int numberOfDigits = 4; //Do you have a 1, 2 or 4 digit display?

  myDisplay.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  
  myDisplay.SetBrightness(100); //Set the display to 100% brightness level

  timer = millis();
}

void loop()
{

   static uint8_t counter = 0;      //this variable will be changed by encoder input
 int8_t tmpdata;
 /**/
  tmpdata = read_encoder();
  if( tmpdata ) {
    Serial.print("Counter value: ");
    Serial.println(counter, DEC);
    counter += tmpdata;
   
    tempString[0] = 58; 
      tempString[1] = 58;
      tempString[2] = counter;
      tempString[3] = 58;
   
  }

 myDisplay.DisplayString(tempString, 0);
  //Produce an output on the display


  delay(5);
}


/* Rotary encoder read example */
#define ENC_A 14
#define ENC_B 15
#define ENC_PORT PINC
 
/* returns change in encoder state (-1,0,1) */
int8_t read_encoder()
{
  static int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static uint8_t old_AB = 0;
  /**/
  old_AB <<= 2;                   //remember previous state
  old_AB |= ( ENC_PORT & 0x03 );  //add current state
  return ( enc_states[( old_AB & 0x0f )]);
}
