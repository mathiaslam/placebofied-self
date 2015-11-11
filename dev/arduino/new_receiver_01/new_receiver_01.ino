#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266_Simple.h>

#define ESP8266_SSID  "o2-WLAN54"
#define ESP8266_PASS  "7739466441199644"

ESP8266_Simple wifi(5,4);

float placebo;
String input;

void setup()
{
  Serial.begin(115200); 
  Serial.println("Placebofied Self - Scale");
  wifi.begin(9600);

  wifi.setupAsWifiStation(ESP8266_SSID, ESP8266_PASS, &Serial);
  
  Serial.println();
}

void loop()
{
  
  char buffer[250]; 
  
  memcpy(buffer, 0, sizeof(buffer));     // Ensure the buffer is empty first!
  strncpy_P(buffer, PSTR("/output/VGAoKDy1ZmSM9Xqv0bqJ.txt?private_keya9YAG4yXkRrIw4rvdV6vo"), sizeof(buffer)-1);
  
  strncpy_P(buffer+strlen(buffer), PSTR("&Millis="), sizeof(buffer)-strlen(buffer)-1);
  ltoa(millis(), buffer+strlen(buffer), 10); // Note "10" is Base10, not a length
 
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
  if(httpResponseCode == 200 || httpResponseCode == ESP8266_OK)
  {
    // Our request was successfull and the response can be found in the buffer
    Serial.println("OK");
    input += buffer;
    Serial.println("PLACEBO:");
    input.remove(0,24);
    input.remove(1,input.length());
    Serial.println(input);
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
    
 
  
  delay(5000);  
}
