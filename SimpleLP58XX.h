#ifndef SimpleLP58XX
#define SimpleLP58XX
#include <Arduino.h>

// I2C adresses for LP58XX series

#define LP5814_STD_ADR 0x2C
#define LP5815_STD_ADR 0x2D
#define LP5816_STD_ADR 0x2C
#define LP5817_STD_ADR 0x2D

// Main registers shared between all LP58XX devices

#define CHIP_EN 0x0  // Enables the chip 
#define DEV_CONFIG0 0x01  // Max current setting
#define DEV_CONFIG1 0x02  // Output setting
#define DEV_CONFIG2 0x03  // Fade setting
#define DEV_CONFIG3 0x04  // Exponential fade setting
#define SHUTDOWN_CMD 0x0D  // Shuts down chip
#define RESET_CMD 0x0E  // Resets the chip
#define UPDATE_CMD 0x0F  // Uploads all changes
#define FLAG_CLR 0x13  // Resets flags
#define OUT0_DC 0x14  // Output current setting
#define OUT1_DC 0x15  // Output current setting
#define OUT2_DC 0x16  // Output current setting
#define OUT3_DC 0x17  // Output current setting
#define OUT0_MANUAL_PWM 0x18  // Output PWM setting
#define OUT1_MANUAL_PWM 0x19  // Output PWM setting
#define OUT2_MANUAL_PWM 0x1A  // Output PWM setting
#define OUT3_MANUAL_PWM 0x1B  // Output PWM setting
#define FLAG 0x40  // Checks flags

// Additional registers for LP5814 / LP5815 (Different physical pinout)

#define DEV_CONFIG4 0x05
#define ENGINE_CONFIG0 0x06
#define ENGINE_CONFIG1 0x07
#define ENGINE_CONFIG2 0x08
#define ENGINE_CONFIG3 0x09
#define ENGINE_CONFIG4 0x0A
#define ENGINE_CONFIG5 0x0B
#define ENGINE_CONFIG6 0x0C
#define START_CMD 0x10
#define STOP_CMD 0x11
#define PAUSE_CONTINUE 0x12
#define PATTERN0_PAUSE_TIME 0x1C
#define PATTERN0_REPEAT_TIME 0x1D
#define PATTERN0_PWM0 0x1E
#define PATTERN0_PWM1 0x1F
#define PATTERN0_PWM2 0x20
#define PATTERN0_PWM3 0x21
#define PATTERN0_PWM4 0x22
#define PATTERN0_SLOPER_TIME1 0x23
#define PATTERN0_SLOPER_TIME2 0x24
#define PATTERN1_PAUSE_TIME 0x25
#define PATTERN1_REPEAT_TIME 0x26
#define PATTERN1_PWM0 0x27
#define PATTERN1_PWM1 0x28
#define PATTERN1_PWM2 0x29
#define PATTERN1_PWM3 0x2A
#define PATTERN1_PWM4 0x2B
#define PATTERN1_SLOPER_TIME1 0x2C
#define PATTERN1_SLOPER_TIME2 0x2D
#define PATTERN2_PAUSE_TIME 0x2E
#define PATTERN2_REPEAT_TIME 0x2F
#define PATTERN2_PWM0 0x30
#define PATTERN2_PWM1 0x31
#define PATTERN2_PWM2 0x32
#define PATTERN2_PWM3 0x33
#define PATTERN2_PWM4 0x34
#define PATTERN2_SLOPER_TIME1 0x35
#define PATTERN2_SLOPER_TIME2 0x36
#define PATTERN3_PAUSE_TIME 0x37
#define PATTERN3_REPEAT_TIME 0x38
#define PATTERN3_PWM0 0x39
#define PATTERN3_PWM1 0x3A
#define PATTERN3_PWM2 0x3B
#define PATTERN3_PWM3 0x3C
#define PATTERN3_PWM4 0x3D
#define PATTERN3_SLOPER_TIME1 0x3E
#define PATTERN3_SLOPER_TIME2 0x3F

// Exact words required for device

#define SHUTDOWN_WORD 0x33
#define RESET_WORD 0xCC
#define UPDATE_WORD 0x55
#define START_WORD 0xFF
#define STOP_WORD 0xAA
#define PAUSE_WORD 0x01
#define CONTINUE_WORD 0x00

// Exact flags useb by the device

#define POR_FLAG 0x00
#define TSD_FLAG 0x01
#define ENGINE_BUSY_FLAG 0x02
#define OUT0_ENGINE_BUSY_FLAG 0x03
#define OUT1_ENGINE_BUSY_FLAG 0x04
#define OUT2_ENGINE_BUSY_FLAG 0x05
#define OUT3_ENGINE_BUSY_FLAG 0x06

// Definitions used by fuctions

#define OUT0 1
#define OUT1 2
#define OUT2 3
#define OUT3 5
#define ADD 3

#define EXPONENTIAL 1
#define LINEAR 0

#define AUTOMATIC 1
#define MANUAL 0

#define ENGINE0 0x00
#define ENGINE1 0x01
#define ENGINE2 0x02
#define ENGINE3 0x03

#define PATTERN0 0x00
#define PATTERN1 0x01
#define PATTERN2 0x02
#define PATTERN3 0x03

#define ENABLE 0x01
#define DISABLE 0x00

#define ONCE 0x00
#define TWICE 0x01
#define THRICE 0x02
#define INFINITE 0x03

class LP58XX {
    public:
        // Constructor
        LP58XX(uint8_t I2C_SCL, uint8_t  I2C_SDA);  // Defines different microcontroller
          // Methods
          void begin();  
    protected:
        // Variables 
        uint8_t _SCL;
        uint8_t _SDA;
          // Methods
          uint8_t readRegister(uint8_t address, uint8_t registerAddress);
          void writeRegister(uint8_t address, uint8_t registerAddress, uint8_t value);
            
};

class LP5817 : public LP58XX {
  public:
    // Constructor
      LP5817(uint8_t adressOfDevice = LP5817_STD_ADR);  // Start the transmission at chosen adress
        // Methods
        void enable();  // Enable device
        void disable();  // Disable device
        void reset();  // Reset the device to nominal settings
        void update();  // Upload changed values
        void setMaxCurrent(bool maxCurrent = false);  // FALSE - 25.5 mA; TRUE - 51 mA || Active if set to 1
        void enableOutput(int firstOutput = false, int secondOutput = false, int thirdOutput = false);  // 0 - Out 0 active; 1 - Out 1 active; 2 - Out 2 active; 3 - Out 1, 2 and 3 active; NONE - Out 1, 2 and 3 are not active || Active if set to 1
        void enableFade(int firstOutput = false, int secondOutput = false, int thirdOutput = false);  // 0 - Out 0 active; 1 - Out 1 active; 2 - Out 2 active; ALL - Out 1, 2 and 3 active; NONE - Out 1, 2 and 3 are not active || Active if set to 1
        void setFadeTime(float fadeValue = 0.0);  // 0 - 0.00s; 1 - 0.05s; 2 - 0.10s; 3 - 0.15s; 4 - 0.20s; 5 - 0.25s; 6 - 0.30s; 7 - 0.35s; 8 - 0.40s; 9 - 0.45s; 10 - 0.50s; 11 - 1.00s; 12 - 2.00s; 13 - 4.00s; 14 - 6.00s; 15 - 8.00s; 
        void setFadeType(bool fadeType = LINEAR, int firstOutput = false, int secondOutput = false, int thirdOutput = false);
        void setCurrent(int OUT0CurrentValue = 0, int OUT1secondCurrentValue = 0, int OUT2CurrentValue = 0);
        void setPWM(int OUT0PWMValue = 0, int OUT1PWMValue = 0, int OUT2PWMValue = 0);
        bool checkFlag(int flag);
        void clearFlag(int flag);
  private:
    // Variables
    uint8_t _address;
};    

class LP5816 : public LP58XX {
  public:
    // Constructor
      LP5816(uint8_t adressOfDevice = LP5816_STD_ADR);  // Start the transmission at chosen adress
        // Methods
        void enable();  // Enable device
        void disable();  // Disable device
        void reset();  // Reset the device to nominal settings
        void update();  // Upload changed values
        void setMaxCurrent(bool maxCurrent = false); 
        void enableOutput(int firstOutput = false, int secondOutput = false, int thirdOutput = false, int fourthOutput = false);  
        void enableFade(int firstOutput = false, int secondOutput = false, int thirdOutput = false, int fourthOutput = false);  
        void setFadeTime(float fadeValue = 0.0); 
        void setFadeType(bool fadeType = LINEAR, int firstOutput = false, int secondOutput = false, int thirdOutput = false, int fourthOutput = false);
        void setCurrent(int OUT0CurrentValue = 0, int OUT1secondCurrentValue = 0, int OUT2CurrentValue = 0, int OUT3CurrentValue = 0);
        void setPWM(int OUT0PWMValue = 0, int OUT1PWMValue = 0, int OUT2PWMValue = 0, int OUT3PWMValue = 0);
        bool checkFlag(int flag);
        void clearFlag(int flag);

  private:
    // Variables
    uint8_t _address;
};    

class LP5815 : public LP58XX {
  public:
    // Constructor
      LP5815(uint8_t adressOfDevice = LP5815_STD_ADR);  // Start the transmission at chosen adress
        // Methods
        void enable();  // Enable device
        void setInstantBlinking(bool value = false);  // Set instant blinking
        void disable();  // Disable device
        void reset();  // Reset the device to nominal settings
        void update();  // Upload changed values
        void setMaxCurrent(bool maxCurrent = false);  // FALSE - 25.5 mA; TRUE - 51 mA || Active if set to 1
        void enableOutput(int firstOutput = false, int secondOutput = false, int thirdOutput = false);  // 0 - Out 0 active; 1 - Out 1 active; 2 - Out 2 active; 3 - Out 1, 2 and 3 active; NONE - Out 1, 2 and 3 are not active || Active if set to 1
        void enableFade(int firstOutput = false, int secondOutput = false, int thirdOutput = false);  // 0 - Out 0 active; 1 - Out 1 active; 2 - Out 2 active; ALL - Out 1, 2 and 3 active; NONE - Out 1, 2 and 3 are not active || Active if set to 1
        void setFadeTime(float fadeValue = 0.0);  // 0 - 0.00s; 1 - 0.05s; 2 - 0.10s; 3 - 0.15s; 4 - 0.20s; 5 - 0.25s; 6 - 0.30s; 7 - 0.35s; 8 - 0.40s; 9 - 0.45s; 10 - 0.50s; 11 - 1.00s; 12 - 2.00s; 13 - 4.00s; 14 - 6.00s; 15 - 8.00s; 
        void setFadeType(bool fadeType = LINEAR, int firstOutput = false, int secondOutput = false, int thirdOutput = false);
        void setWorkingMode(bool workingMode = MANUAL, int firstOutput = false, int secondOutput = false, int thirdOutput = false);
        void setCurrent(int OUT0CurrentValue = 0, int OUT1secondCurrentValue = 0, int OUT2CurrentValue = 0);
        void setPWM(int OUT0PWMValue = 0, int OUT1PWMValue = 0, int OUT2PWMValue = 0);
        void setOutEngine(uint8_t OUT0Engine = ENGINE0, uint8_t OUT1Engine = ENGINE1, uint8_t OUT2Engine = ENGINE2);
        void setEnginePatternOrder(uint8_t engine = ENGINE0, uint8_t pattern0 = PATTERN0, uint8_t pattern1 = PATTERN1, uint8_t pattern2 = PATTERN2, uint8_t pattern3 = PATTERN3);
        void enableEnginePatternOrder(uint8_t engine = ENGINE0, uint8_t patternEnable0 = ENABLE, uint8_t patternEnable1 = ENABLE, uint8_t patternEnable2 = ENABLE, uint8_t patternEnable3 = ENABLE);
        void setEngineRepeatTime(uint8_t engine = ENGINE0, uint8_t times = 1);
        void setPatternPauseTime(uint8_t pattern = PATTERN0, float pauseT0 = 0.0, float pauseT1 = 0.0);
        void setPatternRepeatTime(uint8_t pattern = PATTERN0, uint8_t repeatTimes = 0x0F);
        void setPWMPattern(uint8_t pattern = PATTERN0, uint8_t firstPWM = 0, uint8_t secondPWM = 0, uint8_t thirdPWM = 0, uint8_t fourthPWM = 0, uint8_t fifthPWM = 0);
        void setPatternSloperTime(uint8_t pattern = PATTERN0, float firstTime = 0.0, float secondTime = 0.0, float thirdTime = 0.0, float fourthTime = 0.0);
        void startAutonomousAnimation();
        void pauseAutonomousAnimation(); 
        void continueAutonomousAnimation(); 
        void stopAutonomousAnimation();
        bool checkFlag(int flag);
        void clearFlag(int flag);

  private:
    // Variables
    uint8_t _address;
};    

class LP5814 : public LP58XX {
  public:
    // Constructor
      LP5814(uint8_t adressOfDevice = LP5814_STD_ADR);  // Start the transmission at chosen adress
        // Methods
        void enable();  // Enable device
        void disable();  // Disable device
        void reset();  // Reset the device to nominal settings
        void update();  // Upload changed values
        void setMaxCurrent(bool maxCurrent = false); 
        void enableOutput(int firstOutput = false, int secondOutput = false, int thirdOutput = false, int fourthOutput = false);  
        void enableFade(int firstOutput = false, int secondOutput = false, int thirdOutput = false, int fourthOutput = false);  
        void setFadeTime(float fadeValue = 0.0); 
        void setFadeType(bool fadeType = LINEAR, int firstOutput = false, int secondOutput = false, int thirdOutput = false, int fourthOutput = false);
        void setWorkingMode(bool workingMode = MANUAL, int firstOutput = false, int secondOutput = false, int thirdOutput = false, int fourthOutput = false);
        void setCurrent(int OUT0CurrentValue = 0, int OUT1secondCurrentValue = 0, int OUT2CurrentValue = 0, int OUT3CurrentValue = 0);
        void setPWM(int OUT0PWMValue = 0, int OUT1PWMValue = 0, int OUT2PWMValue = 0, int OUT3PWMValue = 0);
        void setOutEngine(uint8_t OUT0Engine = ENGINE0, uint8_t OUT1Engine = ENGINE1, uint8_t OUT2Engine = ENGINE2, uint8_t OUT3Engine = ENGINE3);
        void setEnginePatternOrder(uint8_t engine = ENGINE0, uint8_t pattern0 = PATTERN0, uint8_t pattern1 = PATTERN1, uint8_t pattern2 = PATTERN2, uint8_t pattern3 = PATTERN3);
        void enableEnginePatternOrder(uint8_t engine = ENGINE0, uint8_t patternEnable0 = ENABLE, uint8_t patternEnable1 = ENABLE, uint8_t patternEnable2 = ENABLE, uint8_t patternEnable3 = ENABLE);
        void setEngineRepeatTime(uint8_t engine = ENGINE0, uint8_t times = 1);
        void setPatternPauseTime(uint8_t pattern = PATTERN0, float pauseT0 = 0, float pauseT1 = 0);
        void setPatternRepeatTime(uint8_t pattern = PATTERN0, uint8_t repeatTimes = 0x0F);
        void setPWMPattern(uint8_t pattern = PATTERN0, uint8_t firstPWM = 0, uint8_t secondPWM = 0, uint8_t thirdPWM = 0, uint8_t fourthPWM = 0, uint8_t fifthPWM = 0);
        void setPatternSloperTime(uint8_t pattern = PATTERN0, float firstTime = 0x00, float secondTime = 0x00, float thirdTime = 0x00, float fourthTime = 0x00);
        void startAutonomousAnimation();
        void pauseAutonomousAnimation(); 
        void continueAutonomousAnimation(); 
        void stopAutonomousAnimation();
        bool checkFlag(int flag);
        void clearFlag(int flag);
  private:
    // Variables
    uint8_t _address;
};    

#endif