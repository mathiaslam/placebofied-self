#include "SevSeg.h"


//Create an instance of the object.
SevSeg myDisplay;

//Create global variables

int encoderPin1 = 2;
int encoderPin2 = 3;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

int count = 0;


void setup()
{
  Serial.begin (9600);

  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

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
  int segD = 16; //Pin 8
  int segE = 9; //Pin 2
  int segF = 4; //Pin 9
  int segG = 15; //Pin 7
  int segDP = 12; //Pin 5

  int numberOfDigits = 4; //Do you have a 1, 2 or 4 digit display?

  myDisplay.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);

  myDisplay.SetBrightness(10); //Set the display to 100% brightness level

}

void loop()
{
  char tempString[10];
  sprintf(tempString, "%4d", count);



  if (encoderValue >= 95 || encoderValue <= -95) {
    count++;
    Serial.println("Sprung" + count);
    encoderValue = 0;
    
    }
  
  
  Serial.println(encoderValue);


  myDisplay.DisplayString(tempString, 0);

}

void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}

