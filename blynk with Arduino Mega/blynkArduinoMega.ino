#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// ===================== DHT 11 Configuration =====================
#include <DHT.h>
#define DHTPIN 2          // What digital pin we're connected to

//Pilih DHT yang di pakai
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301
DHT dht(DHTPIN, DHTTYPE);
// ================================================================

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "750cc8cf585f47ad89d23e5cfa9790e3";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "inimodem";
char pass[] = "inimodem";

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial1

// or Software Serial on Uno, Nano...
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);


int lm35, adc0;
int sensorsuhuPin = A0;

BlynkTimer timer;

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  int analogValue = analogRead(sensorsuhuPin);
  float millivolts = (analogValue/1024.0) * 5000;
  float celsius = millivolts / 10;
  Blynk.virtualWrite(V0, celsius);
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  delay(10);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  dht.begin();
  timer.setInterval(5000L, myTimerEvent); // di kirim per 5 detik
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}

