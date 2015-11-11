#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266_Simple.h>
#include "SevSeg.h"

SevSeg myDisplay;

int encoderPin1 = 2;
int encoderPin2 = 3;
long randomNumber;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

int counter = 0;
int placeboCount = 0;




//#define ESP8266_SSID "o2-WLAN04"
//#define ESP8266_PASS "8EB6H797GW7893M9"
//#define ESP8266_SSID  "o2-WLAN54"
//#define ESP8266_PASS  "7739466441199644"
//#define ESP8266_SSID  "123geheim"
//#define ESP8266_PASS  "123geheim"

#define ESP8266_SSID  "iPhone von Mathias"
#define ESP8266_PASS  "6cwzg0s7xfhuj"

ESP8266_Simple wifi(16, 17);

int placebo;




String input;



void setup()
{

  Serial.begin(115200);
  randomSeed(analogRead(0));

  //wifi.begin(9600);

  //wifi.setupAsWifiStation(ESP8266_SSID, ESP8266_PASS, &Serial);
  placebo = random(-5,5);
  Serial.print("placebo:");
  Serial.print(placebo);

  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

    int displayType = COMMON_CATHODE; //Your display is either common cathode or common anode

  
    //This pinout is for a bubble dispaly
       //Declare what pins are connected to the GND pins (cathodes)
       int digit1 = 9; //Pin 1
       int digit2 = 13; //Pin 10
       int digit3 = 6; //Pin 4
       int digit4 = 4; //Pin 6
       
       //Declare what pins are connected to the segments (anodes)
       int segA = 15; //Pin 12
       int segB = 14; //Pin 11
       int segC = 7; //Pin 3
       int segD = 11; //Pin 8
       int segE = 8; //Pin 2
       int segF = 12; //Pin 9
       int segG = 10; //Pin 7
       int segDP= 5; //Pin 5
   
  int numberOfDigits = 4; //Do you have a 1, 2 or 4 digit display?

  myDisplay.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  
  myDisplay.SetBrightness(100); //Set the display to 100% brightness level



  Serial.println("Ready");
  Serial.println();
  //TCPConnect();

   randomNumber = random(2,5);
  
  //display the random number on the serial monitor
  Serial.print("The Random Number is = ");
  Serial.println(randomNumber);
}

void loop()
{
  
   if (encoderValue >= 95 || encoderValue <= -95) {
    if (placeboCount >= 10) {
      counter += placebo;
      placeboCount = 0;
      Serial.write(counter);
    } else {
      counter++;
      placeboCount++;
    }
  
    Serial.println("Sprung:");
    Serial.println(counter);
    encoderValue = 0;
    
    }
    
    char tempString[10]; //Used for sprintf
  sprintf(tempString, "%4d", counter); //Convert deciSecond into a string that is right adjusted
  myDisplay.DisplayString(tempString, 0); //(numberToDisplay, decimal point location)
  


  

}


void TCPConnect() {

  char buffer[250];

  memcpy(buffer, 0, sizeof(buffer));     // Ensure the buffer is empty first!
  strncpy_P(buffer, PSTR("/output/VGAoKDy1ZmSM9Xqv0bqJ.txt?private_keya9YAG4yXkRrIw4rvdV6vo"), sizeof(buffer) - 1);

  strncpy_P(buffer + strlen(buffer), PSTR("&Millis="), sizeof(buffer) - strlen(buffer) - 1);
  ltoa(millis(), buffer + strlen(buffer), 10); // Note "10" is Base10, not a length

  Serial.print("Requesting ");
  Serial.print(buffer);
  Serial.print(": ");

  unsigned int httpResponseCode =
    wifi.GET
    (
      F("54.86.132.254"),     // The IP address of the server you want to contact
      80,                     // The Port to Connect to (80 is the usual "http" port)
      buffer,                 // Your buffer which currently contains the path to request
      sizeof(buffer),         // The size of the buffer
      F("data.sparkfun.com"), // Optional hostname you are connecting to(* see below)
      2                       // Get from line 2 of the body, no headers (use 0 to get headers)
      // responses often have a leading newline, hence starting
      // from line 2 here, adjust as necessary
    );

  // Now let's interpret the response code
  if (httpResponseCode == 200 || httpResponseCode == ESP8266_OK)
  {
    // Our request was successfull and the response can be found in the buffer
    Serial.println("OK");
    input += buffer;
    Serial.println("PLACEBO:");
    input.remove(0, 24);
    input.remove(1, input.length());
    Serial.println(input);
    char floatbuf[32]; // make this at least big enough for the whole string
    input.toCharArray(floatbuf, sizeof(floatbuf));
    placebo = atof(floatbuf);
    input = "";
    Serial.print("Placebo Value:");
    Serial.print(placebo);
  }
  else
  {
    // Oops, something went wrong.
    if (httpResponseCode < 100)
    {
      // And it's on our end, but what was it?  Well we can find out easily.
      wifi.debugPrintError((byte)httpResponseCode, &Serial);
    }
    else
    {
      // It's probably a server problem
      Serial.print("HTTP Status ");
      Serial.println(httpResponseCode);
    }
  }

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
