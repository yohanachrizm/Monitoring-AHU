#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Alamat I2C dan ukuran LCD

void startLCD(){
  lcd.begin(20, 4);  // Inisialisasi LCD
  lcd.backlight();   // Nyalakan backlight LCD
}

void displayLCD(float temp_in, float hum_in, float pres_in, float pres_dif) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.print(temp_in);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity  :");
  lcd.print(hum_in);
  lcd.print("%");

  lcd.setCursor(0, 2);
  lcd.print("PresIN    :");
  lcd.print(pres_in / 133.3224);
  lcd.print("hPa");

  lcd.setCursor(0, 3);
  lcd.print("PresDif   :");
  lcd.print(pres_dif);
  lcd.print("hPa");
}