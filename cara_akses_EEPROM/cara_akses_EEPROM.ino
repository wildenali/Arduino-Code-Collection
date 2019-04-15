#include <EEPROM.h>
int address1 = 0;
int address2 = 1;
int address3 = 2;
int data1, data2, data3;
int val1, val2, val3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){;}
  pinMode(36, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean tombol1 = digitalRead(36);
  boolean  tombol2 = digitalRead(34);
  
  if (tombol1 == 0){
    delay(500);
    data1++;
    data2 = data1 + 4;
    data3 = data1 + 9;
    Serial.print(data1);
    Serial.print("\t");
    Serial.print(data2);
    Serial.print("\t");
    Serial.println(data3);
    EEPROM.write(address1, data1);
    EEPROM.write(address2, data2);
    EEPROM.write(address3, data3);
  }
  else if(tombol2 == 0){
//    bisa kaya gini
//    val1 = EEPROM.read(address1);
//    val2 = EEPROM.read(address2);
//    Serial.print(val2);
//    Serial.print("\t");
//    Serial.println(val2);

//    atau bisa kaya gini
    data1 = EEPROM.read(address1);
    data2 = EEPROM.read(address2);
    data3 = EEPROM.read(address3);
    Serial.print(data1);
    Serial.print("\t");
    Serial.print(data2);
    Serial.print("\t");
    Serial.println(data3);
  }
 
}
