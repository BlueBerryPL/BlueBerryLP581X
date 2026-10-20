#include "SimpleLP58XX.h"
#include <Arduino.h>
#include <Wire.h>

LP5815 LED(LP5815_STD_ADR);

void setup() {

  Wire.begin();

  LED.reset();

  LED.enable();

  LED.setInstantBlinking(true);

  delay(5000);

  LED.setInstantBlinking(false);

  LED.enableOutput();

  LED.setMaxCurrent(false);
  LED.setCurrent(100, 100, 100);

  LED.setPWM(100, 0, 0);
  LED.update();

  delay(5000);

  LED.setPWM(0, 100, 0);
  LED.update();

  delay(5000);

  LED.setPWM(0, 0, 110);
  LED.update();

  delay(5000);

  LED.reset();

  LED.enable();

  LED.enableOutput();

  LED.enableFade();
  LED.setFadeType(LINEAR);
  LED.setFadeTime(0.0);

  LED.setMaxCurrent();
  LED.setCurrent(100, 100, 100);
  LED.setPWM(100, 100, 100);

  LED.setWorkingMode(AUTOMATIC);
  LED.setOutEngine(ENGINE0, ENGINE1, ENGINE2);
  
  LED.setPatternPauseTime(PATTERN0, 1, 1);
  LED.setPatternRepeatTime(PATTERN0, 1);
  LED.setPWMPattern(PATTERN0, 0, 255, 100, 255, 0);
  LED.setPatternSloperTime(PATTERN0, 0.5, 0.5, 0.5, 0.5);
  
  LED.setPatternPauseTime(PATTERN1, 1, 1);
  LED.setPatternRepeatTime(PATTERN1, 1);
  LED.setPWMPattern(PATTERN1, 100, 255, 0, 255, 100);
  LED.setPatternSloperTime(PATTERN1, 0.5, 0.5, 0.5, 0.5);

  LED.setPatternPauseTime(PATTERN2, 1, 1);
  LED.setPatternRepeatTime(PATTERN2, 1);
  LED.setPWMPattern(PATTERN2, 0, 100, 255, 100, 0);
  LED.setPatternSloperTime(PATTERN2, 0.5, 0.5, 0.5, 0.5);

  LED.setEnginePatternOrder(ENGINE0, PATTERN0, PATTERN1, PATTERN2, PATTERN3);
  LED.enableEnginePatternOrder(ENGINE0, ENABLE, ENABLE, ENABLE, DISABLE);
  LED.setEngineRepeatTime(ENGINE0, 3);

  LED.setEnginePatternOrder(ENGINE1, PATTERN1, PATTERN2, PATTERN0, PATTERN3);
  LED.enableEnginePatternOrder(ENGINE1, ENABLE, ENABLE, ENABLE, DISABLE);
  LED.setEngineRepeatTime(ENGINE1, 3);

  LED.setEnginePatternOrder(ENGINE2, PATTERN2, PATTERN0, PATTERN1, PATTERN3);
  LED.enableEnginePatternOrder(ENGINE2, ENABLE, ENABLE, ENABLE, DISABLE);
  LED.setEngineRepeatTime(ENGINE2, 3);

  LED.update();

  LED.startAutonomousAnimation();

}

void loop() {

}