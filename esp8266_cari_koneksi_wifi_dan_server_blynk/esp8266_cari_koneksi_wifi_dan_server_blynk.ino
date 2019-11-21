#define BLYNK_TIMEOUT_MS  750  // must be BEFORE BlynkSimpleEsp8266.h doesn't work !!!
#define BLYNK_HEARTBEAT   17   // must be BEFORE BlynkSimpleEsp8266.h works OK as 17s
#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;

char auth[] = "UvI7ROLjlUgOuwyfN4IKOtRvgY-dRe8k";


char ssid[] = "iPhone wilden";
char pass[] = "inimodem";
char server[]          = "blynk-cloud.com";
unsigned int port      = 8442;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.connectWiFi(ssid, pass);
  timer.setInterval(11000L, CheckConnection);
  Blynk.config(auth, server, port);
  Blynk.connect();
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
  if(Blynk.connected()){
    Blynk.run();
  }
  timer.run();
}
