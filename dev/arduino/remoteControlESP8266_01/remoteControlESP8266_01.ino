#include "ESP8266.h"
#include <SoftwareSerial.h>


/***********************************************
encoder(will be replaced with a potentiometer)
***********************************************/

int encoderPin1 = 2;
int encoderPin2 = 3;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

/***********************************************/

// replace with your WiFi connection info
#define WLAN_SSID "o2-WLAN04"
#define WLAN_PASS "8EB6H797GW7893M9"
SoftwareSerial Serial1(5, 4);
ESP8266 wifi(Serial1);

int i = 1;
int encoderValueOld = encoderValue;



void setup() {
  // ENCODER
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);

  // WIFI
  Serial.begin(115200);
  Serial1.begin(9600);
  while (!Serial);
  Serial.println("I live!");
  restartESP();

}

void loop() {

  Serial.println("NEU:");
  Serial.println(encoderValue);

  Serial.println("ALT:");
  Serial.println(encoderValueOld);

  if (encoderValue != encoderValueOld) {


    char getBuffer[256] = {'\0'};


    delay(1000);
    // check to see if the ESP8266 is still alive
    if (wifi.kick()) {
      wifi.createTCP("data.sparkfun.com", 80);

      sprintf(getBuffer, "GET /input/VGAoKDy1ZmSM9Xqv0bqJ?private_key=9YAG4yXkRrIw4rvdV6vo&placebo=%d\r\nHost: data.sparkfun.com\r\n\r\n",encoderValue);


      wifi.send((const uint8_t *)getBuffer, strlen(getBuffer));

      Serial.print(getBuffer);
      delay(100);
      wifi.releaseTCP();

      encoderValueOld = encoderValue;
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
  delay(1000);
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

// Update Encoder
void updateEncoder() {
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}

