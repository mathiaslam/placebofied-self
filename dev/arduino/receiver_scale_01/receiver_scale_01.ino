#include "ESP8266.h"
#include <SoftwareSerial.h>
#include "HX711.h"

/***********************************************/

HX711 scale(2, 3);

// replace with your WiFi connection info
#define WLAN_SSID "o2-WLAN04"
#define WLAN_PASS "8EB6H797GW7893M9"
SoftwareSerial Serial1(5, 4);
ESP8266 wifi(Serial1);

float placebo;
 String input;



void setup() {

   Serial.begin(115200);
  Serial.println("HX711 Demo");

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided 
            // by the SCALE parameter (not set yet)  

  scale.set_scale(20700.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided 
            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");

  // WIFI

  Serial1.begin(9600);
  while (!Serial);
  Serial.println("I live!");
  restartESP();


    uint8_t getBuffer[512] = {0};

    // check to see if the ESP8266 is still alive
    if (wifi.kick()) {
      wifi.createTCP("data.sparkfun.com", 80);
      
      char *hello = "GET /output/VGAoKDy1ZmSM9Xqv0bqJ.txt?private_keya9YAG4yXkRrIw4rvdV6vo HTTP/1.1\r\nHost: data.sparkfun.com\r\n\r\n";
      
      wifi.send((const uint8_t*)hello, strlen(hello));

      uint32_t len = wifi.recv(getBuffer, sizeof(getBuffer), 500);
     
      
    if (len > 0) {
        Serial.print("Received:[");
        for(uint32_t i = 0; i < len; i++) {
            //Serial.print((char)getBuffer[i]);
            input += (char)getBuffer[i];

            
        }
        Serial.print("]\r\n");
    }

    delay(100);
      wifi.releaseTCP();
    //Serial.print("HIER IST DER TEXT:\r\n"); 
    //Serial.print(input);
    //Serial.print("HIER IST DER NEUE TEXT:\r\n"); 
    input.remove(0,290);
    input.remove(1,input.length());
    Serial.print(input);

    char floatbuf[32]; // make this at least big enough for the whole string
    input.toCharArray(floatbuf, sizeof(floatbuf));
      placebo = atof(floatbuf);

 
    
    //input = "";
    } 


  

}

void loop(void) {





         Serial.print("one reading:\t");
  Serial.print(scale.get_units()-placebo, 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 1);

  scale.power_down();              // put the ADC in sleep mode
  delay(5000);
  scale.power_up();

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

