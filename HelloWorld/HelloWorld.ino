

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266_Simple.h>
#include "SevSeg.h"

// These are the SSID and PASSWORD to connect to your Wifi Network
//  put details appropriate for your network between the quote marks,
//  eg  #define ESP8266_SSID "YOUR_SSID"
#define ESP8266_SSID  "o2-WLAN54"
#define ESP8266_PASS  "7739466441199644"

// Create the ESP8266 device on pins 
//   8 for Arduino RX (TX on ESP connects to this pin) 
//   9 for Arduino TX (RX on ESP connects to this pin)
//
// REMEMBER!  The ESP8266 is a 3v3 device, if your arduino is 
//   5v powered, you MUST "level shift" TX/RX to 3v3, a zener 
//   like this will work, do it for both TX and RX
//
// [ARDUINO 8] => [1k Resistor] => + => [ESP8266 TX]
//                                 |
//                                 + => [(cathode) 3v3 Zener Diode (anode) ] => GROUND
//
// [ARDUINO 9] => [1k Resistor] => + => [ESP8266 RX]
//                                 |
//                                 + => [(cathode) 3v3 Zener Diode (anode) ] => GROUND
//
// The ESP8266 RST pin and CH_PD pin must both be connected to 3v3 
// (best via a 1k resistor).  The PWR must go to 3v3, and GND to
//  ground of course.   The other pins can be left floating for 
//  normal operation.

ESP8266_Simple wifi(19, 18);

SevSeg sevseg;

String input;
int time;

long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 3000;           // interval at which to blink (milliseconds)


void setup()
{
      byte numDigits = 4;
  byte digitPins[] = {12, 13, 2, 3};
  byte segmentPins[] = {4, 5, 6, 7, 8, 9, 10, 11};

  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  // As usual, we will output debugging information to the normal
  // serial port, the wifi runs on SoftwareSerial using the pins 
  // set above so it does not interfere with your normal debugging.
  Serial.begin(115200); // Reduce this if your Arduino has trouble talking so fast
  Serial.println("ESP8266 Demo Sketch");

  // Set the baud rate, this depends on your ESP8266's previous setup
  // as it remembers the rate.  9600 is the default for recent firmware
  // and is the recommended speed since we will be using SoftwareSerial
  // to communicate with it.
  wifi.begin(9600);
  
  // Connect to the given Wifi network as a station (as opposed to an 
  // Access Point running it's own Wifi network).
  //
  // See how &Serial is passed, the library will print status and debug
  // information there when it is connecting. 
  //
  // Note that this will not return until it has successfully connected,
  // it will just keep retrying.  I like to keep things simple!  
  wifi.setupAsWifiStation(ESP8266_SSID, ESP8266_PASS, &Serial);
  
  // A blank line just for debug formatting 
  Serial.println();
  
    TCPConnect();
}

void loop()
{
  
  // Ok, let's do a request, first we need a buffer
  //  the buffer must be big enough to hold the data you want to get back
  //  it is also used to hold the request path (no sense wasting SRAM for 
  //  two buffers) before the data is read.  If the data we get back
  //  is larger than the buffer, no problem, you just won't get all the data.
  

    
 sevseg.setNumber(time, 2);
sevseg.refreshDisplay();
//Serial.println(time);

unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

   Serial.println("hello");
     //  TCPConnect();
     time +=1;
 
  }
}

void TCPConnect() {
  char buffer[250]; // Remember, SRAM is very limited, think carefully about
                    // how big a buffer you really need!

  
  // Now we copy the request path into the buffer.  In this case, the request
  // path is a fixed string, so I store it in FLASH with PSTR and copy it into
  // the buffer with strncpy_P, taking care to leave at least one byte for 
  // the null string terminator.
  memcpy(buffer, 0, sizeof(buffer));     // Ensure the buffer is empty first!
  strncpy_P(buffer, PSTR("/placebofied/time.php"), sizeof(buffer)-1);
  
  // For fun, let's add a variable parameter to our fixed request path, first the
  // parameter name itself, which is fixed we will store in FLASH, and then
  // and then our value, in this case the result of millis which we insert
  // into the string with ltoa();
  //strncpy_P(buffer+strlen(buffer), PSTR("&Millis="), sizeof(buffer)-strlen(buffer)-1);
  //ltoa(millis(), buffer+strlen(buffer), 10); // Note "10" is Base10, not a length
    
  // Now we can send the http request and get it's HTTP Response Code If Possible
  //  Common response codes: 200 = OK
  //                         404 = FILE NOT FOUND
  //                         500 = SERVER ERROR
  //
  //  We may also give you a response code below 100, this indicates 
  //     0    = unknown status, but we sent the request OK, so it's probably 200
  //     1-99 = some sort of comms error in making the request
  Serial.print("Requesting ");
  Serial.print(buffer);
  Serial.print(": ");
  
  unsigned int httpResponseCode = 
    wifi.GET
    (
      F("95.143.172.115"),     // The IP address of the server you want to contact
      80,                     // The Port to Connect to (80 is the usual "http" port)
      buffer,                 // Your buffer which currently contains the path to request
      sizeof(buffer),         // The size of the buffer
      F("www.mathiaslam.de"), // Optional hostname you are connecting to(* see below)
      2                       // Get from line 2 of the body, no headers (use 0 to get headers)
                              // responses often have a leading newline, hence starting 
                              // from line 2 here, adjust as necessary
    );
  
  // Now let's interpret the response code
  if(httpResponseCode == 200 || httpResponseCode == ESP8266_OK)
  {
    // Our request was successfull and the response can be found in the buffer
    Serial.println("OK");
    input += buffer;
    input.remove(0, 15);
    input.remove(4,input.length());
    
      Serial.println(input);
      
      
         char floatbuf[32]; // make this at least big enough for the whole string
    input.toCharArray(floatbuf, sizeof(floatbuf));
    time = atof(floatbuf);
    input = ""; 
  }
  else
  {
    // Oops, something went wrong.
    if(httpResponseCode < 100)
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
