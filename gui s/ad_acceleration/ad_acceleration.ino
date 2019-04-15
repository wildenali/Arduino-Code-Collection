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



unsigned long currentTime = millis();
static unsigned long lastAccelTime = 0;
int selisih_waktu = 0;
int count_down;
int persen_acc;
float persen_accel;
int accel_aktif = true;

int pwm_kiri, pwm_kanan;

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
  
    if(tombol() == "OK") {menu_tujuan = true; accel_aktif = true;}
    
//    while(menu_tujuan == true){
//      ui_go(goal);
//      if(tombol() == "START") {
//        menu_tujuan = false;
//        ui_menu = false;
//      }
//      else if(tombol() == "0") {
//        menu_tujuan = false;
//      }
//    }
//========================= Accel =========================
//    lastAccelTime = millis();

    while(menu_tujuan == true){
    accel_motor(6000, 100);        //accel_motor(milidetik, pertambahan_kecepatan)
      
   
      if(tombol() == "START") {
        menu_tujuan = false;
        ui_menu = false;
      }
      else if(tombol() == "0") {
        menu_tujuan = false;
      }
    }
//========================= Accel =========================
    
  }
  
  while(true) {
    lcd.clear();
  }
  
}









void accel_motor(int berapa_milidetik, int kecepatan_accel){
  lastAccelTime = millis();
  while(accel_aktif){
    currentTime = millis();
    selisih_waktu = currentTime - lastAccelTime;
    count_down = berapa_milidetik - (currentTime - lastAccelTime);
    
    if (count_down < 0) {
      count_down = 0;
      lastAccelTime = millis();
      accel_aktif = false;
    }
    
    persen_acc = map(count_down, 0, berapa_milidetik, 0, 100);
    persen_accel = (float)persen_acc / 100;
    
    lcd.setCursor(0, 0);
    lcd.print(count_down);
    
    pwm_kiri = 127 + kecepatan_accel * persen_accel;
    pwm_kanan = 127 + kecepatan_accel * persen_accel;
    
    lcd.setCursor(1, 1);
    lcd.print(pwm_kiri);
    
    lcd.setCursor(10, 1);
    lcd.print(pwm_kanan);
    
    
    delay(100);  
    lcd.clear();
  }
}








////       unsigned long currentMillis = millis(); // grab current time
//       unsigned int currentMillis = millis(); // grab current time
//       
//       // check if "interval" time has passed (1000 milliseconds)
//       if ((unsigned long)(currentMillis - previousMillis) >= interval) {
//         previousMillis = millis();
//       }
//       int count_down = interval - (currentMillis - previousMillis);
//       
//       lcd.setCursor(0, 1);
//       lcd.print(interval);
//       
//       lcd.setCursor(9, 1);
//       lcd.print(count_down);
//       
//       lcd.setCursor(0, 0);
//       lcd.print(currentMillis);
//        
//       lcd.setCursor(9, 0);
//       lcd.print(previousMillis);
//       
//       delay(100);  
//       lcd.clear();  


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
