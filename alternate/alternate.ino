/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <SoftwareSerial.h>
#include <ESP8266wifi.h>

#define sw_serial_rx_pin 3 //  Connect this pin to TX on the esp8266
#define sw_serial_tx_pin 2 //  Connect this pin to RX on the esp8266
#define esp8266_reset_pin 5 // Connect this pin to CH_PD on the esp8266, not reset. (let reset be unconnected)

SoftwareSerial swSerial(sw_serial_rx_pin, sw_serial_tx_pin);
ESP8266wifi wifi(swSerial, swSerial, esp8266_reset_pin, Serial);//adding Serial enabled local echo and wifi debug

String inputString;
boolean stringComplete = false;
unsigned long nextPing = 0;
const char* ssid     = "your-ssid";
const char* password = "your-password";

const char* host = "data.sparkfun.com";
const char* streamId   = "....................";
const char* privateKey = "....................";

void setup() {
  inputString.reserve(20);
  swSerial.begin(9600);
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("Starting wifi");

  wifi.setTransportToTCP();// this is also default
  // wifi.setTransportToUDP();//Will use UDP when connecting to server, default is TCP

  wifi.endSendWithNewline(true); // Will end all transmissions with a newline and carrage return ie println.. default is true

  wifi.begin();

  //Turn on local ap and server (TCP)
  wifi.startLocalAPAndServer("MY_CONFIG_AP", "password", "5", "2121");

  wifi.connectToAP("wifissid", "wifipass");
  wifi.connectToServer("192.168.0.28", "2121");
  wifi.send(SERVER, "ESP8266 test app started");
}

int value = 0;

void loop() {

  

 
}

