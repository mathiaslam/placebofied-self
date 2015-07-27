#include <ESPhant.h>
#include <ESP8266.h>

#include <SoftwareSerial.h>

// ESP8266 Wi-Fi module
// RX, TX, RESET (baudrate / old firmware)
ESP8266 esp8266(2, 3, 4, 9600); 

// Arduino example stream
// https://data.sparkfun.com/placebo
// hostname, public key, private key
ESPhant esphant("data.sparkfun.coma", "VGAoKDy1ZmSM9Xqv0bqJ", "9YAG4yXkRrIw4rvdV6vo");

void setup() {
  Serial.begin(9600);

  if (esp8266.connect("o2-WLAN04", "8EB6H797GW7893M9")) {
    Serial.println("Connected to network.");
  } else {
    Serial.println("Error connecting to network.");
    while(1);
  }
}

void loop() {
  esphant.add("placebo", 12341);

  if (esp8266.send(esphant)) {
    Serial.println("Logged Data");
  } else {
    Serial.println("Error logging data.");
  }

  esphant.clear();
  delay(2000);
}
