#include <WiFi.h>
#ifndef STASSID
#define STASSID "DanShopFloor2"
#define STAPSK  "D4nIndustri4l"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;
void connectingWiFi(){
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to WiFi");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting to : ");
  lcd.setCursor(0,1);
  lcd.print(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  delay(3000);

  // Menampilkan informasi koneksi WiFi
  Serial.println("");
  Serial.println("Connected to WiFi");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connected to Wifi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  lcd.setCursor(0,1);
  lcd.print("IP Address: ");
  lcd.setCursor(0,2);
  lcd.print(WiFi.localIP());
  delay(3000);
}

void reconnectWiFi(){
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to WiFi");
}