/* https://github.com/CytronTechnologies/Arduino-LSA08/blob/master/LSA08PID/LSA08PID.ino */

#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int positionVal;
int sensorgaris;
int sensorgaris_pinggir;
int Error;
int errorsensorgaris;
int posisisensorgaris;

int station;
int simpanganke = 1;
int lastbuttonStateSTOP = 0;
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;

#define sensor1 A0 
#define sensor2 A1
#define sensor11 A10 
#define sensor12 A11

int s1, s2, s11, s12;
int simpangan;

unsigned long lastTime;
double Input, PID;
double Setpoint = 0;
double errSum, lastErr;

int kp = 5;        
double ki = 0;
int kd = 7500;

int16_t PIDLeft, PIDRight;
int gas = 100;

const byte rx = 0;    // Defining pin 0 as Rx
const byte tx = 1;    // Defining pin 1 as Tx
const byte serialEn = 2;    // Connect UART output enable of LSA08 to pin 2
const byte junctionPulse = 4;   // Connect JPULSE of LSA08 to pin 4

const byte MotorKiri = 12;   // Connect PWM1 of motor driver to pin 12
const byte MotorKanan = 13;   // Connect PWM2 of motor driver to pin 13

#define PinA 46 //keypad 8 kabel
#define PinB 47
#define PinC 48
#define PinD 49

#define Pin1 50  //keypad 8 kabel, lanjutan
#define Pin2 51
#define Pin3 52
#define Pin4 53

#define STARTSTOP2 44

int buttonState1 = 0;  //tombol keypad 1,2,3,F1
int buttonState2 = 0;
int buttonState3 = 0;
int buttonStateF1 = 0;

int buttonState4 = 0;  //tombol keypad 4,5,6,F2
int buttonState5 = 0;
int buttonState6 = 0;
int buttonStateF2 = 0;

int buttonState7 = 0;  //tombol keypad 7,8,9,F3
int buttonState8 = 0;
int buttonState9 = 0;
int buttonStateF3 = 0;

int buttonStateSTART = 0;  //tombol keypad START,0,STOP,F4
int buttonState0 = 0;
int buttonStateSTOP = 0;
int buttonStateF4 = 0;

void setup() 
  {
  Serial.begin(9600);
  Serial1.begin(19200);

  pinMode(sensor1, INPUT);  
  pinMode(sensor2, INPUT);
  pinMode(sensor11, INPUT);
  pinMode(sensor12, INPUT);

  pinMode(PinA, OUTPUT);
  pinMode(PinB, OUTPUT);
  pinMode(PinC, OUTPUT);
  pinMode(PinD, OUTPUT);
  
  pinMode(Pin1, INPUT_PULLUP);
  pinMode(Pin2, INPUT_PULLUP);
  pinMode(Pin3, INPUT_PULLUP);
  pinMode(Pin4, INPUT_PULLUP);

  pinMode(STARTSTOP2, INPUT);
  
  pinMode(serialEn,OUTPUT);   // Setting serialEn as digital output pin
  pinMode(junctionPulse,INPUT);   // Setting junctionPulse as digital input pin

  // Setting pin 10 - 13 as digital output pin
      for(byte i=10;i<=13;i++) 
        {
        pinMode(i,OUTPUT);
        }

  // Setting initial condition of serialEn pin to HIGH
      digitalWrite(serialEn,HIGH);

  // Setting the initial condition of motors
  // make sure both PWM pins are LOW
      digitalWrite(MotorKiri,LOW);
      digitalWrite(MotorKanan,LOW);

  Wire.begin();
  Wire.beginTransmission(0x27);
  Wire.endTransmission();

  lcd.begin(16, 2); // initialize the lcd
  lcd.setBacklight(255);

}

void loop ()
{
  SettingNilaiError();   
  belokcepat();
  
  if  (digitalRead(STARTSTOP2) == LOW) {
      digitalWrite(PinA, LOW);
      digitalWrite(PinB, HIGH);
      digitalWrite(PinC, HIGH);
      digitalWrite(PinD, HIGH);
      buttonState1 = digitalRead(Pin1);
      buttonState2 = digitalRead(Pin2);
      buttonState3 = digitalRead(Pin3);
      buttonStateF1 = digitalRead(Pin4);
      
          if (buttonStateF1 == LOW)   {  
              delay(50);
              gas--;
              }
          if (buttonState1 == LOW)   {  
              delay(50);
              kd=kd-100;
              }
              
      digitalWrite(PinA, HIGH);
      digitalWrite(PinB, LOW);
      digitalWrite(PinC, HIGH);
      digitalWrite(PinD, HIGH);
      buttonState4 = digitalRead(Pin1);
      buttonState5 = digitalRead(Pin2);
      buttonState6 = digitalRead(Pin3);
      buttonStateF2 = digitalRead(Pin4);
      
          if (buttonStateF2 == LOW)   {   
              delay(50);
              gas++;
              }
          if (buttonState4 == LOW)   {  
              delay(50);
              kd=kd+100;
              }
              
      digitalWrite(PinA, HIGH);
      digitalWrite(PinB, HIGH);
      digitalWrite(PinC, LOW);
      digitalWrite(PinD, HIGH);
      buttonState7 = digitalRead(Pin1);
      buttonState8 = digitalRead(Pin2);
      buttonState9 = digitalRead(Pin3);
      buttonStateF3 = digitalRead(Pin4);
      
          if (buttonStateF3 == LOW)   {  
              delay(50);
              kp--;
              }
      digitalWrite(PinA, HIGH);
      digitalWrite(PinB, HIGH);
      digitalWrite(PinC, HIGH);
      digitalWrite(PinD, LOW);
      buttonStateSTART = digitalRead(Pin1);
      buttonState0 = digitalRead(Pin2);
      buttonStateSTOP = digitalRead(Pin3);
      buttonStateF4 = digitalRead(Pin4);
      
          if (buttonStateF4 == LOW)   {  
              delay(50);
              kp++;
              }
    PIDRight = 0;
    PIDLeft = 0;
    Serial1.write((uint8_t *) &PIDRight, sizeof(PIDRight));
    Serial1.write((uint8_t *) &PIDLeft, sizeof(PIDLeft));
    }

  else {        
        bacastation();
        prog_1();
        hitungPID();
        eksekusikemotor ();
        } 
        
   lcd.home();
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("SPEED ");
   lcd.print(gas);
   delay(50);

//   lcd.setCursor(10, 0);
//   lcd.print("rpm");
//   delay(50);
 
   lcd.setCursor(0, 1);
   lcd.print("KP ");
   lcd.print(kp);
   delay(20);

   lcd.setCursor(8, 1);
   lcd.print("KD ");
   lcd.print(kd);
   delay(20);
}

void SettingNilaiError() 
{
  digitalWrite(serialEn,LOW);   // Set serialEN to LOW to request UART data
  while(Serial.available() <= 0);   // Wait for data to be available
  positionVal = Serial.read();    // "int" dihilangkan, Read incoming data and store in variable positionVal
  digitalWrite(serialEn,HIGH);    // Stop requesting for UART data

//  Serial.print(positionVal-35);
//  Serial.print("\t");
//  Serial.println(digitalRead(junctionPulse));
//  delay (70);
 

  if     (positionVal ==   0)   {errorsensorgaris =  7;}
  else if(positionVal ==   5)   {errorsensorgaris =  6;}
  else if(positionVal ==  10)   {errorsensorgaris =  5;}
  else if(positionVal ==  15)   {errorsensorgaris =  4;}
  else if(positionVal ==  20)   {errorsensorgaris =  3;}
  else if(positionVal ==  25)   {errorsensorgaris =  2;}
  else if(positionVal ==  30)   {errorsensorgaris =  1;}
  else if(positionVal ==  35)   {errorsensorgaris =  0;}
  else if(positionVal ==  40)   {errorsensorgaris = -1;}
  else if(positionVal ==  45)   {errorsensorgaris = -2;}
  else if(positionVal ==  50)   {errorsensorgaris = -3;}
  else if(positionVal ==  55)   {errorsensorgaris = -4;}
  else if(positionVal ==  60)   {errorsensorgaris = -5;}
  else if(positionVal ==  65)   {errorsensorgaris = -6;}
  else if(positionVal ==  70)   {errorsensorgaris = -7;}
    
//  Serial.print("error ");
  Serial.print(errorsensorgaris);    Serial.print("\t");
  
//  Serial.print("Val ");
  Serial.print(positionVal);   Serial.print("\n");
  delay(100);
}

void hitungPID() {
    unsigned long now = millis();
    double timeChange = (double)(now - lastTime);
    Input = errorsensorgaris;
    double Error = Setpoint - Input;
    errSum += (Error * timeChange);
    double dErr = (Error - lastErr) / timeChange;
    PID = kp * Error + ki * errSum + kd * dErr;        
    lastErr = Error;                                                          
    lastTime = now;

//    Serial.println(PID);
}

void eksekusikemotor ()
{
    PIDLeft = gas - PID;
    PIDRight = gas + PID;
    
    if(PIDLeft > gas)           {PIDLeft = gas;}
    if(PIDLeft <= 0)            {PIDLeft = 0;}
    if(PIDRight > gas)          {PIDRight = gas;}
    if(PIDRight <= 0)           {PIDRight = 0;}

                                
    constrain(PIDLeft,0,gas);
    constrain(PIDRight,0,gas);
    
    analogWrite(MotorKiri, PIDLeft);
    analogWrite(MotorKanan, PIDRight);
   
   
    Serial.print("Kiri ");
    Serial.print(PIDLeft);    Serial.print("\t");
    Serial.print("Kanan ");
    Serial.print(PIDRight);   Serial.print("\n");
    delay(100);
    Serial1.write((uint8_t *) &PIDRight, sizeof(PIDRight));
    Serial1.write((uint8_t *) &PIDLeft, sizeof(PIDLeft));
    delay(300);  
}

void belokcepat()  /*------------Tes Berhenti---Hasil OK----Tikung bisa, tapi blom bisa balik, muter terus------*/
{
   SettingNilaiError();

   lcd.setCursor(10, 0);
   lcd.print("V ");
   lcd.print(positionVal);
   delay(50);
    
    if (positionVal ==  255)
    {
     berhenti:
         PIDLeft = 0;
         PIDRight = 0;
         
         Serial1.write((uint8_t *) &PIDRight, sizeof(PIDRight));
         Serial1.write((uint8_t *) &PIDLeft, sizeof(PIDLeft));
         delay(1500);

     goto berhenti;
    }

void KonversiDecimalkeBinner() 
{
  
  s1  = 1 * digitalRead(sensor1);  
  s2  = 2 * digitalRead(sensor2);
  s11 = 4 * digitalRead(sensor11);
  s12 = 8 * digitalRead(sensor12);
  
  sensorgaris_pinggir = s12 + s11 + s2 + s1;
} 

void bacastation() {
  if(sensorgaris_pinggir == 0b1111 || 
     sensorgaris_pinggir == 0b1001 ||
     sensorgaris_pinggir == 0b0110 ||
     sensorgaris_pinggir == 0b1101 ||
     sensorgaris_pinggir == 0b1011 ||
     sensorgaris_pinggir == 0b0101 ||
     sensorgaris_pinggir == 0b1010 ) 
     {
     station = 1; 
     }
  else {
     station = 0;
     }
  
  buttonState = station;
  if (buttonState != lastButtonState) 
      {
      if (buttonState == HIGH) 
          {
          buttonPushCounter++;
          } 
      else{
          }
          delay(50);
      }
   lastButtonState = buttonState;
}

void prog_1()
{
  while (station == 1) 
    {
      PIDRight = 0;
      PIDLeft = 0;
      Serial1.write((uint8_t *) &PIDRight, sizeof(PIDRight));
      Serial1.write((uint8_t *) &PIDLeft, sizeof(PIDLeft));
      delay(15000);
    
    majuduludong:
      SettingNilaiError();
      hitungPID();
      eksekusikemotor ();
      belokcepat();
      bacastation();
      
    if (station == 0) 
          {
          goto keluar;
          }
    goto majuduludong;
    }
    keluar:;                                                                                                                                                
}
