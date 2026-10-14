#include"SHT40.h"
SHT40::SHT40(uint8_t address):_i2cAddress(address){}
void SHT40::begin(){
    Wire.begin();
}
uint16_t SHT40::readRegister(int8_t n){
    writeRegister(0xFD);

    delay(10);

    Wire.requestFrom(_i2cAddress,(uint8_t)6);
    if(Wire.available()>=6){
        uint16_t temp = (Wire.read()<<8) |Wire.read();
        uint8_t CRC = Wire.read();
        uint16_t Humi = (Wire.read()<<8) | Wire.read();
        switch (n){
            case 1:
             return Humi;
            case 2:
             return temp; 
              

        }
            return 0;
        
    }

}
void SHT40::writeRegister(uint8_t command){
    Wire.beginTransmission(_i2cAddress);
    Wire.write(command);
    Wire.endTransmission();

}
float SHT40::readTemperature(){
    int16_t raw = readRegister(1);
    float temperature = -45.0f + 175.0f * ((float)raw / 65535.0f);
    return temperature;


}
float SHT40::readHumidity(){
    int16_t raw = readRegister(2);
    float humidity = -6.0f + 125.0f * ((float)raw / 65535.0f);
    return humidity;
}