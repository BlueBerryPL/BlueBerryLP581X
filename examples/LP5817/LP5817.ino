#include "SimpleLP58XX.h"
#include <Arduino.h>
#include <Wire.h>

LP5817 LED(LP5817_STD_ADR);

void setup() {

  Wire.begin();

  LED.reset();
  LED.enable();

  LED.enableOutput();

  LED.enableFade();
  LED.setFadeType(EXPONENTIAL);
  LED.setFadeTime(1.0);

  LED.setMaxCurrent(false);
  LED.setCurrent(100, 100, 100);

}

void loop() {

  LED.setPWM(200, 0, 0);
  LED.update();

  delay(1000);

  LED.setPWM(0, 200, 0);
  LED.update();

  delay(1000);

  LED.setPWM(0, 0, 200);
  LED.update();

  delay(1000);

}