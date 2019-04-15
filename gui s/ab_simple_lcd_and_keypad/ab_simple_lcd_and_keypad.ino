#include <EEPROM.h>
// ======================= setup LCD 16x2 with i2c =======================
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
// awalnya 0x27 buat address nya
LiquidCrystal_PCF8574 lcd(0x20);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x20 ,2,1,0,4,5,6,7,3, POSITIVE);


#include "tombol.h"  // ============ setup tombol keypad 4x4 =============
#include "user_interface.h"
// ======================= setup LCD 16x2 with i2c =======================



int menu;
bool ui_menu = true;
bool menu_tujuan = false;
int goal = 0;

void setup() {
  
  // put your setup code here, to run once:

  tombol_setup();
  user_interface_setup();
  
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(22, OUTPUT);

  set_tujuan = EEPROM.read(address_tujuan);
  set_kecepatan = EEPROM.read(address_kecepatan);
  set_P = EEPROM.read(address_P);
  set_D = EEPROM.read(address_D);

  ui_tujuan();
  menu = 0;
}


void loop() {
  while(ui_menu == true) {
    if(tombol() == "F2") {menu++;}
    if(tombol() == "F1") {menu--;}
    if(menu >= 3)        {menu = 3;}
    if(menu <= 0)        {menu = 0;}
    
    if(menu == 0)        {goal = ui_tujuan().toInt();}    // konversi String to Int
    else if(menu == 1)   {ui_kecepatan();}
    else if(menu == 2)   {ui_setting_P();}
    else if(menu == 3)   {ui_setting_D();}
  
    if(tombol() == "OK") {menu_tujuan = true;}
    
    while(menu_tujuan == true){
      ui_go(goal);
      if(tombol() == "START") {
        menu_tujuan = false;
        ui_menu = false;
      }
      else if(tombol() == "0") {
        menu_tujuan = false;
      }
    }
  }
  
  while(true) {
    lcd.clear();
  }
  
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
