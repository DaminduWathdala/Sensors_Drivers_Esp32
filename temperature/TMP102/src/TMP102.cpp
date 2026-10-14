#include"TMP102.h"
TMP102::TMP102(uint8_t address):_i2Address(address),_extendedMode(false){}
bool TMP102::begin(){
    Wire.begin();
    uint16_t config = readConfig();
    return true;
}
uint16_t TMP102::readRegister(uint8_t reg){
    Wire.beginTransmission(_i2Address);
    Wire.write(reg);
    Wire.endTransmission(false);

    Wire.requestFrom(_i2Address,(uint8_t)2);
    if (Wire.available()>=2){
        uint16_t msb = Wire.read();
        uint8_t lsb = Wire.read();
        return (msb<<8)|lsb;
 }
    return 0;
}
void TMP102::writeRegister(uint8_t reg,uint16_t value){
    Wire.beginTransmission(_i2Address);
    Wire.write(reg);
    Wire.write((value>>8)&0xFF); //MSB
    Wire.write(value & 0xFF);
    Wire.endTransmission();
}
uint16_t TMP102::readConfig(){
    return readRegister(REG_CONFIG);
}
void TMP102::writeConfig(uint16_t config){
    writeRegister(REG_CONFIG,config);

}
void TMP102::conversionMode(float rate){
    uint16_t config = readConfig();
    if(rate==0.25){
        config |= (0b00<<6);
        }else if(rate==1){
            config |=(1<<6);
        }else if(rate==4){
            config |=(1<<7);
        }else{
            config |=(0b11<<6);
        }
    writeConfig(config);    
    
    
    }
void TMP102::setExtendedMode(bool enable){
    _extendedMode = enable;
    uint16_t config = readConfig();
    if(enable){
        config |= (1<<4);
    }else{
        config &= ~(1<<4);
    } 
writeConfig(config);    

}
void TMP102::setShutdownMode(bool enable){
    uint16_t config = readConfig();
    if(enable){
        config |= (1<<8);

    }else{
        config &= ~(1<<8);
    }
writeConfig(config);    

}
float TMP102::readOneshotTemperature(){
    uint16_t config = readConfig();
    config |= (1<<8);
    config |= (1<<15);
    
    delay(15);

    int16_t raw = readrawTemperature();
    return convertRawToCelsius(raw);
}
void TMP102::setFaultQue(uint8_t fault){
    uint16_t config = readConfig();
    config &=~(0b00<<11);
    switch (fault){
        case 1: config |=(0b00<<11);
        case 2: config |=(0b01<<11);
        case 3: config |=(0b10<<11);
        case 4: config |=(0b11<<11);
        default: config |=(0b00<<11);
    }
writeConfig(config);
}
void TMP102::setThermosetMode(bool interruptMOde){
    uint16_t config = readConfig();
    if(interruptMOde){
        config |=(1<<9);
    }else{
        config &= ~(1<<9);
    }
writeConfig(config);    
}
float TMP102::readTemperature(){
    int16_t raw = readrawTemperature();
    return convertRawToCelsius(raw);
}
int16_t TMP102::readrawTemperature(){
    uint16_t rawdata = readRegister(REG_TEMP);
    if(_extendedMode){
        return(int16_t)rawdata>>3;
    }else{
        return (int16_t)rawdata >>4;
    }
}
float TMP102::convertRawToCelsius(int16_t raw){
    return raw *0.0625f;
}

void TMP102::setUpperLimit(float celsius){
    int16_t raw = (int16_t)(celsius/0.0625f);
    if(_extendedMode){
        raw <<=3;
    }else{
        raw<<=4;
    }
    writeRegister(REG_THIGH,raw);
}
void TMP102::setLowLimit(float celsius){
    int16_t raw = (int16_t)(celsius/0.0625f);
    if(_extendedMode){
        raw<<=3;

    }else{
        raw<<=4;
    }
writeRegister(REG_THIGH,raw);
}