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

int pwm_kiri, pwm_kanan;

#include "tombol.h"           // ============ setup tombol keypad 4x4 =============
#include "accel_speed.h"      // ======================= accel_speed =======================
#include "user_interface.h"   // ======================= user interface =======================




/*================ Motor =======================================================*/
#define MotorKanan 6
#define MotorKiri 5

/*================ PID =========================================================*/
unsigned long lastTime;
double PID;
double errSum, lastErr;


int lastError;
int Error;

int16_t PIDLeft, PIDRight;
float gas = 150;



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
  user_interface_menu_utama();
  
  while(tombol() == "STARTSTOP3") {
    

//    lcd.clear();
//    ui_menu = true;
  }
  
}




void hitungPID()
{
/*-----------Cara Baca DATA satu satu si pixycam2-------*/
  if (pixy.line.numVectors) 
      {
        unsigned long now = millis();
        double timeChange = (double)(now - lastTime);
        
        Error = (int32_t)pixy.frameWidth/2 - pixy.line.vectors->m_x1;
        Serial.println(Error);
        
        errSum += (Error * timeChange);
        double dErr = (Error - lastErr) / timeChange;
        
        PID = kp * Error + ki * errSum + kd * dErr;
        
        lastErr = Error;                                                          
        lastTime = now;
      }
}

void eksekusimotor()
{
//  PIDLeft = gas - PID + (kecepatan_accel * persen_accel);
//  PIDRight = gas + PID + (kecepatan_accel * persen_accel);
  PIDLeft = gas - PID;
  PIDRight = gas + PID;
        
  if(PIDLeft > 255)           {PIDLeft = 255;}
  if(PIDLeft <= 127)          {PIDLeft = 127;}
  if(PIDRight > 255)          {PIDRight = 255;}
  if(PIDRight <= 127)         {PIDRight = 127;}

  analogWrite(MotorKiri, PIDLeft);
  analogWrite(MotorKanan, PIDRight);       
}












