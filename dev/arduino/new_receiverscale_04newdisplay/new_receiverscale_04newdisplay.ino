#include <Arduino.h>
#include <SoftwareSerial.h>

#include "HX711.h"

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();


//#define ESP8266_SSID "o2-WLAN04"
//#define ESP8266_PASS "8EB6H797GW7893M9"
//#define ESP8266_SSID  "o2-WLAN54"
//#define ESP8266_PASS  "7739466441199644"
//#define ESP8266_SSID  "123geheim"
//#define ESP8266_PASS  "123geheim"

#define ESP8266_SSID  "iPhone von Mathias"
#define ESP8266_PASS  "6cwzg0s7xfhuj"


HX711 scale(17, 16);


const int knockSensor = A0;
const int threshold = 600;

int sensorReading = 0;
int placebo;
float placeboCalculate;
String input;
byte oldWeight = 0;
byte newWeight = 0;
byte endWeight = 0;

long previousMillis = 0;
long interval = 4000;
boolean waiting = false;

void setup()
{
#ifndef __AVR_ATtiny85__
  Serial.begin(19200);

#endif
  matrix.begin(0x70);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);


  Serial.begin(115200);
  Serial.println("Placebofied Self - Scale");
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

  wifi.begin(9600);

  //wifi.setupAsWifiStation(ESP8266_SSID, ESP8266_PASS, &Serial);
  digitalWrite(7, HIGH);

  Serial.println("Ready");
  Serial.println();
}

void loop()
{
  matrix.blinkRate(0);
  matrix.clear();
  matrix.writeDisplay();

  sensorReading = analogRead(knockSensor);
  if (sensorReading >= threshold) {
    matrix.print(0000, DEC);
    matrix.writeDisplay();


    Serial.println("Knock!");
    waiting = false;

    TCPConnect();


    unsigned long currentMillis = millis();
    previousMillis = currentMillis;

    while (waiting == false) {

      Serial.print("Placeboweight:");
      Serial.print(scale.get_units() - placebo, 1);

      matrix.print(scale.get_units() - placebo, 1);

      matrix.writeDisplay();


      newWeight = scale.get_units();

      if (oldWeight == newWeight)  {
        oldWeight = newWeight;
        matrix.writeDisplay();

        currentMillis = millis();
        if (currentMillis - previousMillis > interval) {
          previousMillis = currentMillis;
          waiting = true;
          endWeight = newWeight;
        }

      } else {
        oldWeight = newWeight;
        previousMillis = millis();
        matrix.writeDisplay();
      }



    }


    matrix.blinkRate(1);
    matrix.print(endWeight);
    matrix.writeDisplay();


    //Serial.print("\t| average:\t");
    //Serial.println(scale.get_units(10), 1);


    scale.power_down();              // put the ADC in sleep mode
    delay(5000);
    scale.power_up();
    Serial.println("Ready");
  }
  delay(100);  // delay to avoid overloading the serial port buffer

}


void TCPConnect() {

  char buffer[250];

  memcpy(buffer, 0, sizeof(buffer));     // Ensure the buffer is empty first!
  strncpy_P(buffer, PSTR("/output/VGAoKDy1ZmSM9Xqv0bqJ.txt?private_keya9YAG4yXkRrIw4rvdV6vo"), sizeof(buffer) - 1);

  strncpy_P(buffer + strlen(buffer), PSTR("&Millis="), sizeof(buffer) - strlen(buffer) - 1);
  ltoa(millis(), buffer + strlen(buffer), 10); // Note "10" is Base10, not a length

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
  if (httpResponseCode == 200 || httpResponseCode == ESP8266_OK)
  {
    // Our request was successfull and the response can be found in the buffer
    Serial.println("OK");
    input += buffer;
    Serial.println("PLACEBO:");
    input.remove(0, 24);
    input.remove(1, input.length());
    Serial.println(input);
    char floatbuf[32]; // make this at least big enough for the whole string
    input.toCharArray(floatbuf, sizeof(floatbuf));
    placebo = atof(floatbuf);


    switch (placebo) {
      case 0:    // your hand is on the sensor
        placeboCalculate = 5;
        break;
      case 1:    // your hand is close to the sensor
        placeboCalculate = -5;
        break;
      case 2:    // your hand is a few inches from the sensor
        placeboCalculate = -4;
        break;
      case 3:    // your hand is nowhere near the sensor
        placeboCalculate = -3;
        break;
      case 4:    // your hand is nowhere near the sensor
        placeboCalculate = -2;
        break;
      case 5:    // your hand is nowhere near the sensor
        placeboCalculate = -1;
        break;
      case 6:    // your hand is nowhere near the sensor
        placeboCalculate = 1;
        break;
      case 7:    // your hand is nowhere near the sensor
        placeboCalculate = 2;
        break;

      case 8:    // your hand is nowhere near the sensor
        placeboCalculate = 3;
        break;
      case 9:    // your hand is nowhere near the sensor
        placeboCalculate = 4;
        break;

    }


    input = "";
  }
  else
  {
    // Oops, something went wrong.
    if (httpResponseCode < 100)
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
