#include <EEPROM.h>
int data1;
int eeAddress = 0;
  
void setup() {
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);

  Serial.begin(9600);
  while(!Serial){;}
  EEPROM.begin(512);
//  EEPROM.get(eeAddress, data1);
}

void loop() {
  
  boolean tombol1 = digitalRead(D1);
  boolean tombol2 = digitalRead(D2);
  
  if (tombol1 == 0){
    delay(500);
    data1++;
    Serial.print(data1);
    Serial.print("\t");
    EEPROM.put(eeAddress, data1);
    EEPROM.commit();
    Serial.println("Written");
    }
  else if(tombol2 == 0){
    EEPROM.get(eeAddress, data1);
    Serial.println(data1);
  }
 
}
