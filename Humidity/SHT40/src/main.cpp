#include"SHT40.h"
SHT40 sensor(0x44);
void setup(){
  Serial.begin(115200);
  while(!Serial);
  sensor.begin();
  Serial.println("SHT40 Initialized.");

}

void loop(){
  float temp = sensor.readTemperature();
  float humi = sensor.readHumidity();
  Serial.print("Temperaute: ");
  Serial.print(temp);
  Serial.print(",Humidity :");
  Serial.println(humi);

  delay(2000);

}