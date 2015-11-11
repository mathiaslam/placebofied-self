#include "ESP8266.h"
#include <SoftwareSerial.h>

/***********************************************
SWITCH
***********************************************/

#define POS1  17
#define POS2  16
#define POS3  15
#define POS4  14
#define POS5  18
#define POS6  13
#define POS7  12
#define POS8  11
#define POS9  10
#define POS10 9

int position = 0;
boolean update = false;

/***********************************************/

// replace with your WiFi connection info
//#define WLAN_SSID "o2-WLAN04"
//#define WLAN_PASS "8EB6H797GW7893M9"

#define WLAN_SSID "o2-WLAN54"
#define WLAN_PASS "7739466441199644"

SoftwareSerial Serial1(19, 8);
ESP8266 wifi(Serial1);

void setup() {
  // SWITCH
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

  // WIFI
  Serial.begin(115200);
  Serial1.begin(9600);
  while (!Serial);
  Serial.println("I live!");
  restartESP();

}

void loop() {
  
  if (digitalRead(POS1) == LOW && position != 1)
  {
    Serial.println("pos 1");
    position = 1;
    update = true;
  }
  if (digitalRead(POS2) == LOW && position != 2)
  {
    Serial.println("pos 2");
    position = 2;
    update = true;
  }
  if (digitalRead(POS3) == LOW && position != 3)
  {
    Serial.println("pos 3");
      position = 3;
      update = true;
  }
  if (digitalRead(POS4) == LOW && position != 4)
  {
    Serial.println("pos 4");
     position = 4;
     update = true;
  }
  if (digitalRead(POS5) == LOW && position != 5)
  {
    Serial.println("pos 5");
     position = 5;
     update = true;
  }
  if (digitalRead(POS6) == LOW && position != 6)
  {
    Serial.println("pos 6");
     position = 6;
     update = true;
  }
  if (digitalRead(POS7) == LOW && position != 7)
  {
    Serial.println("pos 7");
     position = 7;
     update = true;
  }
  if (digitalRead(POS8) == LOW && position != 8)
  {
    Serial.println("pos 8");
     position = 8;
     update = true;
  }
  if (digitalRead(POS9) == LOW && position != 9)
  {
    Serial.println("pos 9");
     position = 9;
     update = true;
  }
  if (digitalRead(POS10) == LOW && position != 10)
  {
    Serial.println("pos 10");
     position = 10;
     update = true;
  }
  delay(3000);

  if (update == true){
   char getBuffer[256] = {'\0'};


    delay(1000);
    // check to see if the ESP8266 is still alive
    if (wifi.kick()) {
      wifi.createTCP("data.sparkfun.com", 80);

      sprintf(getBuffer, "GET /input/VGAoKDy1ZmSM9Xqv0bqJ?private_key=9YAG4yXkRrIw4rvdV6vo&placebo=%d\r\nHost: data.sparkfun.com\r\n\r\n",position);


      wifi.send((const uint8_t *)getBuffer, strlen(getBuffer));

      Serial.print(getBuffer);
      delay(100);
      wifi.releaseTCP();

      update = false;
    }
  }


 
  //  } else {
  //    wifi.restart();
  //       Serial.println("ESP8266 died; restarting\n");
  //    delay(30000);
  //    restartESP();
  //
  //    Serial.println("");
  //  }

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


