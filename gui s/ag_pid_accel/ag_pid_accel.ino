/*================ Pixy ========================================================*/
#include <Pixy2.h>
Pixy2 pixy;

#include <EEPROM.h>
// ======================= setup LCD 16x2 with i2c =======================
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
// awalnya 0x27 buat address nya
LiquidCrystal_PCF8574 lcd(0x20);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x20 ,2,1,0,4,5,6,7,3, POSITIVE);
// ======================= setup LCD 16x2 with i2c =======================




#include "tombol.h"           // ============ setup tombol keypad 4x4 =============
#include "follow_track.h"
#include "accel_speed.h"      // ======================= accel_speed =======================
#include "user_interface.h"   // ======================= user interface =======================

void setup() {
// SETINGAN BARU =================================================================================
  Serial1.begin(19200);
  Serial.begin(115200);
  Serial.print("Starting...\n");

  pinMode(MotorKiri, OUTPUT);
  pinMode(MotorKanan, OUTPUT);

  analogWrite(MotorKiri, 127);
  analogWrite(MotorKanan, 127);   
// SETINGAN BARU =================================================================================

  tombol_setup();
  user_interface_setup();

  set_tujuan = EEPROM.read(address_tujuan);
  set_kecepatan = EEPROM.read(address_kecepatan);
  kp = EEPROM.read(address_P);
  kd = EEPROM.read(address_D);

  ui_tujuan();
  menu = 0;
}


void loop() {
//  user_interface_menu_utama();
  
  while(tombol() == "STARTSTOP3") {
    
    accel_motor(5000, 100);
    hitungPID();
    eksekusimotor();
    
    delay(50);
    lcd.clear();
    ui_menu = true;
  }
  
}

















