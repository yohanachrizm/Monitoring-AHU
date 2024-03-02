#include <BME280I2C.h>

BME280I2C::Settings settings_out(    
    BME280::OSR_X1,    
    BME280::OSR_X1,    
    BME280::OSR_X1,    
    BME280::Mode_Forced,    
    BME280::StandbyTime_1000ms,    
    BME280::Filter_Off,    
    BME280::SpiEnable_False,    
    BME280I2C::I2CAddr_0x77
);  
BME280I2C bme_out(settings_out); 

void initializeBMEout(BME280I2C &bme) {
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
  settings_out.tempOSR = BME280::OSR_X4;     
  bme.setSettings(settings_out); 
}
