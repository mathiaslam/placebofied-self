
#include <Phant.h>
#include "ESP8266.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); /* RX:D3, TX:D2 */
//ESP8266 wifi(mySerial);

#define SSID        "o2-WLAN04"
#define PASSWORD    "8EB6H797GW7893M9"

Phant phant("data.sparkfun.coma", "VGAoKDy1ZmSM9Xqv0bqJ", "9YAG4yXkRrIw4rvdV6vo");


void setup(void)
{
    Serial.begin(9600);
   
}

void loop(void)
{

 

  phant.add("placebo", 123123);


  Serial.println("----TEST URL-----");
  Serial.println(phant.url());

  Serial.println();

  //phant.add("placebo", 666);

  Serial.println("----HTTP POST----");
  //Serial.println(phant.post());
 
  Serial.println();

  Serial.println("----HTTP GET----");
  Serial.println(phant.post());

  Serial.println("----HTTP DELETE----");
  Serial.println(phant.clear());
  
  delay(10000);
}

