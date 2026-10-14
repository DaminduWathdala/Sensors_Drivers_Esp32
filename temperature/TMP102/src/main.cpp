#include"TMP102.h"

TMP102 sensor(0x48);

void setup(){
  Serial.begin(115200);
  while(!Serial);
  if(!sensor.begin()){
    Serial.println("Error: TMP10 not found");
    while(1);
  }

  sensor.conversionMode(1);
  sensor.setExtendedMode(false);
  sensor.setFaultQue(4);
  sensor.setShutdownMode(false);
  sensor.setUpperLimit(40.0f);
  sensor.setLowLimit(25.0f);

  Serial.println("Initialized Successfully");


}
void loop(){
  float temperature = sensor.readOneshotTemperature();
  Serial.print("Temperature is :");
  Serial.print(temperature);
  Serial.println("C");

  delay(60000);
}