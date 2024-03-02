#include <BME280I2C.h>

float OFFSET_IPRES = 6.0;
float OFFSET_ITEMP = -0.3;

BME280I2C::Settings settings_in(    
    BME280::OSR_X1,    
    BME280::OSR_X1,    
    BME280::OSR_X1,    
    BME280::Mode_Forced,    
    BME280::StandbyTime_1000ms,    
    BME280::Filter_Off,    
    BME280::SpiEnable_False,    
    BME280I2C::I2CAddr_0x76
);  
BME280I2C bme_in(settings_in); 

void initializeBMEin(BME280I2C &bme) {
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    delay(1000);
  }

  switch(bme.chipModel())   {      
    case BME280::ChipModel_BME280:        
      Serial.println("Found BME280 sensor! Success.");        
      break;      
    case BME280::ChipModel_BMP280:        
      Serial.println("Found BMP280 sensor! No Humidity available.");            
      break;      
    default:        
      Serial.println("Found UNKNOWN sensor! Error!");   
  }

  // Change some settings before using.    
  settings_in.tempOSR = BME280::OSR_X4;     
  bme.setSettings(settings_in); 
}

void readBME(BME280I2C &bme, float &pres, float &temp, float &hum, BME280::TempUnit tempUnit, BME280::PresUnit presUnit) {
  bme.read(pres, temp, hum, tempUnit, presUnit);
}

void displayData(float temp, float hum, float pres) {
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println(" °C");

  Serial.print("Humidity = ");
  Serial.print(hum);
  Serial.println(" %");

  Serial.print("Pressure = ");
  Serial.print(pres / 133.3224);
  Serial.println(" hPa");
}
