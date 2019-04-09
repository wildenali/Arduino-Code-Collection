

// ======================= setup LCD 16x2 with i2c =======================
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
// awalnya 0x27 buat address nya
LiquidCrystal_PCF8574 lcd(0x20);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x20 ,2,1,0,4,5,6,7,3, POSITIVE);

// ======================= setup tombol keypad 4x4 =======================
#include "tombol.h"
// ======================= setup tombol keypad 4x4 =======================

#include "user_interface.h"
// ======================= setup LCD 16x2 with i2c =======================





void setup() {
  
  // put your setup code here, to run once:

  tombol_setup();
  user_interface_setup();
  
  pinMode(12, INPUT);
  pinMode(11, INPUT);
}



void loop() {

  
}




















//String abc;
//  ui_go(abc);
//  if(digitalRead(12) == LOW && digitalRead(11) == LOW) {
//    ui_tujuan();
//  }
//  else if(digitalRead(12) == HIGH && digitalRead(11) == LOW) {
//    ui_kecepatan();
//  }
//  else if(digitalRead(12) == LOW && digitalRead(11) == HIGH) {
//    ui_setting_P();    
//  }
//  else if(digitalRead(12) == HIGH && digitalRead(11) == HIGH) {
//    ui_setting_D();    
//  }
