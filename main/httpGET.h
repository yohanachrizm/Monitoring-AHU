#include <HTTPClient.h>
#include <WiFi.h>

// Konfigurasi server PHP
const char* serverIP = "10.203.163.29"; // Ganti dengan alamat IP server PHP Anda
const int serverPort = 80;
const char* serverPath = "/monitoring/controlFiller1.php"; // Ganti dengan path file PHP di server


//HTTPClient http;
WiFiClient client;

void sendData(float temp, float hum, float pres, float dpres, float otemp, float ohum, float opres) {
  HTTPClient http;
  // Kirim data secara berurutan
  String getData = "dataSuhu=" + String(temp) + "&dataKelembaban=" + String(hum) + "&dataTekanan=" + String(pres) + "&dataDPress=" + String(dpres) + "&dataSuhu2=" + String(otemp) + "&dataKelembaban2=" + String(ohum) + "&dataTekanan2=" + String(opres);
  
  // Buat URL dan header
  String url = "http://" + String(serverIP) + ":" + String(serverPort) + serverPath + "?" + getData;
  http.begin(client,url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Kirim data
  int httpResponseCode = http.GET();

  // Handle respons dari server
  if (httpResponseCode > 0) {
    Serial.print("Server response code: ");
    Serial.println(httpResponseCode);
    Serial.println(http.getString());
  } else {
    Serial.print("HTTP error code: ");
    Serial.println(httpResponseCode);
  }

  // Akhiri koneksi
  http.end();  
}