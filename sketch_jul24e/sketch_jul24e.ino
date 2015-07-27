#include "ESP8266.h"
#include <SoftwareSerial.h>

// replace with your WiFi connection info
#define WLAN_SSID "o2-WLAN04"
#define WLAN_PASS "8EB6H797GW7893M9"
SoftwareSerial Serial1(3, 2);
ESP8266 wifi(Serial1);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(9600);   
  while (!Serial);      
  Serial.println("I live!");
  restartESP();
}

void loop() {
  static long startTime = millis();
  char getBuffer[256] = {'\0'};
  char getInput[256] = {'\0'};
  // check to see if the ESP8266 is still alive
  if (wifi.kick()) {
    wifi.createTCP("data.sparkfun.com", 80);
    long thisTime = millis();
    sprintf(getInput, "GET /output/VGAoKDy1ZmSM9Xqv0bqJ?private_key=9YAG4yXkRrIw4rvdV6vo&placebo\r\nHost: data.sparkfun.com\r\n\r\n",
      (thisTime - startTime)/1000, thisTime/1000); 
    //sprintf(getBuffer, "GET /output/VGAoKDy1ZmSM9Xqv0bqJ?private_key=9YAG4yXkRrIw4rvdV6vo&placebo=341\r\nHost: data.sparkfun.com\r\n\r\n",
    //  (thisTime - startTime)/1000, thisTime/1000);
    Serial.print("Starting send at "); Serial.println(millis());
   // wifi.send((const uint8_t *)getBuffer, strlen(getBuffer));
    wifi.send((const uint8_t *)getInput, strlen(getInput));

    delay(10);
  
  // Read all the lines of the reply from server and print them to Serial

    String line = wifi.readStringUntil('\r');
    Serial.print(line);
  
  
  Serial.println();
  Serial.println("closing connection");
    
    Serial.print("Ending send at "); Serial.println(millis());
    Serial.print(getBuffer);
    Serial.print(getInput);
    
    delay(100);
    wifi.releaseTCP();
  } else {
    wifi.restart();
       Serial.println("ESP8266 died; restarting\n");
    delay(30000);
    restartESP();
    startTime = millis();
    Serial.println("");
  }
  delay(1000);
}

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
