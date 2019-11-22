#define BLYNK_TIMEOUT_MS  750  // must be BEFORE BlynkSimpleEsp8266.h doesn't work !!!
#define BLYNK_HEARTBEAT   17   // must be BEFORE BlynkSimpleEsp8266.h works OK as 17s
#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

#include "ESP8266WiFi.h"      // file ini diperlukan untuk Scan WiFi

char auth[] = "UvI7ROLjlUgOuwyfN4IKOtRvgY-dRe8k";
//char ssid[] = "Ini apa";
//char pass[] = "Intiinovasiteknologi";
char ssid[] = "iPhone wilden";
char pass[] = "inimodem";
char server[]          = "blynk-cloud.com";
unsigned int port      = 8442;

#define ada       true
#define tidakada  false

#define online    true
#define offline   false

bool wifi_yg_dicari;
bool status_internet;

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Setup done");

  // Scan selama kurang lebih 30 detik
  bool cari_wifi = true;
  int scan_ke = 0;
  int i;
  while(cari_wifi == true){
    Serial.print("scan start ");
    Serial.print("ke-");
    Serial.println(scan_ke);
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    scan_ke++;
    if (n == 0 && scan_ke >= 30) {        // Jika tidak ada WiFi sama sekali dan sudah nge scan sebanyak 30 kali, maka wifi_yg_dicari = tidakada
      Serial.println("no networks found");
      wifi_yg_dicari = tidakada;
      cari_wifi = false;
    }
    else if (n != 0 && scan_ke >= 30){    // Jika ada WiFi dan sudah nge scan sebanyak 30 kali, tapi tidak kunjung konek ke WiFi yg diharapkan (contoh: WiFi.SSID(i) == "Itu apa") maka wifi_yg_dicari = tidakada
      Serial.println("no networks found_");
      wifi_yg_dicari = tidakada;
      cari_wifi = false;
    }
    else {                                // Cari Wifi 
      Serial.print(n);
      Serial.println(" networks found");
      for (i = 0; i < n; ++i) {
        // Print SSID and RSSI for each network found
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
        delay(10);
        
        if(WiFi.SSID(i) == ssid) {    // Jika ada WiFi dan kunjung konek ke WiFi yg diharapkan sesuai ssid yang telah ditentukan maka wifi_yg_dicari = ada
          wifi_yg_dicari = ada;       // wifi_yg_dicari jadi ada
          cari_wifi = false;          // jadi kalau ketemu WiFi dengan SSID yang telah ditentukan, dia langsung keluar fungsi scan_wifi
        }
      }
    }
    Serial.println("");
    delay(1000);    
  }
  
  Serial.println("scan SELESAI");
  Serial.print("WiFi yang di cari = ");
  if(wifi_yg_dicari == ada) Serial.println("ada");
  else                      Serial.println("tidak ada");


  if(wifi_yg_dicari == ada) {
    Blynk.connectWiFi(ssid, pass);
    timer.setInterval(60000L, CheckConnection);
    Blynk.config(auth, server, port);
    Blynk.connect();
    status_internet = online;
  }
  else{
    status_internet = offline;
  }
  
}

void CheckConnection(){    // check every 11s if connected to Blynk server
  if(!Blynk.connected()){
    Serial.println("Not connected to Blynk server"); 
    Blynk.connect();  // try to connect to server with default timeout
  }
  else{
    Serial.println("Connected to Blynk server");     
  }
}

void loop() {
  if(status_internet == online && Blynk.connected()) {
    Blynk.run();
    Serial.println("mode online, konek ke blynk server");
  }
  else{
    Serial.println("mode offline, tidak konek ke blynk server");
  }
  timer.run();
}
