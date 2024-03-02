#include <Wire.h>
#include <BME280I2C.h>
#include <LiquidCrystal_I2C.h>
#include "lcd.h"
#include "connectWiFi.h"
#include "bme_in.h"
#include "bme_out.h"
#include "httpGET.h"

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Memulai LCD
  startLCD();

  // Menghubungkan ke WiFi
  connectingWiFi();
  
  // Inisialisasi sensor BME280 INDOOR
  initializeBMEin(bme_in);

  // Inisialisasi sensor BME280 OUTDOOR
  initializeBMEout(bme_out);
}

unsigned long lastMsg=0;  
unsigned long now;

void loop() {
  float itemp, ihum, ipres, otemp, ohum, opres, dpres, ipres_hpa, opres_hpa; 
  now = millis();
  if (now - lastMsg > (1000/3)){
    lastMsg = now;
    BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);   
    BME280::PresUnit presUnit(BME280::PresUnit_Pa);    
    BME280::PresUnit opresUnit(BME280::PresUnit_Pa);
    
    // Membaca data sensor BME280 INDOOR
    readBME(bme_in, ipres, itemp, ihum, tempUnit, presUnit);

    // Membaca data sensor BME280 OUTDOOR
    readBME(bme_out, opres, otemp, ohum, tempUnit, opresUnit);
    
    // Menghitung Perbedaan tekanan
    ipres_hpa = (ipres / 133.3224) + OFFSET_IPRES;
    opres_hpa = opres / 133.3224;
    dpres = ipres_hpa-opres_hpa;
    itemp = itemp + OFFSET_ITEMP;

    if(WiFi.status() == WL_CONNECTED){ // Jika koneksi WiFi terhubung
      // Menampilkan data pada LCD
      displayLCD(itemp, ihum, ipres, dpres);
      //publishBME_IN(itemp, ihum, ipres_hpa, dpres);
      sendData(itemp,ihum,ipres_hpa,dpres,otemp,ohum,opres_hpa);
      // Menampilkan data di Serial Monitor
      Serial.println("INDOOR Sensor:");
      displayData(itemp, ihum, ipres);
      Serial.println("OUTDOOR Sensor:");
      displayData(otemp, ohum, opres);
      Serial.print("Pressure Difference= ");
      Serial.print(dpres);
      Serial.println(" hPa");
    } else {
      reconnectWiFi();      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Connecting to : ");
      lcd.setCursor(0,1);
      lcd.print(ssid);
      delay(1000);
      displayLCD(itemp, ihum, ipres, dpres);
      
    }
  }
}
