// ======================= setup LCD 16x2 with i2c =======================
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
// awalnya 0x27 buat address nya
LiquidCrystal_PCF8574 lcd(0x20);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x20 ,2,1,0,4,5,6,7,3, POSITIVE);
#include "user_interface.h"
// ======================= setup LCD 16x2 with i2c =======================


// ======================= setup tombol keypad 4x4 =======================
#include "tombol.h"
// ======================= setup tombol keypad 4x4 =======================


void setup() {
  
  // put your setup code here, to run once:

  tombol_setup();
  user_interface_setup();
}

String x;

void loop() {
  
  tombol();
  if(tombol() == "0")   x = "0";
  if(tombol() == "1")   x = "1";
  if(tombol() == "2")   x = "2";
  if(tombol() == "3")   x = "3";
  if(tombol() == "4")   x = "4";
  if(tombol() == "5")   x = "5";
  if(tombol() == "6")   x = "6";
  if(tombol() == "7")   x = "7";
  if(tombol() == "8")   x = "8";
  if(tombol() == "9")   x = "9";
  if(tombol() == "F1")   x = "F1";
  if(tombol() == "F2")   x = "F2";
  if(tombol() == "F3")   x = "F3";
  if(tombol() == "F4")   x = "F4";
  if(tombol() == "START")   x = "START";
  if(tombol() == "STOP")    x = "STOP";
  
  ui_tujuan(x);
  


}
