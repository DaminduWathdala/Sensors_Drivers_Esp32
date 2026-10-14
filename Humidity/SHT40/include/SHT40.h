#ifndef SHT40_SENSOR_H
#define SHT40_SENSOR_H
#include<Wire.h>
#include<Arduino.h>

class SHT40{
    private:
     uint8_t  _i2cAddress;
      uint16_t readRegister(int8_t n);
      void writeRegister(uint8_t command=0xFD);
    public:
      SHT40(uint8_t address=0x44);
      void begin();
      float readTemperature();
      float readHumidity();
      
};
#endif