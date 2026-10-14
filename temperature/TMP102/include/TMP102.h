#ifndef TMP102_H
#define TMP102_H 
#include <Arduino.h>
#include<Wire.h>

class TMP102{
    private:
     uint8_t _i2Address;
     bool _extendedMode;


     //register Pointers
     static const uint8_t REG_TEMP{0x00};
     static const uint8_t REG_CONFIG{0x01};
     static const uint8_t REG_TLOW{0x02};
     static const uint8_t REG_THIGH{0x03};

     uint16_t readRegister(uint8_t reg);
     void writeRegister(uint8_t reg,uint16_t value);
    
    public:
      TMP102(uint8_t address);
      
      bool begin();

      //configuration access

      uint16_t readConfig();
      void writeConfig(uint16_t config);
      void conversionMode(float rate);


      //Threshold limits
      void setUpperLimit(float celsius);
      void setLowLimit(float celsius);

      //operation mode
      void setShutdownMode(bool enable);
      void setExtendedMode(bool enable);
      

      //Alert mode and fault queue
      void setThermosetMode(bool interruptMOde);
      void setFaultQue(uint8_t faults);

      //__Temperature Reading
      float readOneshotTemperature();
      float readTemperature();
      int16_t readrawTemperature();
      float convertRawToCelsius(int16_t raw);







};

#endif