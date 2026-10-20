#include "SimpleLP58XX.h"
#include <Arduino.h>
#include <Wire.h>

  LP58XX::LP58XX(uint8_t I2C_SCL, uint8_t I2C_SDA) {
    _SCL = I2C_SCL;
    _SDA = I2C_SDA;
}

  void LP58XX::begin() {
    Wire.begin();
}

  uint8_t LP58XX::readRegister(uint8_t address, uint8_t registerAddress) {
    Wire.beginTransmission(address);  // Start comunication with slave 
    Wire.write(registerAddress);  // Get to the register
    Wire.endTransmission(false);  // Refresh the connection
    Wire.requestFrom(address, (uint8_t)1); // Ask for 1 byte of data
    return Wire.read();
  }

  void LP58XX::writeRegister(uint8_t address, uint8_t registerAddress, uint8_t value) {
    Wire.beginTransmission(address);
    Wire.write(registerAddress);
    Wire.write(value);
    Wire.endTransmission();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////

  LP5817::LP5817(uint8_t adressOfDevice) : LP58XX(_SCL, _SDA) { // Object LP58XX has to be created here directly
    _address = adressOfDevice;
  }

  void LP5817::enable() {
    uint8_t registerValue = readRegister(_address, CHIP_EN);
    registerValue = (registerValue & 0xFE) | (1 * 0x01); // Enables the last bit
    writeRegister(_address, CHIP_EN, registerValue);
  }

  void LP5817::disable() {
    uint8_t registerValue = readRegister(_address, CHIP_EN);
    registerValue = (registerValue & 0xFE) | (0 * 0x01); // Disables the last bit
    writeRegister(_address, CHIP_EN, registerValue);
  }

  void LP5817::reset() {
    writeRegister(_address, RESET_CMD, RESET_WORD);
  }

  void LP5817::update() {
    writeRegister(_address, UPDATE_CMD, UPDATE_WORD);
  }

  void LP5817::setMaxCurrent(bool maxCurrent) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG0);
      if (maxCurrent == false) {
    registerValue = (registerValue & 0xFE) | (0 * 0x01); // Disables the last bit
      }
      else {
    registerValue = (registerValue & 0xFE) | (1 * 0x01); // Disables the last bit
      }
    writeRegister(_address, DEV_CONFIG0, registerValue);
  }

  void LP5817::enableOutput(int firstOutput, int secondOutput, int thirdOutput) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG1);
    int sum = 0;
      if (firstOutput == false && secondOutput == false && thirdOutput == false) {  // If all variables are not set or set ALL / Drive all outputs
        sum = 0;
      }
      if (firstOutput != false && secondOutput == false && thirdOutput == false) {
        sum = firstOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD;
      }
    switch (sum) {
      case 0:
        registerValue = (registerValue & 0xF8) | (1 * 0x07);  // Set register value to XXXX X111
        break;
      case 4:
        registerValue = (registerValue & 0xF8) | (1 * 0x01);  // Set register value to XXXX X001
        break;
      case 5:
        registerValue = (registerValue & 0xF8) | (1 * 0x02);  // Set register value to XXXX X010
        break;
      case 6:
        registerValue = (registerValue & 0xF8) | (1 * 0x04);  // Set register value to XXXX X100
        break;
      case 9:
        registerValue = (registerValue & 0xF8) | (1 * 0x03);  // Set register value to XXXX X011
        break;
      case 10:
        registerValue = (registerValue & 0xF8) | (1 * 0x05);  // Set register value to XXXX X101
        break;
      case 11:
        registerValue = (registerValue & 0xF8) | (1 * 0x06);  // Set register value to XXXX X110
        break;
      case 15:
        registerValue = (registerValue & 0xF8) | (1 * 0x07);  // Set register value to XXXX X111
        break;
      } 
    writeRegister(_address, DEV_CONFIG1, registerValue);
  }

  void LP5817::enableFade(int firstOutput, int secondOutput, int thirdOutput) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG2);
    int sum = 0;
      if (firstOutput == false && secondOutput == false && thirdOutput == false) {  // If all variables are not set or set ALL / Drive all outputs
        sum = 0;
      }
      if (firstOutput != false && secondOutput == false && thirdOutput == false) {
        sum = firstOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD;
      }
    switch (sum) {
      case 0:
        registerValue = (registerValue & 0xF8) | (1 * 0x07);  // Set register value to XXXX X111
        break;
      case 4:
        registerValue = (registerValue & 0xF8) | (1 * 0x01);  // Set register value to XXXX X001
        break;
      case 5:
        registerValue = (registerValue & 0xF8) | (1 * 0x02);  // Set register value to XXXX X010
        break;
      case 6:
        registerValue = (registerValue & 0xF8) | (1 * 0x04);  // Set register value to XXXX X100
        break;
      case 9:
        registerValue = (registerValue & 0xF8) | (1 * 0x03);  // Set register value to XXXX X011
        break;
      case 10:
        registerValue = (registerValue & 0xF8) | (1 * 0x05);  // Set register value to XXXX X101
        break;
      case 11:
        registerValue = (registerValue & 0xF8) | (1 * 0x06);  // Set register value to XXXX X110
        break;
      case 15:
        registerValue = (registerValue & 0xF8) | (1 * 0x07);  // Set register value to XXXX X111
        break;
      } 
    writeRegister(_address, DEV_CONFIG2, registerValue);
  }

  void LP5817::setFadeTime(float fadeValue) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG2);
    int value = fadeValue * 100;
      switch(value) {
        case 0:
          registerValue = (registerValue & 0x0F) | (0 * 0x00);  // Set register value to 1110 XXXX
          break;
        case 5:
          registerValue = (registerValue & 0x0F) | (1 * 0x10);  // Set register value to 0001 XXXX
          break;
        case 10:
          registerValue = (registerValue & 0x0F) | (1 * 0x20);  // Set register value to 0010 XXXX
          break;
        case 15:
          registerValue = (registerValue & 0x0F) | (1 * 0x30);  // Set register value to 0011 XXXX
          break;
        case 20:
          registerValue = (registerValue & 0x0F) | (1 * 0x40);  // Set register value to 0100 XXXX
          break;
        case 25:
          registerValue = (registerValue & 0x0F) | (1 * 0x50);  // Set register value to 0101 XXXX
          break;
        case 30:
          registerValue = (registerValue & 0x0F) | (1 * 0x60);  // Set register value to 0110 XXXX
          break;
        case 35:
          registerValue = (registerValue & 0x0F) | (1 * 0x70);  // Set register value to 0111 XXXX
          break;
        case 40:
          registerValue = (registerValue & 0x0F) | (1 * 0x80);  // Set register value to 1000 XXXX
          break;
        case 45:
          registerValue = (registerValue & 0x0F) | (1 * 0x90);  // Set register value to 1001 XXXX
          break;
        case 50:
          registerValue = (registerValue & 0x0F) | (1 * 0xA0);  // Set register value to 1010 XXXX
          break;
        case 100:
          registerValue = (registerValue & 0x0F) | (1 * 0xB0);  // Set register value to 1011 XXXX
          break;
        case 200:
          registerValue = (registerValue & 0x0F) | (1 * 0xC0);  // Set register value to 1100 XXXX
          break;
        case 400:
          registerValue = (registerValue & 0x0F) | (1 * 0xD0);  // Set register value to 1101 XXXX
          break;
        case 600:
          registerValue = (registerValue & 0x0F) | (1 * 0xE0);  // Set register value to 1110 XXXX
          break;
        case 800:
          registerValue = (registerValue & 0x0F) | (1 * 0xF0);  // Set register value to 1110 XXXX
          break;
      }
    writeRegister(_address, DEV_CONFIG2, registerValue);
  }

  void LP5817::setFadeType(bool fadeType, int firstOutput, int secondOutput, int thirdOutput) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG3);
    int sum = 0;
      if (firstOutput == false && secondOutput == false && thirdOutput == false) {  // If all variables are not set or set ALL / Drive all outputs
        sum = 0;
      }
      if (firstOutput != false && secondOutput == false && thirdOutput == false) {
        sum = firstOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD;
      }
      if (fadeType == EXPONENTIAL) { 
        switch (sum) {
          case 0: 
            registerValue = (registerValue & 0x8F) | (1 * 0x70);  // Set register value to X111 XXXX
            break;
          case 4:
            registerValue = (registerValue & 0xEF) | (1 * 0x10);  // Set register value to XXX1 XXXX
            break;
          case 5:
            registerValue = (registerValue & 0xDF) | (1 * 0x20);  // Set register value to XX1X XXXX
            break;
          case 6:
            registerValue = (registerValue & 0xBF) | (1 * 0x40);  // Set register value to X1XX XXXX
            break;
          case 9:
            registerValue = (registerValue & 0xCF) | (1 * 0x30);  // Set register value to XX11 XXXX
            break;
          case 10:
            registerValue = (registerValue & 0xAF) | (1 * 0x50);  // Set register value to X1X1 XXXX
            break;
          case 11:
            registerValue = (registerValue & 0x9F) | (1 * 0x60);  // Set register value to X11X XXXX
            break;
          case 15:
            registerValue = (registerValue & 0x8F) | (1 * 0x70);  // Set register value to X111 XXXX
            break;
          } 
      }
      else if (fadeType == LINEAR) { 
        switch (sum) {
          case 0: 
            registerValue = (registerValue & 0x8F) | (0 * 0x70);  // Set register value to X000 XXXX
            break;
          case 4:
            registerValue = (registerValue & 0xEF) | (0 * 0x10);  // Set register value to XXX0 XXXX
            break;
          case 5:
            registerValue = (registerValue & 0xDF) | (0 * 0x20);  // Set register value to XX0X XXXX
            break;
          case 6:
            registerValue = (registerValue & 0xBF) | (0 * 0x40);  // Set register value to X0XX XXXX
            break;
          case 9:
            registerValue = (registerValue & 0xCF) | (0 * 0x30);  // Set register value to XX00 XXXX
            break;
          case 10:
            registerValue = (registerValue & 0xAF) | (0 * 0x50);  // Set register value to X0X0 XXXX
            break;
          case 11:
            registerValue = (registerValue & 0x9F) | (0 * 0x60);  // Set register value to X00X XXXX
            break;
          case 15:
            registerValue = (registerValue & 0x8F) | (0 * 0x70);  // Set register value to X000 XXXX
            break;
          } 
      }
    writeRegister(_address, DEV_CONFIG3, registerValue);
  }

  void LP5817::setCurrent(int OUT0CurrentValue, int OUT1secondCurrentValue, int OUT2CurrentValue) {
    writeRegister(_address, OUT0_DC, OUT0CurrentValue);
    writeRegister(_address, OUT1_DC, OUT1secondCurrentValue);
    writeRegister(_address, OUT2_DC, OUT2CurrentValue);
  }

  void LP5817::setPWM(int OUT0PWMValue, int OUT1PWMValue, int OUT2PWMValue) {
    writeRegister(_address, OUT0_MANUAL_PWM, OUT0PWMValue);
    writeRegister(_address, OUT1_MANUAL_PWM, OUT1PWMValue);
    writeRegister(_address, OUT2_MANUAL_PWM, OUT2PWMValue);
  }

  bool LP5817::checkFlag(int flag) {
    uint8_t registerValue = readRegister(_address, FLAG);
    switch (flag) {
      case 0: 
        registerValue = registerValue & 0x01; // Check the value of last bit
        break;
      case 1: 
        registerValue = ((registerValue >> 1) & 0x01); // Move bits certain amount to the right and then check the value of wanted flag
        break;
    }
    return registerValue;
  }

  void LP5817::clearFlag(int flag) {
    uint8_t registerValue = readRegister(_address, FLAG_CLR);
      switch (flag) {
        case 0:
          registerValue = (registerValue & 0xFC) | (1 * 0x01); // Disables the last bit
          break;
        case 1:
          registerValue = (registerValue & 0xFC) | (1 * 0x02); // Disables the last bit
          break;
      }
    writeRegister(_address, FLAG_CLR, registerValue);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////

  LP5816::LP5816(uint8_t adressOfDevice) : LP58XX(_SCL, _SDA) { // Object LP58XX has to be created here directly
    _address = adressOfDevice;
  }

  void LP5816::enable() {
    uint8_t registerValue = readRegister(_address, CHIP_EN);
    registerValue = (registerValue & 0xFE) | (1 * 0x01); // Enables the last bit
    writeRegister(_address, CHIP_EN, registerValue);
  }

  void LP5816::disable() {
    uint8_t registerValue = readRegister(_address, CHIP_EN);
    registerValue = (registerValue & 0xFE) | (0 * 0x01); // Disables the last bit
    writeRegister(_address, CHIP_EN, registerValue);
  }

  void LP5816::reset() {
    writeRegister(_address, RESET_CMD, RESET_WORD);
  }

  void LP5816::update() {
    writeRegister(_address, UPDATE_CMD, UPDATE_WORD);
  }

  void LP5816::setMaxCurrent(bool maxCurrent) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG0);
      if (maxCurrent == false) {
    registerValue = (registerValue & 0xFE) | (0 * 0x01); // Disables the last bit
      }
      else {
    registerValue = (registerValue & 0xFE) | (1 * 0x01); // Disables the last bit
      }
    writeRegister(_address, DEV_CONFIG0, registerValue);
  }

  void LP5816::enableOutput(int firstOutput, int secondOutput, int thirdOutput, int fourthOutput) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG1);
    int sum = 0;
      if (firstOutput == false && secondOutput == false && thirdOutput == false && fourthOutput == false) {  // If all variables are not set or set ALL / Drive all outputs
        sum = 0;
      }
      if (firstOutput != false && secondOutput == false && thirdOutput == false && fourthOutput == false) {
        sum = firstOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput == false && fourthOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false && fourthOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false && fourthOutput != false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD + fourthOutput + ADD;
      }
    switch (sum) {
      case 0:
        registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1111
        break;
      case 4:
        registerValue = (registerValue & 0xF0) | (1 * 0x01);  // Set register value to XXXX 0001
        break;
      case 5:
        registerValue = (registerValue & 0xF0) | (1 * 0x02);  // Set register value to XXXX 0010
        break;
      case 6:
        registerValue = (registerValue & 0xF0) | (1 * 0x04);  // Set register value to XXXX 0100
        break;
      case 8:
        registerValue = (registerValue & 0xF0) | (1 * 0x08);  // Set register value to XXXX 1000
        break;
      case 9:
        registerValue = (registerValue & 0xF0) | (1 * 0x03);  // Set register value to XXXX 0011
        break;
      case 10:
        registerValue = (registerValue & 0xF0) | (1 * 0x05);  // Set register value to XXXX 0101
        break;
      case 12:
        registerValue = (registerValue & 0xF0) | (1 * 0x09);  // Set register value to XXXX 1001
        break;
      case 11:
        registerValue = (registerValue & 0xF0) | (1 * 0x06);  // Set register value to XXXX 0110
        break;
      case 13:
        registerValue = (registerValue & 0xF0) | (1 * 0x0A);  // Set register value to XXXX 1010
        break;
      case 14:
        registerValue = (registerValue & 0xF0) | (1 * 0x0C);  // Set register value to XXXX 1100
        break;
      case 15:
        registerValue = (registerValue & 0xF0) | (1 * 0x07);  // Set register value to XXXX 0111
        break;
      case 17:
        registerValue = (registerValue & 0xF0) | (1 * 0x0B);  // Set register value to XXXX 1011
        break;
      case 18:
        registerValue = (registerValue & 0xF0) | (1 * 0x0D);  // Set register value to XXXX 1101
        break;
      case 19:
        registerValue = (registerValue & 0xF0) | (1 * 0x0E);  // Set register value to XXXX 1110
        break;
      case 23:
        registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1111
        break;
      } 
    writeRegister(_address, DEV_CONFIG1, registerValue);
  }

  void LP5816::enableFade(int firstOutput, int secondOutput, int thirdOutput, int fourthOutput) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG2);
    int sum = 0;
      if (firstOutput == false && secondOutput == false && thirdOutput == false && fourthOutput == false) {  // If all variables are not set or set ALL / Drive all outputs
        sum = 0;
      }
      if (firstOutput != false && secondOutput == false && thirdOutput == false && fourthOutput == false) {
        sum = firstOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput == false && fourthOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false && fourthOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false && fourthOutput != false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD + fourthOutput + ADD;
      }
    switch (sum) {
      case 0:
        registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1111
        break;
      case 4:
        registerValue = (registerValue & 0xF0) | (1 * 0x01);  // Set register value to XXXX 0001
        break;
      case 5:
        registerValue = (registerValue & 0xF0) | (1 * 0x02);  // Set register value to XXXX 0010
        break;
      case 6:
        registerValue = (registerValue & 0xF0) | (1 * 0x04);  // Set register value to XXXX 0100
        break;
      case 8:
        registerValue = (registerValue & 0xF0) | (1 * 0x08);  // Set register value to XXXX 1000
        break;
      case 9:
        registerValue = (registerValue & 0xF0) | (1 * 0x03);  // Set register value to XXXX 0011
        break;
      case 10:
        registerValue = (registerValue & 0xF0) | (1 * 0x05);  // Set register value to XXXX 0101
        break;
      case 12:
        registerValue = (registerValue & 0xF0) | (1 * 0x09);  // Set register value to XXXX 1001
        break;
      case 11:
        registerValue = (registerValue & 0xF0) | (1 * 0x06);  // Set register value to XXXX 0110
        break;
      case 13:
        registerValue = (registerValue & 0xF0) | (1 * 0x0A);  // Set register value to XXXX 1010
        break;
      case 14:
        registerValue = (registerValue & 0xF0) | (1 * 0x0C);  // Set register value to XXXX 1100
        break;
      case 15:
        registerValue = (registerValue & 0xF0) | (1 * 0x07);  // Set register value to XXXX 0111
        break;
      case 17:
        registerValue = (registerValue & 0xF0) | (1 * 0x0B);  // Set register value to XXXX 1011
        break;
      case 18:
        registerValue = (registerValue & 0xF0) | (1 * 0x0D);  // Set register value to XXXX 1101
        break;
      case 19:
        registerValue = (registerValue & 0xF0) | (1 * 0x0E);  // Set register value to XXXX 1110
        break;
      case 23:
        registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1111
        break;
      } 
    writeRegister(_address, DEV_CONFIG2, registerValue);
  }

  void LP5816::setFadeTime(float fadeValue) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG2);
    int value = fadeValue * 100;
      switch(value) {
        case 0:
          registerValue = (registerValue & 0x0F) | (0 * 0x00);  // Set register value to 1110 XXXX
          break;
        case 5:
          registerValue = (registerValue & 0x0F) | (1 * 0x10);  // Set register value to 0001 XXXX
          break;
        case 10:
          registerValue = (registerValue & 0x0F) | (1 * 0x20);  // Set register value to 0010 XXXX
          break;
        case 15:
          registerValue = (registerValue & 0x0F) | (1 * 0x30);  // Set register value to 0011 XXXX
          break;
        case 20:
          registerValue = (registerValue & 0x0F) | (1 * 0x40);  // Set register value to 0100 XXXX
          break;
        case 25:
          registerValue = (registerValue & 0x0F) | (1 * 0x50);  // Set register value to 0101 XXXX
          break;
        case 30:
          registerValue = (registerValue & 0x0F) | (1 * 0x60);  // Set register value to 0110 XXXX
          break;
        case 35:
          registerValue = (registerValue & 0x0F) | (1 * 0x70);  // Set register value to 0111 XXXX
          break;
        case 40:
          registerValue = (registerValue & 0x0F) | (1 * 0x80);  // Set register value to 1000 XXXX
          break;
        case 45:
          registerValue = (registerValue & 0x0F) | (1 * 0x90);  // Set register value to 1001 XXXX
          break;
        case 50:
          registerValue = (registerValue & 0x0F) | (1 * 0xA0);  // Set register value to 1010 XXXX
          break;
        case 100:
          registerValue = (registerValue & 0x0F) | (1 * 0xB0);  // Set register value to 1011 XXXX
          break;
        case 200:
          registerValue = (registerValue & 0x0F) | (1 * 0xC0);  // Set register value to 1100 XXXX
          break;
        case 400:
          registerValue = (registerValue & 0x0F) | (1 * 0xD0);  // Set register value to 1101 XXXX
          break;
        case 600:
          registerValue = (registerValue & 0x0F) | (1 * 0xE0);  // Set register value to 1110 XXXX
          break;
        case 800:
          registerValue = (registerValue & 0x0F) | (1 * 0xF0);  // Set register value to 1110 XXXX
          break;
      }

    writeRegister(_address, DEV_CONFIG2, registerValue);
  }

  void LP5816::setFadeType(bool fadeType, int firstOutput, int secondOutput, int thirdOutput, int fourthOutput) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG3);
    int sum = 0;
      if (firstOutput == false && secondOutput == false && thirdOutput == false && fourthOutput == false) {  // If all variables are not set or set ALL / Drive all outputs
        sum = 0;
      }
      if (firstOutput != false && secondOutput == false && thirdOutput == false && fourthOutput == false) {
        sum = firstOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput == false && fourthOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false && fourthOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false && fourthOutput != false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD + fourthOutput + ADD;
      }
    if (fadeType == EXPONENTIAL) { 
      switch (sum) {
        case 0: 
          registerValue = (registerValue & 0x0F) | (1 * 0x70);  // Set register value to X111 XXXX
          break;
        case 4:
          registerValue = (registerValue & 0xEF) | (1 * 0x10);  // Set register value to XXX1 XXXX
          break;
        case 5:
          registerValue = (registerValue & 0xDF) | (1 * 0x20);  // Set register value to XX1X XXXX
          break;
        case 6:
          registerValue = (registerValue & 0xBF) | (1 * 0x40);  // Set register value to X1XX XXXX
          break;
        case 8:
          registerValue = (registerValue & 0x7F) | (1 * 0x80);  // Set register value to 1XXX XXXX 
          break;
        case 9:
          registerValue = (registerValue & 0xCF) | (1 * 0x30);  // Set register value to XX11 XXXX
          break;
        case 10:
          registerValue = (registerValue & 0xAF) | (1 * 0x50);  // Set register value to X1X1 XXXX
          break;
        case 11:
          registerValue = (registerValue & 0x9F) | (1 * 0x60);  // Set register value to X11X XXXX
          break;
        case 12:
          registerValue = (registerValue & 0x6F) | (1 * 0x90);  // Set register value to 1XX1 XXXX 
          break;
        case 13:
          registerValue = (registerValue & 0x5F) | (1 * 0xA0);  // Set register value to 1X1X XXXX 
          break;
        case 14:
          registerValue = (registerValue & 0x3F) | (1 * 0xC0);  // Set register value to 11XX XXXX 
          break;
        case 15:
          registerValue = (registerValue & 0x8F) | (1 * 0x70);  // Set register value to X111 XXXX
          break;  
        case 17:
          registerValue = (registerValue & 0x4F) | (1 * 0xB0);  // Set register value to 1X11 XXXX 
          break;
        case 18:
          registerValue = (registerValue & 0x2F) | (1 * 0xD0);  // Set register value to 11X1 XXXX 
          break;
        case 19:
          registerValue = (registerValue & 0x1F) | (1 * 0xE0);  // Set register value to 111X XXXX 
          break;
        case 23:
          registerValue = (registerValue & 0x0F) | (1 * 0xF0);  // Set register value to 1111 XXXX 
          break;
      }
    }
    else if (fadeType == LINEAR) { 
      switch (sum) {
        case 0: 
          registerValue = (registerValue & 0x0F) | (0 * 0x70);  // Set register value to X111 XXXX
          break;
        case 4:
          registerValue = (registerValue & 0xEF) | (0 * 0x10);  // Set register value to XXX1 XXXX
          break;
        case 5:
          registerValue = (registerValue & 0xDF) | (0 * 0x20);  // Set register value to XX1X XXXX
          break;
        case 6:
          registerValue = (registerValue & 0xBF) | (0 * 0x40);  // Set register value to X1XX XXXX
          break;
        case 8:
          registerValue = (registerValue & 0x7F) | (0 * 0x80);  // Set register value to 1XXX XXXX 
          break;
        case 9:
          registerValue = (registerValue & 0xCF) | (0 * 0x30);  // Set register value to XX11 XXXX
          break;
        case 10:
          registerValue = (registerValue & 0xAF) | (0 * 0x50);  // Set register value to X1X1 XXXX
          break;
        case 11:
          registerValue = (registerValue & 0x9F) | (0 * 0x60);  // Set register value to X11X XXXX
          break;
        case 12:
          registerValue = (registerValue & 0x6F) | (0 * 0x90);  // Set register value to 1XX1 XXXX 
          break;
        case 13:
          registerValue = (registerValue & 0x5F) | (0 * 0xA0);  // Set register value to 1X1X XXXX 
          break;
        case 14:
          registerValue = (registerValue & 0x3F) | (0 * 0xC0);  // Set register value to 11XX XXXX 
          break;
        case 15:
          registerValue = (registerValue & 0x8F) | (0 * 0x70);  // Set register value to X111 XXXX
          break;  
        case 17:
          registerValue = (registerValue & 0x4F) | (0 * 0xB0);  // Set register value to 1X11 XXXX 
          break;
        case 18:
          registerValue = (registerValue & 0x2F) | (0 * 0xD0);  // Set register value to 11X1 XXXX 
          break;
        case 19:
          registerValue = (registerValue & 0x1F) | (0 * 0xE0);  // Set register value to 111X XXXX 
          break;
        case 23:
          registerValue = (registerValue & 0x0F) | (0 * 0xF0);  // Set register value to 1111 XXXX 
          break;
      }
    }
    writeRegister(_address, DEV_CONFIG3, registerValue);
  }

  void LP5816::setCurrent(int OUT0CurrentValue, int OUT1CurrentValue, int OUT2CurrentValue, int OUT3CurrentValue) {
    writeRegister(_address, OUT0_DC, OUT0CurrentValue);
    writeRegister(_address, OUT1_DC, OUT1CurrentValue);
    writeRegister(_address, OUT2_DC, OUT2CurrentValue);
    writeRegister(_address, OUT3_DC, OUT2CurrentValue);
  }

  void LP5816::setPWM(int OUT0PWMValue, int OUT1PWMValue, int OUT2PWMValue, int OUT3PWMValue) {
    writeRegister(_address, OUT0_MANUAL_PWM, OUT0PWMValue);
    writeRegister(_address, OUT1_MANUAL_PWM, OUT1PWMValue);
    writeRegister(_address, OUT2_MANUAL_PWM, OUT2PWMValue);
    writeRegister(_address, OUT3_MANUAL_PWM, OUT3PWMValue);
  }

  bool LP5816::checkFlag(int flag) {
    uint8_t registerValue = readRegister(_address, FLAG);
    switch (flag) {
      case 0: 
        registerValue = registerValue & 0x01; // Check the value of last bit
        break;
      case 1: 
        registerValue = ((registerValue >> 1) & 0x01); // Move bits certain amount to the right and then check the value of wanted flag
        break;
    }
    return registerValue;
  }

  void LP5816::clearFlag(int flag) {
    uint8_t registerValue = readRegister(_address, FLAG_CLR);
      switch (flag) {
        case 0:
          registerValue = (registerValue & 0xFC) | (1 * 0x01); // Disables the last bit
          break;
        case 1:
          registerValue = (registerValue & 0xFC) | (1 * 0x02); // Disables the last bit
          break;
      }
    writeRegister(_address, FLAG_CLR, registerValue);
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

  LP5815::LP5815(uint8_t adressOfDevice) : LP58XX(_SCL, _SDA) { // Object LP58XX has to be created here directly
    _address = adressOfDevice;
  }

  void LP5815::enable() {
    uint8_t registerValue = readRegister(_address, CHIP_EN);
    registerValue = (registerValue & 0xFE) | (1 * 0x01); // Enables the last bit
    writeRegister(_address, CHIP_EN, registerValue);
  }

  void LP5815::setInstantBlinking(bool value) {
    uint8_t registerValue = readRegister(_address, CHIP_EN);
      if (value == false) {
        registerValue = (registerValue & 0xFD) | (1 * 0x02); // Enables the last bit
      }
      else if (value == true) {
        registerValue = (registerValue & 0xFD) | (0 * 0x02); // Enables the last bit
      }
    writeRegister(_address, CHIP_EN, registerValue);
  }

  void LP5815::disable() {
    uint8_t registerValue = readRegister(_address, CHIP_EN);
    registerValue = (registerValue & 0xFE) | (0 * 0x01); // Disables the last bit
    writeRegister(_address, CHIP_EN, registerValue);
  }

  void LP5815::reset() {
    writeRegister(_address, RESET_CMD, RESET_WORD);
  }

  void LP5815::update() {
    writeRegister(_address, UPDATE_CMD, UPDATE_WORD);
  }

  void LP5815::setMaxCurrent(bool maxCurrent) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG0);
      if (maxCurrent == false) {
    registerValue = (registerValue & 0xFE) | (0 * 0x01); // Disables the last bit
      }
      else {
    registerValue = (registerValue & 0xFE) | (1 * 0x01); // Disables the last bit
      }
    writeRegister(_address, DEV_CONFIG0, registerValue);
  }

  void LP5815::enableOutput(int firstOutput, int secondOutput, int thirdOutput) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG1);
    int sum = 0;
      if (firstOutput == false && secondOutput == false && thirdOutput == false) {  // If all variables are not set or set ALL / Drive all outputs
        sum = 0;
      }
      if (firstOutput != false && secondOutput == false && thirdOutput == false) {
        sum = firstOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD;
      }
    switch (sum) {
      case 0:
        registerValue = (registerValue & 0xF8) | (1 * 0x07);  // Set register value to XXXX X111
        break;
      case 4:
        registerValue = (registerValue & 0xF8) | (1 * 0x01);  // Set register value to XXXX X001
        break;
      case 5:
        registerValue = (registerValue & 0xF8) | (1 * 0x02);  // Set register value to XXXX X010
        break;
      case 6:
        registerValue = (registerValue & 0xF8) | (1 * 0x04);  // Set register value to XXXX X100
        break;
      case 9:
        registerValue = (registerValue & 0xF8) | (1 * 0x03);  // Set register value to XXXX X011
        break;
      case 10:
        registerValue = (registerValue & 0xF8) | (1 * 0x05);  // Set register value to XXXX X101
        break;
      case 11:
        registerValue = (registerValue & 0xF8) | (1 * 0x06);  // Set register value to XXXX X110
        break;
      case 15:
        registerValue = (registerValue & 0xF8) | (1 * 0x07);  // Set register value to XXXX X111
        break;
      } 
    writeRegister(_address, DEV_CONFIG1, registerValue);
  }

  void LP5815::enableFade(int firstOutput, int secondOutput, int thirdOutput) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG2);
    int sum = 0;
      if (firstOutput == false && secondOutput == false && thirdOutput == false) {  // If all variables are not set or set ALL / Drive all outputs
        sum = 0;
      }
      if (firstOutput != false && secondOutput == false && thirdOutput == false) {
        sum = firstOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD;
      }
    switch (sum) {
      case 0:
        registerValue = (registerValue & 0xF8) | (1 * 0x07);  // Set register value to XXXX X111
        break;
      case 4:
        registerValue = (registerValue & 0xF8) | (1 * 0x01);  // Set register value to XXXX X001
        break;
      case 5:
        registerValue = (registerValue & 0xF8) | (1 * 0x02);  // Set register value to XXXX X010
        break;
      case 6:
        registerValue = (registerValue & 0xF8) | (1 * 0x04);  // Set register value to XXXX X100
        break;
      case 9:
        registerValue = (registerValue & 0xF8) | (1 * 0x03);  // Set register value to XXXX X011
        break;
      case 10:
        registerValue = (registerValue & 0xF8) | (1 * 0x05);  // Set register value to XXXX X101
        break;
      case 11:
        registerValue = (registerValue & 0xF8) | (1 * 0x06);  // Set register value to XXXX X110
        break;
      case 15:
        registerValue = (registerValue & 0xF8) | (1 * 0x07);  // Set register value to XXXX X111
        break;
      } 
    writeRegister(_address, DEV_CONFIG2, registerValue);
  }

  void LP5815::setFadeTime(float fadeValue) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG2);
    int value = fadeValue * 100;
      switch(value) {
        case 0:
          registerValue = (registerValue & 0x0F) | (0 * 0x00);  // Set register value to 1110 XXXX
          break;
        case 5:
          registerValue = (registerValue & 0x0F) | (1 * 0x10);  // Set register value to 0001 XXXX
          break;
        case 10:
          registerValue = (registerValue & 0x0F) | (1 * 0x20);  // Set register value to 0010 XXXX
          break;
        case 15:
          registerValue = (registerValue & 0x0F) | (1 * 0x30);  // Set register value to 0011 XXXX
          break;
        case 20:
          registerValue = (registerValue & 0x0F) | (1 * 0x40);  // Set register value to 0100 XXXX
          break;
        case 25:
          registerValue = (registerValue & 0x0F) | (1 * 0x50);  // Set register value to 0101 XXXX
          break;
        case 30:
          registerValue = (registerValue & 0x0F) | (1 * 0x60);  // Set register value to 0110 XXXX
          break;
        case 35:
          registerValue = (registerValue & 0x0F) | (1 * 0x70);  // Set register value to 0111 XXXX
          break;
        case 40:
          registerValue = (registerValue & 0x0F) | (1 * 0x80);  // Set register value to 1000 XXXX
          break;
        case 45:
          registerValue = (registerValue & 0x0F) | (1 * 0x90);  // Set register value to 1001 XXXX
          break;
        case 50:
          registerValue = (registerValue & 0x0F) | (1 * 0xA0);  // Set register value to 1010 XXXX
          break;
        case 100:
          registerValue = (registerValue & 0x0F) | (1 * 0xB0);  // Set register value to 1011 XXXX
          break;
        case 200:
          registerValue = (registerValue & 0x0F) | (1 * 0xC0);  // Set register value to 1100 XXXX
          break;
        case 400:
          registerValue = (registerValue & 0x0F) | (1 * 0xD0);  // Set register value to 1101 XXXX
          break;
        case 600:
          registerValue = (registerValue & 0x0F) | (1 * 0xE0);  // Set register value to 1110 XXXX
          break;
        case 800:
          registerValue = (registerValue & 0x0F) | (1 * 0xF0);  // Set register value to 1110 XXXX
          break;
      }
    writeRegister(_address, DEV_CONFIG2, registerValue);
  }

  void LP5815::setFadeType(bool fadeType, int firstOutput, int secondOutput, int thirdOutput) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG3);
    int sum = 0;
      if (firstOutput == false && secondOutput == false && thirdOutput == false) {  // If all variables are not set or set ALL / Drive all outputs
        sum = 0;
      }
      if (firstOutput != false && secondOutput == false && thirdOutput == false) {
        sum = firstOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD;
      }
      if (fadeType == EXPONENTIAL) { 
        switch (sum) {
          case 0: 
            registerValue = (registerValue & 0x8F) | (1 * 0x70);  // Set register value to X111 XXXX
            break;
          case 4:
            registerValue = (registerValue & 0xEF) | (1 * 0x10);  // Set register value to XXX1 XXXX
            break;
          case 5:
            registerValue = (registerValue & 0xDF) | (1 * 0x20);  // Set register value to XX1X XXXX
            break;
          case 6:
            registerValue = (registerValue & 0xBF) | (1 * 0x40);  // Set register value to X1XX XXXX
            break;
          case 9:
            registerValue = (registerValue & 0xCF) | (1 * 0x30);  // Set register value to XX11 XXXX
            break;
          case 10:
            registerValue = (registerValue & 0xAF) | (1 * 0x50);  // Set register value to X1X1 XXXX
            break;
          case 11:
            registerValue = (registerValue & 0x9F) | (1 * 0x60);  // Set register value to X11X XXXX
            break;
          case 15:
            registerValue = (registerValue & 0x8F) | (1 * 0x70);  // Set register value to X111 XXXX
            break;
          } 
      }
      else if (fadeType == LINEAR) { 
        switch (sum) {
          case 0: 
            registerValue = (registerValue & 0x8F) | (0 * 0x70);  // Set register value to X000 XXXX
            break;
          case 4:
            registerValue = (registerValue & 0xEF) | (0 * 0x10);  // Set register value to XXX0 XXXX
            break;
          case 5:
            registerValue = (registerValue & 0xDF) | (0 * 0x20);  // Set register value to XX0X XXXX
            break;
          case 6:
            registerValue = (registerValue & 0xBF) | (0 * 0x40);  // Set register value to X0XX XXXX
            break;
          case 9:
            registerValue = (registerValue & 0xCF) | (0 * 0x30);  // Set register value to XX00 XXXX
            break;
          case 10:
            registerValue = (registerValue & 0xAF) | (0 * 0x50);  // Set register value to X0X0 XXXX
            break;
          case 11:
            registerValue = (registerValue & 0x9F) | (0 * 0x60);  // Set register value to X00X XXXX
            break;
          case 15:
            registerValue = (registerValue & 0x8F) | (0 * 0x70);  // Set register value to X000 XXXX
            break;
          } 
      }
    writeRegister(_address, DEV_CONFIG3, registerValue);
  }

  void LP5815::setWorkingMode(bool workingMode, int firstOutput, int secondOutput, int thirdOutput) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG3);
    int sum = 0;
      if (firstOutput == false && secondOutput == false && thirdOutput == false) {  // If all variables are not set or set ALL / Drive all outputs
        sum = 0;
      }
      if (firstOutput != false && secondOutput == false && thirdOutput == false) {
        sum = firstOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD;
      }
  if (workingMode == AUTOMATIC) { 
    switch (sum) {
      case 0:
        registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1111
        break;
      case 4:
        registerValue = (registerValue & 0xF0) | (1 * 0x01);  // Set register value to XXXX 0001
        break;
      case 5:
        registerValue = (registerValue & 0xF0) | (1 * 0x02);  // Set register value to XXXX 0010
        break;
      case 6:
        registerValue = (registerValue & 0xF0) | (1 * 0x04);  // Set register value to XXXX 0100
        break;
      case 8:
        registerValue = (registerValue & 0xF0) | (1 * 0x08);  // Set register value to XXXX 1000
        break;
      case 9:
        registerValue = (registerValue & 0xF0) | (1 * 0x03);  // Set register value to XXXX 0011
        break;
      case 10:
        registerValue = (registerValue & 0xF0) | (1 * 0x05);  // Set register value to XXXX 0101
        break;
      case 12:
        registerValue = (registerValue & 0xF0) | (1 * 0x09);  // Set register value to XXXX 1001
        break;
      case 11:
        registerValue = (registerValue & 0xF0) | (1 * 0x06);  // Set register value to XXXX 0110
        break;
      case 13:
        registerValue = (registerValue & 0xF0) | (1 * 0x0A);  // Set register value to XXXX 1010
        break;
      case 14:
        registerValue = (registerValue & 0xF0) | (1 * 0x0C);  // Set register value to XXXX 1100
        break;
      case 15:
        registerValue = (registerValue & 0xF0) | (1 * 0x07);  // Set register value to XXXX 0111
        break;
      case 17:
        registerValue = (registerValue & 0xF0) | (1 * 0x0B);  // Set register value to XXXX 1011
        break;
      case 18:
        registerValue = (registerValue & 0xF0) | (1 * 0x0D);  // Set register value to XXXX 1101
        break;
      case 19:
        registerValue = (registerValue & 0xF0) | (1 * 0x0E);  // Set register value to XXXX 1110
        break;
      case 23:
        registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1111
        break;
      } 
    }
    else if (workingMode == MANUAL) { 
    switch (sum) {
      case 0:
        registerValue = (registerValue & 0xF0) | (0 * 0x0F);  // Set register value to XXXX 1111
        break;
      case 4:
        registerValue = (registerValue & 0xF0) | (0 * 0x01);  // Set register value to XXXX 0001
        break;
      case 5:
        registerValue = (registerValue & 0xF0) | (0 * 0x02);  // Set register value to XXXX 0010
        break;
      case 6:
        registerValue = (registerValue & 0xF0) | (0 * 0x04);  // Set register value to XXXX 0100
        break;
      case 8:
        registerValue = (registerValue & 0xF0) | (0 * 0x08);  // Set register value to XXXX 1000
        break;
      case 9:
        registerValue = (registerValue & 0xF0) | (0 * 0x03);  // Set register value to XXXX 0011
        break;
      case 10:
        registerValue = (registerValue & 0xF0) | (0 * 0x05);  // Set register value to XXXX 0101
        break;
      case 12:
        registerValue = (registerValue & 0xF0) | (0 * 0x09);  // Set register value to XXXX 1001
        break;
      case 11:
        registerValue = (registerValue & 0xF0) | (0 * 0x06);  // Set register value to XXXX 0110
        break;
      case 13:
        registerValue = (registerValue & 0xF0) | (0 * 0x0A);  // Set register value to XXXX 1010
        break;
      case 14:
        registerValue = (registerValue & 0xF0) | (0 * 0x0C);  // Set register value to XXXX 1100
        break;
      case 15:
        registerValue = (registerValue & 0xF0) | (0 * 0x07);  // Set register value to XXXX 0111
        break;
      case 17:
        registerValue = (registerValue & 0xF0) | (0 * 0x0B);  // Set register value to XXXX 1011
        break;
      case 18:
        registerValue = (registerValue & 0xF0) | (0 * 0x0D);  // Set register value to XXXX 1101
        break;
      case 19:
        registerValue = (registerValue & 0xF0) | (0 * 0x0E);  // Set register value to XXXX 1110
        break;
      case 23:
        registerValue = (registerValue & 0xF0) | (0 * 0x0F);  // Set register value to XXXX 1111
        break;
      } 
    }
    writeRegister(_address, DEV_CONFIG3, registerValue);
  }

  void LP5815::setCurrent(int OUT0CurrentValue, int OUT1secondCurrentValue, int OUT2CurrentValue) {
    writeRegister(_address, OUT0_DC, OUT0CurrentValue);
    writeRegister(_address, OUT1_DC, OUT1secondCurrentValue);
    writeRegister(_address, OUT2_DC, OUT2CurrentValue);
  }

  void LP5815::setPWM(int OUT0PWMValue, int OUT1PWMValue, int OUT2PWMValue) {
    writeRegister(_address, OUT0_MANUAL_PWM, OUT0PWMValue);
    writeRegister(_address, OUT1_MANUAL_PWM, OUT1PWMValue);
    writeRegister(_address, OUT2_MANUAL_PWM, OUT2PWMValue);
  }

  void LP5815::setOutEngine(uint8_t OUT0Engine, uint8_t OUT1Engine, uint8_t OUT2Engine) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG4);
    registerValue = (OUT0Engine & 0x03) | ((OUT1Engine & 0x03) << 2) | ((OUT2Engine & 0x03) << 4) | ((registerValue & 0x03) << 6);
    writeRegister(_address, DEV_CONFIG4, registerValue);
  }

  void LP5815::setEnginePatternOrder(uint8_t engine, uint8_t pattern0, uint8_t pattern1, uint8_t pattern2, uint8_t pattern3) {
    uint8_t registerValue = 0x00;
    registerValue = (pattern0 & 0x03) | ((pattern1 & 0x03) << 2) | ((pattern2 & 0x03) << 4) | ((pattern3 & 0x03) << 6);
      if (engine == ENGINE0) {
        writeRegister(_address, ENGINE_CONFIG0, registerValue);
      }
      else if (engine == ENGINE1) {
        writeRegister(_address, ENGINE_CONFIG1, registerValue);
      }
      else if (engine == ENGINE2) {
        writeRegister(_address, ENGINE_CONFIG2, registerValue);
      }
      else if (engine == ENGINE3) {
        writeRegister(_address, ENGINE_CONFIG3, registerValue);
      }
  }

  void LP5815::enableEnginePatternOrder(uint8_t engine, uint8_t patternEnable0, uint8_t patternEnable1, uint8_t patternEnable2, uint8_t patternEnable3) {
    uint8_t registerValue = 0x00;
      if (engine == ENGINE0) {
        registerValue = readRegister(_address, ENGINE_CONFIG4);
        registerValue = (registerValue & 0xF0) | (patternEnable0 & 0x01) | ((patternEnable1 & 0x01) << 1) | ((patternEnable2 & 0x01) << 2) | ((patternEnable3 & 0x01) << 3);  // Set register value to XXXX YYYY
        writeRegister(_address, ENGINE_CONFIG4, registerValue);
      }
      else if (engine == ENGINE1) {
        registerValue = readRegister(_address, ENGINE_CONFIG4);
        registerValue = (registerValue & 0x0F) | ((patternEnable0 & 0x01) << 4) | ((patternEnable1 & 0x01) << 5) | ((patternEnable2 & 0x01) << 6) | ((patternEnable3 & 0x01) << 7);  // Set register value to YYYY XXXX
        writeRegister(_address, ENGINE_CONFIG4, registerValue);
      }
      else if (engine == ENGINE2) {
        registerValue = readRegister(_address, ENGINE_CONFIG5);
        registerValue = (registerValue & 0xF0) | (patternEnable0 & 0x01) | ((patternEnable1 & 0x01) << 1) | ((patternEnable2 & 0x01) << 2) | ((patternEnable3 & 0x01) << 3);  // Set register value to XXXX YYYY
        writeRegister(_address, ENGINE_CONFIG5, registerValue);
      }
      else if (engine == ENGINE3) {
        registerValue = readRegister(_address, ENGINE_CONFIG5);
        registerValue = (registerValue & 0x0F) | ((patternEnable0 & 0x01) << 4) | ((patternEnable1 & 0x01) << 5) | ((patternEnable2 & 0x01) << 6) | ((patternEnable3 & 0x01) << 7);  // Set register value to YYYY XXXX
        writeRegister(_address, ENGINE_CONFIG5, registerValue);
      }
  }

  void LP5815::setEngineRepeatTime(uint8_t engine, uint8_t times) {
    uint8_t registerValue = readRegister(_address, ENGINE_CONFIG6);
      if (engine == ENGINE0) {
        registerValue = (registerValue & 0xFC) | (times);
      }
      else if (engine == ENGINE1) {
        registerValue = (registerValue & 0xF3) | (times << 2);
      }
      else if (engine == ENGINE2) {
        registerValue =  (registerValue & 0xCF) | (times << 4);
      }
      else if (engine == ENGINE3) {
        registerValue = (registerValue & 0x3F) | (times << 6);
      }
    writeRegister(_address, ENGINE_CONFIG6, registerValue);
   }

  void LP5815::setPatternPauseTime(uint8_t pattern, float pauseT0, float pauseT1) {
    uint8_t registerValue = 0x00;
    long int T0 = pauseT0 * 100;
    long int T1 = pauseT1 * 100;
      switch (T0) {
        case 0:
          registerValue = (registerValue & 0x0F) | (1 * 0xF0);  // Set register value to 1110 XXXX
          break;
        case 5:
          registerValue = (registerValue & 0x0F) | (1 * 0x10);  // Set register value to 0001 XXXX
          break;
        case 10:
          registerValue = (registerValue & 0x0F) | (1 * 0x20);  // Set register value to 0010 XXXX
          break;
        case 15:
          registerValue = (registerValue & 0x0F) | (1 * 0x30);  // Set register value to 0011 XXXX
          break;
        case 20:
          registerValue = (registerValue & 0x0F) | (1 * 0x40);  // Set register value to 0100 XXXX
          break;
        case 25:
          registerValue = (registerValue & 0x0F) | (1 * 0x50);  // Set register value to 0101 XXXX
          break;
        case 30:
          registerValue = (registerValue & 0x0F) | (1 * 0x60);  // Set register value to 0110 XXXX
          break;
        case 35:
          registerValue = (registerValue & 0x0F) | (1 * 0x70);  // Set register value to 0111 XXXX
          break;
        case 40:
          registerValue = (registerValue & 0x0F) | (1 * 0x80);  // Set register value to 1000 XXXX
          break;
        case 45:
          registerValue = (registerValue & 0x0F) | (1 * 0x90);  // Set register value to 1001 XXXX
          break;
        case 50:
          registerValue = (registerValue & 0x0F) | (1 * 0xA0);  // Set register value to 1010 XXXX
          break;
        case 100:
          registerValue = (registerValue & 0x0F) | (1 * 0xB0);  // Set register value to 1011 XXXX
          break;
        case 200:
          registerValue = (registerValue & 0x0F) | (1 * 0xC0);  // Set register value to 1100 XXXX
          break;
        case 400:
          registerValue = (registerValue & 0x0F) | (1 * 0xD0);  // Set register value to 1101 XXXX
          break;
        case 600:
          registerValue = (registerValue & 0x0F) | (1 * 0xE0);  // Set register value to 1110 XXXX
          break;
        case 800:
          registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1110 
          break;
      }
      switch (T1) {
        case 0:
          registerValue = (registerValue & 0xF0) | (0 * 0x0F);  // Set register value to XXXX 0000 
          break;
        case 5:
          registerValue = (registerValue & 0xF0) | (1 * 0x01);  // Set register value to XXXX 0001 
          break;
        case 10:
          registerValue = (registerValue & 0xF0) | (1 * 0x02);  // Set register value to XXXX 0010 
          break;
        case 15:
          registerValue = (registerValue & 0xF0) | (1 * 0x03);  // Set register value to XXXX 0011 
          break;
        case 20:
          registerValue = (registerValue & 0xF0) | (1 * 0x04);  // Set register value to XXXX 0100 
          break;
        case 25:
          registerValue = (registerValue & 0xF0) | (1 * 0x05);  // Set register value to XXXX 0101 
          break;
        case 30:
          registerValue = (registerValue & 0xF0) | (1 * 0x06);  // Set register value to XXXX 0110 
          break;
        case 35:
          registerValue = (registerValue & 0xF0) | (1 * 0x07);  // Set register value to XXXX 0111
          break;
        case 40:
          registerValue = (registerValue & 0xF0) | (1 * 0x08);  // Set register value to XXXX 1000 
          break;
        case 45:
          registerValue = (registerValue & 0xF0) | (1 * 0x09);  // Set register value to XXXX 1001
          break;
        case 50:
          registerValue = (registerValue & 0xF0) | (1 * 0x0A);  // Set register value to XXXX 1010 
          break;
        case 100:
          registerValue = (registerValue & 0xF0) | (1 * 0x0B);  // Set register value to XXXX 1011 
          break;
        case 200:
          registerValue = (registerValue & 0xF0) | (1 * 0x0C);  // Set register value to XXXX 1100 
          break;
        case 400:
          registerValue = (registerValue & 0xF0) | (1 * 0x0D);  // Set register value to XXXX 1101 
          break;
        case 600:
          registerValue = (registerValue & 0xF0) | (1 * 0x0E);  // Set register value to XXXX 1110 
          break;
        case 800:
          registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1110 
          break;
      }

      if (pattern == PATTERN0) {
        writeRegister(_address, PATTERN0_PAUSE_TIME, registerValue);
      }
      else if (pattern == PATTERN1) {
        writeRegister(_address, PATTERN1_PAUSE_TIME, registerValue);
      }
      else if (pattern == PATTERN2) {
        writeRegister(_address, PATTERN2_PAUSE_TIME, registerValue);
      }
      else if (pattern == PATTERN3) {
        writeRegister(_address, PATTERN3_PAUSE_TIME, registerValue);
      }
  }

  void LP5815::setPatternRepeatTime(uint8_t pattern, uint8_t repeatTimes) {
    uint8_t registerValue = 0x00;
      if (pattern == PATTERN0) {
        registerValue = readRegister(_address, PATTERN0_REPEAT_TIME);
      }
      else if (pattern == PATTERN1) {
        registerValue = readRegister(_address, PATTERN1_REPEAT_TIME);
      }
      else if (pattern == PATTERN2) {
        registerValue = readRegister(_address, PATTERN2_REPEAT_TIME);
      }
      else if (pattern == PATTERN3) {
        registerValue = readRegister(_address, PATTERN3_REPEAT_TIME);
      }
      switch (repeatTimes) {
        case 0:
          registerValue = (registerValue & 0xF0) | (0 * 0x0F);  // Set register value to XXXX 0000 
          break;
        case 1:
          registerValue = (registerValue & 0xF0) | (1 * 0x01);  // Set register value to XXXX 0001 
          break;
        case 2:
          registerValue = (registerValue & 0xF0) | (1 * 0x02);  // Set register value to XXXX 0010 
          break;
        case 3:
          registerValue = (registerValue & 0xF0) | (1 * 0x03);  // Set register value to XXXX 0011 
          break;
        case 4:
          registerValue = (registerValue & 0xF0) | (1 * 0x04);  // Set register value to XXXX 0100 
          break;
        case 5:
          registerValue = (registerValue & 0xF0) | (1 * 0x05);  // Set register value to XXXX 0101 
          break;
        case 6:
          registerValue = (registerValue & 0xF0) | (1 * 0x06);  // Set register value to XXXX 0110 
          break;
        case 7:
          registerValue = (registerValue & 0xF0) | (1 * 0x07);  // Set register value to XXXX 0111
          break;
        case 8:
          registerValue = (registerValue & 0xF0) | (1 * 0x08);  // Set register value to XXXX 1000 
          break;
        case 9:
          registerValue = (registerValue & 0xF0) | (1 * 0x09);  // Set register value to XXXX 1001
          break;
        case 10:
          registerValue = (registerValue & 0xF0) | (1 * 0x0A);  // Set register value to XXXX 1010 
          break;
        case 11:
          registerValue = (registerValue & 0xF0) | (1 * 0x0B);  // Set register value to XXXX 1011 
          break;
        case 12:
          registerValue = (registerValue & 0xF0) | (1 * 0x0C);  // Set register value to XXXX 1100 
          break;
        case 13:
          registerValue = (registerValue & 0xF0) | (1 * 0x0D);  // Set register value to XXXX 1101 
          break;
        case 14:
          registerValue = (registerValue & 0xF0) | (1 * 0x0E);  // Set register value to XXXX 1110 
          break;
        case 15:
          registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1110 
          break;
      }
      if (pattern == PATTERN0) {
        writeRegister(_address, PATTERN0_REPEAT_TIME, registerValue);
      }
      else if (pattern == PATTERN1) {
        writeRegister(_address, PATTERN1_REPEAT_TIME, registerValue);
      }
      else if (pattern == PATTERN2) {
        writeRegister(_address, PATTERN2_REPEAT_TIME, registerValue);
      }
      else if (pattern == PATTERN3) {
        writeRegister(_address, PATTERN3_REPEAT_TIME, registerValue);
      }
  }

  void LP5815::setPWMPattern(uint8_t pattern, uint8_t firstPWM, uint8_t secondPWM, uint8_t thirdPWM, uint8_t fourthPWM, uint8_t fifthPWM) {
    if (pattern == PATTERN0) {
      writeRegister(_address, PATTERN0_PWM0, firstPWM);
      writeRegister(_address, PATTERN0_PWM1, secondPWM);
      writeRegister(_address, PATTERN0_PWM2, thirdPWM);
      writeRegister(_address, PATTERN0_PWM3, fourthPWM);
      writeRegister(_address, PATTERN0_PWM4, fifthPWM);
    }
    else if (pattern == PATTERN1) {
      writeRegister(_address, PATTERN1_PWM0, firstPWM);
      writeRegister(_address, PATTERN1_PWM1, secondPWM);
      writeRegister(_address, PATTERN1_PWM2, thirdPWM);
      writeRegister(_address, PATTERN1_PWM3, fourthPWM);
      writeRegister(_address, PATTERN1_PWM4, fifthPWM);
    }
    else if (pattern == PATTERN2) {
      writeRegister(_address, PATTERN2_PWM0, firstPWM);
      writeRegister(_address, PATTERN2_PWM1, secondPWM);
      writeRegister(_address, PATTERN2_PWM2, thirdPWM);
      writeRegister(_address, PATTERN2_PWM3, fourthPWM);
      writeRegister(_address, PATTERN2_PWM4, fifthPWM);
    }
    else if (pattern == PATTERN3) {
      writeRegister(_address, PATTERN3_PWM0, firstPWM);
      writeRegister(_address, PATTERN3_PWM1, secondPWM);
      writeRegister(_address, PATTERN3_PWM2, thirdPWM);
      writeRegister(_address, PATTERN3_PWM3, fourthPWM);
      writeRegister(_address, PATTERN3_PWM4, fifthPWM);
    }
  }

  void LP5815::setPatternSloperTime(uint8_t pattern, float firstTime, float secondTime, float thirdTime, float fourthTime) {
    uint8_t registerOneValue = 0x00;
    uint8_t registerTwoValue = 0x00;
    int fir = firstTime * 100;
    int sec = secondTime * 100;
    int thi = thirdTime * 100;
    int fou = fourthTime * 100;
      switch (sec) {
        case 0:
          registerOneValue = (registerOneValue & 0x0F) | (0 * 0xF0);  // Set register value to 0000 XXXX
          break;
        case 5:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x10);  // Set register value to 0001 XXXX
          break;
        case 10:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x20);  // Set register value to 0010 XXXX
          break;
        case 15:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x30);  // Set register value to 0011 XXXX
          break;
        case 20:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x40);  // Set register value to 0100 XXXX
          break;
        case 25:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x50);  // Set register value to 0101 XXXX
          break;
        case 30:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x60);  // Set register value to 0110 XXXX
          break;
        case 35:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x70);  // Set register value to 0111 XXXX
          break;
        case 40:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x80);  // Set register value to 1000 XXXX
          break;
        case 45:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x90);  // Set register value to 1001 XXXX
          break;
        case 50:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0xA0);  // Set register value to 1010 XXXX
          break;
        case 100:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0xB0);  // Set register value to 1011 XXXX
          break;
        case 200:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0xC0);  // Set register value to 1100 XXXX
          break;
        case 400:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0xD0);  // Set register value to 1101 XXXX
          break;
        case 600:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0xE0);  // Set register value to 1110 XXXX
          break;
        case 800:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0xF0);  // Set register value to 1110 XXXX
          break;
      }
      switch (fir) {
        case 0:
          registerOneValue = (registerOneValue & 0xF0) | (0 * 0x0F);  // Set register value to XXXX 0000 
          break;
        case 5:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x01);  // Set register value to XXXX 0001 
          break;
        case 10:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x02);  // Set register value to XXXX 0010 
          break;
        case 15:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x03);  // Set register value to XXXX 0011 
          break;
        case 20:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x04);  // Set register value to XXXX 0100 
          break;
        case 25:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x05);  // Set register value to XXXX 0101 
          break;
        case 30:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x06);  // Set register value to XXXX 0110 
          break;
        case 35:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x07);  // Set register value to XXXX 0111
          break;
        case 40:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x08);  // Set register value to XXXX 1000 
          break;
        case 45:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x09);  // Set register value to XXXX 1001
          break;
        case 50:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x0A);  // Set register value to XXXX 1010 
          break;
        case 100:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x0B);  // Set register value to XXXX 1011 
          break;
        case 200:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x0C);  // Set register value to XXXX 1100 
          break;
        case 400:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x0D);  // Set register value to XXXX 1101 
          break;
        case 600:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x0E);  // Set register value to XXXX 1110 
          break;
        case 800:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1110 
          break;
      }
      switch (fou) {
        case 0:
          registerTwoValue = (registerTwoValue & 0x0F) | (0 * 0xF0);  // Set register value to 0000 XXXX
          break;
        case 5:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x10);  // Set register value to 0001 XXXX
          break;
        case 10:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x20);  // Set register value to 0010 XXXX
          break;
        case 15:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x30);  // Set register value to 0011 XXXX
          break;
        case 20:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x40);  // Set register value to 0100 XXXX
          break;
        case 25:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x50);  // Set register value to 0101 XXXX
          break;
        case 30:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x60);  // Set register value to 0110 XXXX
          break;
        case 35:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x70);  // Set register value to 0111 XXXX
          break;
        case 40:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x80);  // Set register value to 1000 XXXX
          break;
        case 45:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x90);  // Set register value to 1001 XXXX
          break;
        case 50:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0xA0);  // Set register value to 1010 XXXX
          break;
        case 100:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0xB0);  // Set register value to 1011 XXXX
          break;
        case 200:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0xC0);  // Set register value to 1100 XXXX
          break;
        case 400:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0xD0);  // Set register value to 1101 XXXX
          break;
        case 600:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0xE0);  // Set register value to 1110 XXXX
          break;
        case 800:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0xF0);  // Set register value to 1110 XXXX
          break;
      }
      switch (thi) {
        case 0:
          registerTwoValue = (registerTwoValue & 0xF0) | (0 * 0x0F);  // Set register value to XXXX 0000 
          break;
        case 5:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x01);  // Set register value to XXXX 0001 
          break;
        case 10:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x02);  // Set register value to XXXX 0010 
          break;
        case 15:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x03);  // Set register value to XXXX 0011 
          break;
        case 20:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x04);  // Set register value to XXXX 0100 
          break;
        case 25:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x05);  // Set register value to XXXX 0101 
          break;
        case 30:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x06);  // Set register value to XXXX 0110 
          break;
        case 35:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x07);  // Set register value to XXXX 0111
          break;
        case 40:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x08);  // Set register value to XXXX 1000 
          break;
        case 45:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x09);  // Set register value to XXXX 1001
          break;
        case 50:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x0A);  // Set register value to XXXX 1010 
          break;
        case 100:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x0B);  // Set register value to XXXX 1011 
          break;
        case 200:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x0C);  // Set register value to XXXX 1100 
          break;
        case 400:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x0D);  // Set register value to XXXX 1101 
          break;
        case 600:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x0E);  // Set register value to XXXX 1110 
          break;
        case 800:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1110 
          break;
      }

      if (pattern == PATTERN0) {
        writeRegister(_address, PATTERN0_SLOPER_TIME1, registerOneValue);
        writeRegister(_address, PATTERN0_SLOPER_TIME2, registerTwoValue);
      }
      else if (pattern == PATTERN1) {
        writeRegister(_address, PATTERN1_SLOPER_TIME1, registerOneValue);
        writeRegister(_address, PATTERN1_SLOPER_TIME2, registerTwoValue);
      }
      else if (pattern == PATTERN2) {
        writeRegister(_address, PATTERN2_SLOPER_TIME1, registerOneValue);
        writeRegister(_address, PATTERN2_SLOPER_TIME2, registerTwoValue);
      }
      else if (pattern == PATTERN3) {
        writeRegister(_address, PATTERN3_SLOPER_TIME1, registerOneValue);
        writeRegister(_address, PATTERN3_SLOPER_TIME2, registerTwoValue);
      }
  }

  void LP5815::startAutonomousAnimation() {
    writeRegister(_address, START_CMD, START_WORD);
    continueAutonomousAnimation();
  }

  void LP5815::pauseAutonomousAnimation() {
    uint8_t registerValue = readRegister(_address, PAUSE_CONTINUE);
    registerValue = (registerValue & 0xFE) | (1 * PAUSE_WORD); // Enables the last bit
    writeRegister(_address, PAUSE_CONTINUE, registerValue);
  }

  void LP5815::continueAutonomousAnimation() {
    uint8_t registerValue = readRegister(_address, PAUSE_CONTINUE);
    registerValue = (registerValue & 0xFE) | (1 * CONTINUE_WORD); // Disables the last bit
    writeRegister(_address, PAUSE_CONTINUE, registerValue);
  }

  void LP5815::stopAutonomousAnimation() {
    writeRegister(_address, STOP_CMD, STOP_WORD);
  }

  bool LP5815::checkFlag(int flag) {
    uint8_t registerValue = readRegister(_address, FLAG);
    switch (flag) {
      case 0: 
        registerValue = registerValue & 0x01; // Check the value of last bit
        break;
      case 1: 
        registerValue = ((registerValue >> 1) & 0x01); // Move bits certain amount to the right and then check the value of wanted flag
        break;
      case 2: 
        registerValue = ((registerValue >> 2) & 0x01); // Move bits certain amount to the right and then check the value of wanted flag
        break;
      case 3: 
        registerValue = ((registerValue >> 3) & 0x01); // Move bits certain amount to the right and then check the value of wanted flag
        break;
      case 4: 
        registerValue = ((registerValue >> 4) & 0x01); // Move bits certain amount to the right and then check the value of wanted flag
        break;
      case 5: 
        registerValue = ((registerValue >> 5) & 0x01); // Move bits certain amount to the right and then check the value of wanted flag
        break;
      case 6: 
        registerValue = ((registerValue >> 6) & 0x01); // Move bits certain amount to the right and then check the value of wanted flag
        break;
    }
    return registerValue;
  }

  void LP5815::clearFlag(int flag) {
    uint8_t registerValue = readRegister(_address, FLAG_CLR);
      switch (flag) {
        case 0:
          registerValue = (registerValue & 0xFC) | (1 * 0x01); // Disables the last bit
          break;
        case 1:
          registerValue = (registerValue & 0xFC) | (1 * 0x02); // Disables the second last bit
          break;
    writeRegister(_address, FLAG_CLR, registerValue);
      }
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

  LP5814::LP5814(uint8_t adressOfDevice) : LP58XX(_SCL, _SDA) { // Object LP58XX has to be created here directly
    _address = adressOfDevice;
  }

  void LP5814::enable() {
    uint8_t registerValue = readRegister(_address, CHIP_EN);
    registerValue = (registerValue & 0xFE) | (1 * 0x01); // Enables the last bit
    writeRegister(_address, CHIP_EN, registerValue);
  }

  void LP5814::disable() {
    uint8_t registerValue = readRegister(_address, CHIP_EN);
    registerValue = (registerValue & 0xFE) | (0 * 0x01); // Disables the last bit
    writeRegister(_address, CHIP_EN, registerValue);
  }

  void LP5814::reset() {
    writeRegister(_address, RESET_CMD, RESET_WORD);
  }

  void LP5814::update() {
    writeRegister(_address, UPDATE_CMD, UPDATE_WORD);
  }

  void LP5814::setMaxCurrent(bool maxCurrent) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG0);
      if (maxCurrent == false) {
    registerValue = (registerValue & 0xFE) | (0 * 0x01); // Disables the last bit
      }
      else {
    registerValue = (registerValue & 0xFE) | (1 * 0x01); // Disables the last bit
      }
    writeRegister(_address, DEV_CONFIG0, registerValue);
  }

  void LP5814::enableOutput(int firstOutput, int secondOutput, int thirdOutput, int fourthOutput) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG1);
    int sum = 0;
      if (firstOutput == false && secondOutput == false && thirdOutput == false && fourthOutput == false) {  // If all variables are not set or set ALL / Drive all outputs
        sum = 0;
      }
      if (firstOutput != false && secondOutput == false && thirdOutput == false && fourthOutput == false) {
        sum = firstOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput == false && fourthOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false && fourthOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false && fourthOutput != false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD + fourthOutput + ADD;
      }
    switch (sum) {
      case 0:
        registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1111
        break;
      case 4:
        registerValue = (registerValue & 0xF0) | (1 * 0x01);  // Set register value to XXXX 0001
        break;
      case 5:
        registerValue = (registerValue & 0xF0) | (1 * 0x02);  // Set register value to XXXX 0010
        break;
      case 6:
        registerValue = (registerValue & 0xF0) | (1 * 0x04);  // Set register value to XXXX 0100
        break;
      case 8:
        registerValue = (registerValue & 0xF0) | (1 * 0x08);  // Set register value to XXXX 1000
        break;
      case 9:
        registerValue = (registerValue & 0xF0) | (1 * 0x03);  // Set register value to XXXX 0011
        break;
      case 10:
        registerValue = (registerValue & 0xF0) | (1 * 0x05);  // Set register value to XXXX 0101
        break;
      case 12:
        registerValue = (registerValue & 0xF0) | (1 * 0x09);  // Set register value to XXXX 1001
        break;
      case 11:
        registerValue = (registerValue & 0xF0) | (1 * 0x06);  // Set register value to XXXX 0110
        break;
      case 13:
        registerValue = (registerValue & 0xF0) | (1 * 0x0A);  // Set register value to XXXX 1010
        break;
      case 14:
        registerValue = (registerValue & 0xF0) | (1 * 0x0C);  // Set register value to XXXX 1100
        break;
      case 15:
        registerValue = (registerValue & 0xF0) | (1 * 0x07);  // Set register value to XXXX 0111
        break;
      case 17:
        registerValue = (registerValue & 0xF0) | (1 * 0x0B);  // Set register value to XXXX 1011
        break;
      case 18:
        registerValue = (registerValue & 0xF0) | (1 * 0x0D);  // Set register value to XXXX 1101
        break;
      case 19:
        registerValue = (registerValue & 0xF0) | (1 * 0x0E);  // Set register value to XXXX 1110
        break;
      case 23:
        registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1111
        break;
      } 
    writeRegister(_address, DEV_CONFIG1, registerValue);
  }

  void LP5814::enableFade(int firstOutput, int secondOutput, int thirdOutput, int fourthOutput) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG2);
    int sum = 0;
      if (firstOutput == false && secondOutput == false && thirdOutput == false && fourthOutput == false) {  // If all variables are not set or set ALL / Drive all outputs
        sum = 0;
      }
      if (firstOutput != false && secondOutput == false && thirdOutput == false && fourthOutput == false) {
        sum = firstOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput == false && fourthOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false && fourthOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false && fourthOutput != false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD + fourthOutput + ADD;
      }
    switch (sum) {
      case 0:
        registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1111
        break;
      case 4:
        registerValue = (registerValue & 0xF0) | (1 * 0x01);  // Set register value to XXXX 0001
        break;
      case 5:
        registerValue = (registerValue & 0xF0) | (1 * 0x02);  // Set register value to XXXX 0010
        break;
      case 6:
        registerValue = (registerValue & 0xF0) | (1 * 0x04);  // Set register value to XXXX 0100
        break;
      case 8:
        registerValue = (registerValue & 0xF0) | (1 * 0x08);  // Set register value to XXXX 1000
        break;
      case 9:
        registerValue = (registerValue & 0xF0) | (1 * 0x03);  // Set register value to XXXX 0011
        break;
      case 10:
        registerValue = (registerValue & 0xF0) | (1 * 0x05);  // Set register value to XXXX 0101
        break;
      case 12:
        registerValue = (registerValue & 0xF0) | (1 * 0x09);  // Set register value to XXXX 1001
        break;
      case 11:
        registerValue = (registerValue & 0xF0) | (1 * 0x06);  // Set register value to XXXX 0110
        break;
      case 13:
        registerValue = (registerValue & 0xF0) | (1 * 0x0A);  // Set register value to XXXX 1010
        break;
      case 14:
        registerValue = (registerValue & 0xF0) | (1 * 0x0C);  // Set register value to XXXX 1100
        break;
      case 15:
        registerValue = (registerValue & 0xF0) | (1 * 0x07);  // Set register value to XXXX 0111
        break;
      case 17:
        registerValue = (registerValue & 0xF0) | (1 * 0x0B);  // Set register value to XXXX 1011
        break;
      case 18:
        registerValue = (registerValue & 0xF0) | (1 * 0x0D);  // Set register value to XXXX 1101
        break;
      case 19:
        registerValue = (registerValue & 0xF0) | (1 * 0x0E);  // Set register value to XXXX 1110
        break;
      case 23:
        registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1111
        break;
      } 
    writeRegister(_address, DEV_CONFIG2, registerValue);
  }

  void LP5814::setFadeTime(float fadeValue) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG2);
    int value = fadeValue * 100;
      switch(value) {
        case 0:
          registerValue = (registerValue & 0x0F) | (0 * 0x00);  // Set register value to 1110 XXXX
          break;
        case 5:
          registerValue = (registerValue & 0x0F) | (1 * 0x10);  // Set register value to 0001 XXXX
          break;
        case 10:
          registerValue = (registerValue & 0x0F) | (1 * 0x20);  // Set register value to 0010 XXXX
          break;
        case 15:
          registerValue = (registerValue & 0x0F) | (1 * 0x30);  // Set register value to 0011 XXXX
          break;
        case 20:
          registerValue = (registerValue & 0x0F) | (1 * 0x40);  // Set register value to 0100 XXXX
          break;
        case 25:
          registerValue = (registerValue & 0x0F) | (1 * 0x50);  // Set register value to 0101 XXXX
          break;
        case 30:
          registerValue = (registerValue & 0x0F) | (1 * 0x60);  // Set register value to 0110 XXXX
          break;
        case 35:
          registerValue = (registerValue & 0x0F) | (1 * 0x70);  // Set register value to 0111 XXXX
          break;
        case 40:
          registerValue = (registerValue & 0x0F) | (1 * 0x80);  // Set register value to 1000 XXXX
          break;
        case 45:
          registerValue = (registerValue & 0x0F) | (1 * 0x90);  // Set register value to 1001 XXXX
          break;
        case 50:
          registerValue = (registerValue & 0x0F) | (1 * 0xA0);  // Set register value to 1010 XXXX
          break;
        case 100:
          registerValue = (registerValue & 0x0F) | (1 * 0xB0);  // Set register value to 1011 XXXX
          break;
        case 200:
          registerValue = (registerValue & 0x0F) | (1 * 0xC0);  // Set register value to 1100 XXXX
          break;
        case 400:
          registerValue = (registerValue & 0x0F) | (1 * 0xD0);  // Set register value to 1101 XXXX
          break;
        case 600:
          registerValue = (registerValue & 0x0F) | (1 * 0xE0);  // Set register value to 1110 XXXX
          break;
        case 800:
          registerValue = (registerValue & 0x0F) | (1 * 0xF0);  // Set register value to 1111 XXXX
          break;
      }

    writeRegister(_address, DEV_CONFIG2, registerValue);
  }

  void LP5814::setFadeType(bool fadeType, int firstOutput, int secondOutput, int thirdOutput, int fourthOutput) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG3);
    int sum = 0;
      if (firstOutput == false && secondOutput == false && thirdOutput == false && fourthOutput == false) {  // If all variables are not set or set ALL / Drive all outputs
        sum = 0;
      }
      if (firstOutput != false && secondOutput == false && thirdOutput == false && fourthOutput == false) {
        sum = firstOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput == false && fourthOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false && fourthOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false && fourthOutput != false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD + fourthOutput + ADD;
      }
    if (fadeType == EXPONENTIAL) { 
      switch (sum) {
        case 0: 
          registerValue = (registerValue & 0x0F) | (1 * 0x70);  // Set register value to X111 XXXX
          break;
        case 4:
          registerValue = (registerValue & 0xEF) | (1 * 0x10);  // Set register value to XXX1 XXXX
          break;
        case 5:
          registerValue = (registerValue & 0xDF) | (1 * 0x20);  // Set register value to XX1X XXXX
          break;
        case 6:
          registerValue = (registerValue & 0xBF) | (1 * 0x40);  // Set register value to X1XX XXXX
          break;
        case 8:
          registerValue = (registerValue & 0x7F) | (1 * 0x80);  // Set register value to 1XXX XXXX 
          break;
        case 9:
          registerValue = (registerValue & 0xCF) | (1 * 0x30);  // Set register value to XX11 XXXX
          break;
        case 10:
          registerValue = (registerValue & 0xAF) | (1 * 0x50);  // Set register value to X1X1 XXXX
          break;
        case 11:
          registerValue = (registerValue & 0x9F) | (1 * 0x60);  // Set register value to X11X XXXX
          break;
        case 12:
          registerValue = (registerValue & 0x6F) | (1 * 0x90);  // Set register value to 1XX1 XXXX 
          break;
        case 13:
          registerValue = (registerValue & 0x5F) | (1 * 0xA0);  // Set register value to 1X1X XXXX 
          break;
        case 14:
          registerValue = (registerValue & 0x3F) | (1 * 0xC0);  // Set register value to 11XX XXXX 
          break;
        case 15:
          registerValue = (registerValue & 0x8F) | (1 * 0x70);  // Set register value to X111 XXXX
          break;  
        case 17:
          registerValue = (registerValue & 0x4F) | (1 * 0xB0);  // Set register value to 1X11 XXXX 
          break;
        case 18:
          registerValue = (registerValue & 0x2F) | (1 * 0xD0);  // Set register value to 11X1 XXXX 
          break;
        case 19:
          registerValue = (registerValue & 0x1F) | (1 * 0xE0);  // Set register value to 111X XXXX 
          break;
        case 23:
          registerValue = (registerValue & 0x0F) | (1 * 0xF0);  // Set register value to 1111 XXXX 
          break;
      }
    }
    else if (fadeType == LINEAR) { 
      switch (sum) {
        case 0: 
          registerValue = (registerValue & 0x0F) | (0 * 0x70);  // Set register value to X111 XXXX
          break;
        case 4:
          registerValue = (registerValue & 0xEF) | (0 * 0x10);  // Set register value to XXX1 XXXX
          break;
        case 5:
          registerValue = (registerValue & 0xDF) | (0 * 0x20);  // Set register value to XX1X XXXX
          break;
        case 6:
          registerValue = (registerValue & 0xBF) | (0 * 0x40);  // Set register value to X1XX XXXX
          break;
        case 8:
          registerValue = (registerValue & 0x7F) | (0 * 0x80);  // Set register value to 1XXX XXXX 
          break;
        case 9:
          registerValue = (registerValue & 0xCF) | (0 * 0x30);  // Set register value to XX11 XXXX
          break;
        case 10:
          registerValue = (registerValue & 0xAF) | (0 * 0x50);  // Set register value to X1X1 XXXX
          break;
        case 11:
          registerValue = (registerValue & 0x9F) | (0 * 0x60);  // Set register value to X11X XXXX
          break;
        case 12:
          registerValue = (registerValue & 0x6F) | (0 * 0x90);  // Set register value to 1XX1 XXXX 
          break;
        case 13:
          registerValue = (registerValue & 0x5F) | (0 * 0xA0);  // Set register value to 1X1X XXXX 
          break;
        case 14:
          registerValue = (registerValue & 0x3F) | (0 * 0xC0);  // Set register value to 11XX XXXX 
          break;
        case 15:
          registerValue = (registerValue & 0x8F) | (0 * 0x70);  // Set register value to X111 XXXX
          break;  
        case 17:
          registerValue = (registerValue & 0x4F) | (0 * 0xB0);  // Set register value to 1X11 XXXX 
          break;
        case 18:
          registerValue = (registerValue & 0x2F) | (0 * 0xD0);  // Set register value to 11X1 XXXX 
          break;
        case 19:
          registerValue = (registerValue & 0x1F) | (0 * 0xE0);  // Set register value to 111X XXXX 
          break;
        case 23:
          registerValue = (registerValue & 0x0F) | (0 * 0xF0);  // Set register value to 1111 XXXX 
          break;
      }
    }
    writeRegister(_address, DEV_CONFIG3, registerValue);
  }

  void LP5814::setWorkingMode(bool workingMode, int firstOutput, int secondOutput, int thirdOutput, int fourthOutput) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG3);
    int sum = 0;
      if (firstOutput == false && secondOutput == false && thirdOutput == false && fourthOutput == false) {  // If all variables are not set or set ALL / Drive all outputs
        sum = 0;
      }
      if (firstOutput != false && secondOutput == false && thirdOutput == false && fourthOutput == false) {
        sum = firstOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput == false && fourthOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false && fourthOutput == false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD;
      }
      if (firstOutput != false && secondOutput != false && thirdOutput != false && fourthOutput != false) {
        sum = firstOutput + ADD + secondOutput + ADD + thirdOutput + ADD + fourthOutput + ADD;
      }
  if (workingMode == AUTOMATIC) { 
    switch (sum) {
      case 0:
        registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1111
        break;
      case 4:
        registerValue = (registerValue & 0xF0) | (1 * 0x01);  // Set register value to XXXX 0001
        break;
      case 5:
        registerValue = (registerValue & 0xF0) | (1 * 0x02);  // Set register value to XXXX 0010
        break;
      case 6:
        registerValue = (registerValue & 0xF0) | (1 * 0x04);  // Set register value to XXXX 0100
        break;
      case 8:
        registerValue = (registerValue & 0xF0) | (1 * 0x08);  // Set register value to XXXX 1000
        break;
      case 9:
        registerValue = (registerValue & 0xF0) | (1 * 0x03);  // Set register value to XXXX 0011
        break;
      case 10:
        registerValue = (registerValue & 0xF0) | (1 * 0x05);  // Set register value to XXXX 0101
        break;
      case 12:
        registerValue = (registerValue & 0xF0) | (1 * 0x09);  // Set register value to XXXX 1001
        break;
      case 11:
        registerValue = (registerValue & 0xF0) | (1 * 0x06);  // Set register value to XXXX 0110
        break;
      case 13:
        registerValue = (registerValue & 0xF0) | (1 * 0x0A);  // Set register value to XXXX 1010
        break;
      case 14:
        registerValue = (registerValue & 0xF0) | (1 * 0x0C);  // Set register value to XXXX 1100
        break;
      case 15:
        registerValue = (registerValue & 0xF0) | (1 * 0x07);  // Set register value to XXXX 0111
        break;
      case 17:
        registerValue = (registerValue & 0xF0) | (1 * 0x0B);  // Set register value to XXXX 1011
        break;
      case 18:
        registerValue = (registerValue & 0xF0) | (1 * 0x0D);  // Set register value to XXXX 1101
        break;
      case 19:
        registerValue = (registerValue & 0xF0) | (1 * 0x0E);  // Set register value to XXXX 1110
        break;
      case 23:
        registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1111
        break;
      } 
    }
    else if (workingMode == MANUAL) { 
    switch (sum) {
      case 0:
        registerValue = (registerValue & 0xF0) | (0 * 0x0F);  // Set register value to XXXX 1111
        break;
      case 4:
        registerValue = (registerValue & 0xF0) | (0 * 0x01);  // Set register value to XXXX 0001
        break;
      case 5:
        registerValue = (registerValue & 0xF0) | (0 * 0x02);  // Set register value to XXXX 0010
        break;
      case 6:
        registerValue = (registerValue & 0xF0) | (0 * 0x04);  // Set register value to XXXX 0100
        break;
      case 8:
        registerValue = (registerValue & 0xF0) | (0 * 0x08);  // Set register value to XXXX 1000
        break;
      case 9:
        registerValue = (registerValue & 0xF0) | (0 * 0x03);  // Set register value to XXXX 0011
        break;
      case 10:
        registerValue = (registerValue & 0xF0) | (0 * 0x05);  // Set register value to XXXX 0101
        break;
      case 12:
        registerValue = (registerValue & 0xF0) | (0 * 0x09);  // Set register value to XXXX 1001
        break;
      case 11:
        registerValue = (registerValue & 0xF0) | (0 * 0x06);  // Set register value to XXXX 0110
        break;
      case 13:
        registerValue = (registerValue & 0xF0) | (0 * 0x0A);  // Set register value to XXXX 1010
        break;
      case 14:
        registerValue = (registerValue & 0xF0) | (0 * 0x0C);  // Set register value to XXXX 1100
        break;
      case 15:
        registerValue = (registerValue & 0xF0) | (0 * 0x07);  // Set register value to XXXX 0111
        break;
      case 17:
        registerValue = (registerValue & 0xF0) | (0 * 0x0B);  // Set register value to XXXX 1011
        break;
      case 18:
        registerValue = (registerValue & 0xF0) | (0 * 0x0D);  // Set register value to XXXX 1101
        break;
      case 19:
        registerValue = (registerValue & 0xF0) | (0 * 0x0E);  // Set register value to XXXX 1110
        break;
      case 23:
        registerValue = (registerValue & 0xF0) | (0 * 0x0F);  // Set register value to XXXX 1111
        break;
      } 
    }
    writeRegister(_address, DEV_CONFIG3, registerValue);
  }

  void LP5814::setCurrent(int OUT0CurrentValue, int OUT1CurrentValue, int OUT2CurrentValue, int OUT3CurrentValue) {
    writeRegister(_address, OUT0_DC, OUT0CurrentValue);
    writeRegister(_address, OUT1_DC, OUT1CurrentValue);
    writeRegister(_address, OUT2_DC, OUT2CurrentValue);
    writeRegister(_address, OUT3_DC, OUT2CurrentValue);
  }

  void LP5814::setPWM(int OUT0PWMValue, int OUT1PWMValue, int OUT2PWMValue, int OUT3PWMValue) {
    writeRegister(_address, OUT0_MANUAL_PWM, OUT0PWMValue);
    writeRegister(_address, OUT1_MANUAL_PWM, OUT1PWMValue);
    writeRegister(_address, OUT2_MANUAL_PWM, OUT2PWMValue);
    writeRegister(_address, OUT3_MANUAL_PWM, OUT3PWMValue);
  }

  void LP5814::setOutEngine(uint8_t OUT0Engine, uint8_t OUT1Engine, uint8_t OUT2Engine, uint8_t OUT3Engine) {
    uint8_t registerValue = readRegister(_address, DEV_CONFIG4);
    registerValue = (OUT0Engine & 0x03) | ((OUT1Engine & 0x03) << 2) | ((OUT2Engine & 0x03) << 4) | ((OUT3Engine & 0x03) << 6);
    writeRegister(_address, DEV_CONFIG4, registerValue);
  }

  void LP5814::setEnginePatternOrder(uint8_t engine, uint8_t pattern0, uint8_t pattern1, uint8_t pattern2, uint8_t pattern3) {
    uint8_t registerValue = 0x00;
    registerValue = (pattern0 & 0x03) | ((pattern1 & 0x03) << 2) | ((pattern2 & 0x03) << 4) | ((pattern3 & 0x03) << 6);
      if (engine == ENGINE0) {
        writeRegister(_address, ENGINE_CONFIG0, registerValue);
      }
      else if (engine == ENGINE1) {
        writeRegister(_address, ENGINE_CONFIG1, registerValue);
      }
      else if (engine == ENGINE2) {
        writeRegister(_address, ENGINE_CONFIG2, registerValue);
      }
      else if (engine == ENGINE3) {
        writeRegister(_address, ENGINE_CONFIG3, registerValue);
      }
  }

  void LP5814::enableEnginePatternOrder(uint8_t engine, uint8_t patternEnable0, uint8_t patternEnable1, uint8_t patternEnable2, uint8_t patternEnable3) {
    uint8_t registerValue = 0x00;
      if (engine == ENGINE0) {
        registerValue = readRegister(_address, ENGINE_CONFIG4);
        registerValue = (registerValue & 0xF0) | (patternEnable0 & 0x01) | ((patternEnable1 & 0x01) << 1) | ((patternEnable2 & 0x01) << 2) | ((patternEnable3 & 0x01) << 3);  // Set register value to XXXX YYYY
        writeRegister(_address, ENGINE_CONFIG4, registerValue);
      }
      else if (engine == ENGINE1) {
        registerValue = readRegister(_address, ENGINE_CONFIG4);
        registerValue = (registerValue & 0x0F) | ((patternEnable0 & 0x01) << 4) | ((patternEnable1 & 0x01) << 5) | ((patternEnable2 & 0x01) << 6) | ((patternEnable3 & 0x01) << 7);  // Set register value to YYYY XXXX
        writeRegister(_address, ENGINE_CONFIG4, registerValue);
      }
      else if (engine == ENGINE2) {
        registerValue = readRegister(_address, ENGINE_CONFIG5);
        registerValue = (registerValue & 0xF0) | (patternEnable0 & 0x01) | ((patternEnable1 & 0x01) << 1) | ((patternEnable2 & 0x01) << 2) | ((patternEnable3 & 0x01) << 3);  // Set register value to XXXX YYYY
        writeRegister(_address, ENGINE_CONFIG5, registerValue);
      }
      else if (engine == ENGINE3) {
        registerValue = readRegister(_address, ENGINE_CONFIG5);
        registerValue = (registerValue & 0x0F) | ((patternEnable0 & 0x01) << 4) | ((patternEnable1 & 0x01) << 5) | ((patternEnable2 & 0x01) << 6) | ((patternEnable3 & 0x01) << 7);  // Set register value to YYYY XXXX
        writeRegister(_address, ENGINE_CONFIG5, registerValue);
      }
  }

  void LP5814::setEngineRepeatTime(uint8_t engine, uint8_t times) {
    uint8_t registerValue = readRegister(_address, ENGINE_CONFIG6);
      if (engine == ENGINE0) {
        registerValue = (registerValue & 0xFC) | (times);
      }
      else if (engine == ENGINE1) {
        registerValue = (registerValue & 0xF3) | (times << 2);
      }
      else if (engine == ENGINE2) {
        registerValue =  (registerValue & 0xCF) | (times << 4);
      }
      else if (engine == ENGINE3) {
        registerValue = (registerValue & 0x3F) | (times << 6);
      }
    writeRegister(_address, ENGINE_CONFIG6, registerValue);
   }

  void LP5814::setPatternPauseTime(uint8_t pattern, float pauseT0, float pauseT1) {
    uint8_t registerValue = 0x00;
    long int T0 = pauseT0 * 100;
    long int T1 = pauseT1 * 100;
      switch (T0) {
        case 0:
          registerValue = (registerValue & 0x0F) | (0 * 0xF0);  // Set register value to 0000 XXXX
          break;
        case 5:
          registerValue = (registerValue & 0x0F) | (1 * 0x10);  // Set register value to 0001 XXXX
          break;
        case 10:
          registerValue = (registerValue & 0x0F) | (1 * 0x20);  // Set register value to 0010 XXXX
          break;
        case 15:
          registerValue = (registerValue & 0x0F) | (1 * 0x30);  // Set register value to 0011 XXXX
          break;
        case 20:
          registerValue = (registerValue & 0x0F) | (1 * 0x40);  // Set register value to 0100 XXXX
          break;
        case 25:
          registerValue = (registerValue & 0x0F) | (1 * 0x50);  // Set register value to 0101 XXXX
          break;
        case 30:
          registerValue = (registerValue & 0x0F) | (1 * 0x60);  // Set register value to 0110 XXXX
          break;
        case 35:
          registerValue = (registerValue & 0x0F) | (1 * 0x70);  // Set register value to 0111 XXXX
          break;
        case 40:
          registerValue = (registerValue & 0x0F) | (1 * 0x80);  // Set register value to 1000 XXXX
          break;
        case 45:
          registerValue = (registerValue & 0x0F) | (1 * 0x90);  // Set register value to 1001 XXXX
          break;
        case 50:
          registerValue = (registerValue & 0x0F) | (1 * 0xA0);  // Set register value to 1010 XXXX
          break;
        case 100:
          registerValue = (registerValue & 0x0F) | (1 * 0xB0);  // Set register value to 1011 XXXX
          break;
        case 200:
          registerValue = (registerValue & 0x0F) | (1 * 0xC0);  // Set register value to 1100 XXXX
          break;
        case 400:
          registerValue = (registerValue & 0x0F) | (1 * 0xD0);  // Set register value to 1101 XXXX
          break;
        case 600:
          registerValue = (registerValue & 0x0F) | (1 * 0xE0);  // Set register value to 1110 XXXX
          break;
        case 800:
          registerValue = (registerValue & 0x0F) | (1 * 0xF0);  // Set register value to 1110 XXXX
          break;
      }
      switch (T1) {
        case 0:
          registerValue = (registerValue & 0xF0) | (0 * 0x0F);  // Set register value to XXXX 0000 
          break;
        case 5:
          registerValue = (registerValue & 0xF0) | (1 * 0x01);  // Set register value to XXXX 0001 
          break;
        case 10:
          registerValue = (registerValue & 0xF0) | (1 * 0x02);  // Set register value to XXXX 0010 
          break;
        case 15:
          registerValue = (registerValue & 0xF0) | (1 * 0x03);  // Set register value to XXXX 0011 
          break;
        case 20:
          registerValue = (registerValue & 0xF0) | (1 * 0x04);  // Set register value to XXXX 0100 
          break;
        case 25:
          registerValue = (registerValue & 0xF0) | (1 * 0x05);  // Set register value to XXXX 0101 
          break;
        case 30:
          registerValue = (registerValue & 0xF0) | (1 * 0x06);  // Set register value to XXXX 0110 
          break;
        case 35:
          registerValue = (registerValue & 0xF0) | (1 * 0x07);  // Set register value to XXXX 0111
          break;
        case 40:
          registerValue = (registerValue & 0xF0) | (1 * 0x08);  // Set register value to XXXX 1000 
          break;
        case 45:
          registerValue = (registerValue & 0xF0) | (1 * 0x09);  // Set register value to XXXX 1001
          break;
        case 50:
          registerValue = (registerValue & 0xF0) | (1 * 0x0A);  // Set register value to XXXX 1010 
          break;
        case 100:
          registerValue = (registerValue & 0xF0) | (1 * 0x0B);  // Set register value to XXXX 1011 
          break;
        case 200:
          registerValue = (registerValue & 0xF0) | (1 * 0x0C);  // Set register value to XXXX 1100 
          break;
        case 400:
          registerValue = (registerValue & 0xF0) | (1 * 0x0D);  // Set register value to XXXX 1101 
          break;
        case 600:
          registerValue = (registerValue & 0xF0) | (1 * 0x0E);  // Set register value to XXXX 1110 
          break;
        case 800:
          registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1110 
          break;
      }

      if (pattern == PATTERN0) {
        writeRegister(_address, PATTERN0_PAUSE_TIME, registerValue);
      }
      else if (pattern == PATTERN1) {
        writeRegister(_address, PATTERN1_PAUSE_TIME, registerValue);
      }
      else if (pattern == PATTERN2) {
        writeRegister(_address, PATTERN2_PAUSE_TIME, registerValue);
      }
      else if (pattern == PATTERN3) {
        writeRegister(_address, PATTERN3_PAUSE_TIME, registerValue);
      }
  }

  void LP5814::setPatternRepeatTime(uint8_t pattern, uint8_t repeatTimes) {
    uint8_t registerValue = 0x00;
      if (pattern == PATTERN0) {
        registerValue = readRegister(_address, PATTERN0_REPEAT_TIME);
      }
      else if (pattern == PATTERN1) {
        registerValue = readRegister(_address, PATTERN1_REPEAT_TIME);
      }
      else if (pattern == PATTERN2) {
        registerValue = readRegister(_address, PATTERN2_REPEAT_TIME);
      }
      else if (pattern == PATTERN3) {
        registerValue = readRegister(_address, PATTERN3_REPEAT_TIME);
      }

      switch (repeatTimes) {
        case 0:
          registerValue = (registerValue & 0xF0) | (0 * 0x0F);  // Set register value to XXXX 0000 
          break;
        case 1:
          registerValue = (registerValue & 0xF0) | (1 * 0x01);  // Set register value to XXXX 0001 
          break;
        case 2:
          registerValue = (registerValue & 0xF0) | (1 * 0x02);  // Set register value to XXXX 0010 
          break;
        case 3:
          registerValue = (registerValue & 0xF0) | (1 * 0x03);  // Set register value to XXXX 0011 
          break;
        case 4:
          registerValue = (registerValue & 0xF0) | (1 * 0x04);  // Set register value to XXXX 0100 
          break;
        case 5:
          registerValue = (registerValue & 0xF0) | (1 * 0x05);  // Set register value to XXXX 0101 
          break;
        case 6:
          registerValue = (registerValue & 0xF0) | (1 * 0x06);  // Set register value to XXXX 0110 
          break;
        case 7:
          registerValue = (registerValue & 0xF0) | (1 * 0x07);  // Set register value to XXXX 0111
          break;
        case 8:
          registerValue = (registerValue & 0xF0) | (1 * 0x08);  // Set register value to XXXX 1000 
          break;
        case 9:
          registerValue = (registerValue & 0xF0) | (1 * 0x09);  // Set register value to XXXX 1001
          break;
        case 10:
          registerValue = (registerValue & 0xF0) | (1 * 0x0A);  // Set register value to XXXX 1010 
          break;
        case 11:
          registerValue = (registerValue & 0xF0) | (1 * 0x0B);  // Set register value to XXXX 1011 
          break;
        case 12:
          registerValue = (registerValue & 0xF0) | (1 * 0x0C);  // Set register value to XXXX 1100 
          break;
        case 13:
          registerValue = (registerValue & 0xF0) | (1 * 0x0D);  // Set register value to XXXX 1101 
          break;
        case 14:
          registerValue = (registerValue & 0xF0) | (1 * 0x0E);  // Set register value to XXXX 1110 
          break;
        case 15:
          registerValue = (registerValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1110 
          break;
      }
      if (pattern == PATTERN0) {
        writeRegister(_address, PATTERN0_REPEAT_TIME, registerValue);
      }
      else if (pattern == PATTERN1) {
        writeRegister(_address, PATTERN1_REPEAT_TIME, registerValue);
      }
      else if (pattern == PATTERN2) {
        writeRegister(_address, PATTERN2_REPEAT_TIME, registerValue);
      }
      else if (pattern == PATTERN3) {
        writeRegister(_address, PATTERN3_REPEAT_TIME, registerValue);
      }
  }

  void LP5814::setPWMPattern(uint8_t pattern, uint8_t firstPWM, uint8_t secondPWM, uint8_t thirdPWM, uint8_t fourthPWM, uint8_t fifthPWM) {
    if (pattern == PATTERN0) {
      writeRegister(_address, PATTERN0_PWM0, firstPWM);
      writeRegister(_address, PATTERN0_PWM1, secondPWM);
      writeRegister(_address, PATTERN0_PWM2, thirdPWM);
      writeRegister(_address, PATTERN0_PWM3, fourthPWM);
      writeRegister(_address, PATTERN0_PWM4, fifthPWM);
    }
    else if (pattern == PATTERN1) {
      writeRegister(_address, PATTERN1_PWM0, firstPWM);
      writeRegister(_address, PATTERN1_PWM1, secondPWM);
      writeRegister(_address, PATTERN1_PWM2, thirdPWM);
      writeRegister(_address, PATTERN1_PWM3, fourthPWM);
      writeRegister(_address, PATTERN1_PWM4, fifthPWM);
    }
    else if (pattern == PATTERN2) {
      writeRegister(_address, PATTERN2_PWM0, firstPWM);
      writeRegister(_address, PATTERN2_PWM1, secondPWM);
      writeRegister(_address, PATTERN2_PWM2, thirdPWM);
      writeRegister(_address, PATTERN2_PWM3, fourthPWM);
      writeRegister(_address, PATTERN2_PWM4, fifthPWM);
    }
    else if (pattern == PATTERN3) {
      writeRegister(_address, PATTERN3_PWM0, firstPWM);
      writeRegister(_address, PATTERN3_PWM1, secondPWM);
      writeRegister(_address, PATTERN3_PWM2, thirdPWM);
      writeRegister(_address, PATTERN3_PWM3, fourthPWM);
      writeRegister(_address, PATTERN3_PWM4, fifthPWM);
    }
  }

  void LP5814::setPatternSloperTime(uint8_t pattern, float firstTime, float secondTime, float thirdTime, float fourthTime) {
    uint8_t registerOneValue = 0x00;
    uint8_t registerTwoValue = 0x00;
    long int fir = firstTime * 100;
    long int sec = secondTime * 100;
    long int thi = thirdTime * 100;
    long int fou = fourthTime * 100;
      switch (sec) {
        case 0:
          registerOneValue = (registerOneValue & 0x0F) | (0 * 0xF0);  // Set register value to 0000 XXXX
          break;
        case 5:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x10);  // Set register value to 0001 XXXX
          break;
        case 10:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x20);  // Set register value to 0010 XXXX
          break;
        case 15:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x30);  // Set register value to 0011 XXXX
          break;
        case 20:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x40);  // Set register value to 0100 XXXX
          break;
        case 25:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x50);  // Set register value to 0101 XXXX
          break;
        case 30:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x60);  // Set register value to 0110 XXXX
          break;
        case 35:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x70);  // Set register value to 0111 XXXX
          break;
        case 40:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x80);  // Set register value to 1000 XXXX
          break;
        case 45:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0x90);  // Set register value to 1001 XXXX
          break;
        case 50:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0xA0);  // Set register value to 1010 XXXX
          break;
        case 100:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0xB0);  // Set register value to 1011 XXXX
          break;
        case 200:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0xC0);  // Set register value to 1100 XXXX
          break;
        case 400:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0xD0);  // Set register value to 1101 XXXX
          break;
        case 600:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0xE0);  // Set register value to 1110 XXXX
          break;
        case 800:
          registerOneValue = (registerOneValue & 0x0F) | (1 * 0xF0);  // Set register value to 1110 XXXX
          break;
      }
      switch (fir) {
        case 0:
          registerOneValue = (registerOneValue & 0xF0) | (0 * 0x0F);  // Set register value to XXXX 0000 
          break;
        case 5:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x01);  // Set register value to XXXX 0001 
          break;
        case 10:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x02);  // Set register value to XXXX 0010 
          break;
        case 15:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x03);  // Set register value to XXXX 0011 
          break;
        case 20:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x04);  // Set register value to XXXX 0100 
          break;
        case 25:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x05);  // Set register value to XXXX 0101 
          break;
        case 30:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x06);  // Set register value to XXXX 0110 
          break;
        case 35:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x07);  // Set register value to XXXX 0111
          break;
        case 40:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x08);  // Set register value to XXXX 1000 
          break;
        case 45:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x09);  // Set register value to XXXX 1001
          break;
        case 50:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x0A);  // Set register value to XXXX 1010 
          break;
        case 100:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x0B);  // Set register value to XXXX 1011 
          break;
        case 200:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x0C);  // Set register value to XXXX 1100 
          break;
        case 400:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x0D);  // Set register value to XXXX 1101 
          break;
        case 600:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x0E);  // Set register value to XXXX 1110 
          break;
        case 800:
          registerOneValue = (registerOneValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1110 
          break;
      }
      switch (fou) {
        case 0:
          registerTwoValue = (registerTwoValue & 0x0F) | (0 * 0xF0);  // Set register value to 0000 XXXX
          break;
        case 5:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x10);  // Set register value to 0001 XXXX
          break;
        case 10:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x20);  // Set register value to 0010 XXXX
          break;
        case 15:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x30);  // Set register value to 0011 XXXX
          break;
        case 20:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x40);  // Set register value to 0100 XXXX
          break;
        case 25:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x50);  // Set register value to 0101 XXXX
          break;
        case 30:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x60);  // Set register value to 0110 XXXX
          break;
        case 35:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x70);  // Set register value to 0111 XXXX
          break;
        case 40:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x80);  // Set register value to 1000 XXXX
          break;
        case 45:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0x90);  // Set register value to 1001 XXXX
          break;
        case 50:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0xA0);  // Set register value to 1010 XXXX
          break;
        case 100:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0xB0);  // Set register value to 1011 XXXX
          break;
        case 200:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0xC0);  // Set register value to 1100 XXXX
          break;
        case 400:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0xD0);  // Set register value to 1101 XXXX
          break;
        case 600:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0xE0);  // Set register value to 1110 XXXX
          break;
        case 800:
          registerTwoValue = (registerTwoValue & 0x0F) | (1 * 0xF0);  // Set register value to 1110 XXXX
          break;
      }
      switch (thi) {
        case 0:
          registerTwoValue = (registerTwoValue & 0xF0) | (0 * 0x0F);  // Set register value to XXXX 0000 
          break;
        case 5:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x01);  // Set register value to XXXX 0001 
          break;
        case 10:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x02);  // Set register value to XXXX 0010 
          break;
        case 15:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x03);  // Set register value to XXXX 0011 
          break;
        case 20:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x04);  // Set register value to XXXX 0100 
          break;
        case 25:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x05);  // Set register value to XXXX 0101 
          break;
        case 30:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x06);  // Set register value to XXXX 0110 
          break;
        case 35:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x07);  // Set register value to XXXX 0111
          break;
        case 40:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x08);  // Set register value to XXXX 1000 
          break;
        case 45:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x09);  // Set register value to XXXX 1001
          break;
        case 50:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x0A);  // Set register value to XXXX 1010 
          break;
        case 100:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x0B);  // Set register value to XXXX 1011 
          break;
        case 200:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x0C);  // Set register value to XXXX 1100 
          break;
        case 400:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x0D);  // Set register value to XXXX 1101 
          break;
        case 600:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x0E);  // Set register value to XXXX 1110 
          break;
        case 800:
          registerTwoValue = (registerTwoValue & 0xF0) | (1 * 0x0F);  // Set register value to XXXX 1110 
          break;
      }

      if (pattern == PATTERN0) {
        writeRegister(_address, PATTERN0_SLOPER_TIME1, registerOneValue);
        writeRegister(_address, PATTERN0_SLOPER_TIME2, registerTwoValue);
      }
      else if (pattern == PATTERN1) {
        writeRegister(_address, PATTERN1_SLOPER_TIME1, registerOneValue);
        writeRegister(_address, PATTERN1_SLOPER_TIME2, registerTwoValue);
      }
      else if (pattern == PATTERN2) {
        writeRegister(_address, PATTERN2_SLOPER_TIME1, registerOneValue);
        writeRegister(_address, PATTERN2_SLOPER_TIME2, registerTwoValue);
      }
      else if (pattern == PATTERN3) {
        writeRegister(_address, PATTERN3_SLOPER_TIME1, registerOneValue);
        writeRegister(_address, PATTERN3_SLOPER_TIME2, registerTwoValue);
      }
  }

  void LP5814::startAutonomousAnimation() {
    writeRegister(_address, START_CMD, START_WORD);
    continueAutonomousAnimation();
  }

  void LP5814::pauseAutonomousAnimation() {
    uint8_t registerValue = readRegister(_address, PAUSE_CONTINUE);
    registerValue = (registerValue & 0xFE) | (1 * PAUSE_WORD); // Enables the last bit
    writeRegister(_address, PAUSE_CONTINUE, registerValue);
  }

  void LP5814::continueAutonomousAnimation() {
    uint8_t registerValue = readRegister(_address, PAUSE_CONTINUE);
    registerValue = (registerValue & 0xFE) | (1 * CONTINUE_WORD); // Disables the last bit
    writeRegister(_address, PAUSE_CONTINUE, registerValue);
  }

  void LP5814::stopAutonomousAnimation() {
    writeRegister(_address, STOP_CMD, STOP_WORD);
  }

  bool LP5814::checkFlag(int flag) {
    uint8_t registerValue = readRegister(_address, FLAG);
    switch (flag) {
      case 0: 
        registerValue = registerValue & 0x01; // Check the value of last bit
        break;
      case 1: 
        registerValue = ((registerValue >> 1) & 0x01); // Move bits certain amount to the right and then check the value of wanted flag
        break;
      case 2: 
        registerValue = ((registerValue >> 2) & 0x01); // Move bits certain amount to the right and then check the value of wanted flag
        break;
      case 3: 
        registerValue = ((registerValue >> 3) & 0x01); // Move bits certain amount to the right and then check the value of wanted flag
        break;
      case 4: 
        registerValue = ((registerValue >> 4) & 0x01); // Move bits certain amount to the right and then check the value of wanted flag
        break;
      case 5: 
        registerValue = ((registerValue >> 5) & 0x01); // Move bits certain amount to the right and then check the value of wanted flag
        break;
      case 6: 
        registerValue = ((registerValue >> 6) & 0x01); // Move bits certain amount to the right and then check the value of wanted flag
        break;
    }
    return registerValue;
  }

  void LP5814::clearFlag(int flag) {
    uint8_t registerValue = readRegister(_address, FLAG_CLR);
      switch (flag) {
        case 0:
          registerValue = (registerValue & 0xFC) | (1 * 0x01); // Disables the last bit
          break;
        case 1:
          registerValue = (registerValue & 0xFC) | (1 * 0x02); // Disables the last bit
          break;
    writeRegister(_address, FLAG_CLR, registerValue);
      }
  }
  








