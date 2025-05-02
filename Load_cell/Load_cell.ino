#include <Arduino.h>
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
int MeasureTime;
HX711 scale;

void setup() {
  Serial.begin(9600);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  
  //scale.set_scale(-459.542);
  scale.set_scale(-1084.53);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0
  Serial.println("Times,Measures");
}

void loop() {
  MeasureTime = millis();
  Serial.print(MeasureTime);
  Serial.print(",");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
  // by the SCALE parameter set with set_scale
}
