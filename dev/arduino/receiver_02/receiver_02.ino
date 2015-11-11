#include "ESP8266.h"
#include <SoftwareSerial.h>

/***********************************************/

//HH
//#define WLAN_SSID "o2-WLAN04"
//#define WLAN_PASS "8EB6H797GW7893M9"

//HB
#define WLAN_SSID "o2-WLAN54"
#define WLAN_PASS "7739466441199644"

/***********************************************/
SoftwareSerial Serial1(5, 4);
ESP8266 wifi(Serial1);


 String input;



void setup() {

  // WIFI
  Serial.begin(115200);
  Serial1.begin(9600);
  while (!Serial);
  Serial.println("I live!");
  restartESP();

}

void loop(void) {

    uint8_t getBuffer[512] = {0};

    // check to see if the ESP8266 is still alive
    if (wifi.kick()) {
      wifi.createTCP("data.sparkfun.com", 80);
      
      char *hello = "GET /output/VGAoKDy1ZmSM9Xqv0bqJ.txt?private_keya9YAG4yXkRrIw4rvdV6vo HTTP/1.1\r\nHost: data.sparkfun.com\r\n\r\n";


      wifi.send((const uint8_t*)hello, strlen(hello));
      delay(5000);

      uint32_t len = wifi.recv(getBuffer, sizeof(getBuffer));
     
      
    if (len > 0) {
        Serial.print("Received:[");
        for(uint32_t i = 0; i < len; i++) {
            //Serial.print((char)getBuffer[i]);
            input += (char)getBuffer[i];

            
        }
        Serial.print("]\r\n");
    }

   if (wifi.releaseTCP()) {
      Serial.print("release tcp ok\r\n");
    } else {
      Serial.print("release tcp err\r\n");
    }
    //Serial.print("HIER IST DER TEXT:\r\n"); 
    //Serial.print(input);
    //Serial.print("HIER IST DER NEUE TEXT:\r\n"); 
    //input.remove(0,290);
    //input.remove(1,input.length());
    Serial.print(input);

    
    //input = "";
    } 
  delay(10000);
}

// Restart ESP
void restartESP (void) {
  Serial.print("FW Version:");
  Serial.println(wifi.getVersion().c_str());
  if (wifi.setOprToStation()) {
    Serial.print("to station ok\r\n");
  } else {
    Serial.print("to station err\r\n");
  }
  if (wifi.joinAP(WLAN_SSID, WLAN_PASS)) {
    Serial.print("Join AP success\r\n");
    Serial.print("IP:");
    Serial.println( wifi.getLocalIP().c_str());
  } else {
    Serial.print("Join AP failure\r\n");
  }
  if (wifi.disableMUX()) {
    Serial.print("single ok\r\n");
  } else {
    Serial.print("single err\r\n");
  }
  Serial.print("setup end\r\n");
}

