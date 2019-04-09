#include <Pixy2.h>

#define MotorKanan 13
#define MotorKiri 12

Pixy2 pixy;

#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display


unsigned long lastTime;
double PID;
double errSum, lastErr;

double kp = 1.6;       /*speed150, kp1, kd1500_troli kosong*/
double ki = 0;         /*speed165, kp1.5, kd1900_troli isi 25 kantong (300pasang)*/
double kd = 2000;      /*speed180, kp1.5, kd2100_troli kosong*/
                       /*speed180, kp1.2, kd2300_troli kosong*/
int lastError;
int Error;

int16_t PIDLeft, PIDRight;
float gas = 180;

//#define PinA 46 //keypad 8 kabel
//#define PinB 47
//#define PinC 48
//#define PinD 49
//
//#define Pin1 50  //keypad 8 kabel, lanjutan
//#define Pin2 51
//#define Pin3 52
//#define Pin4 53
//
#define STARTSTOP1 43
#define STARTSTOP2 44 /*---tombol PAUSE----*/
#define STARTSTOP3 45
//
//int buttonState1 = 0;  //tombol keypad 1,2,3,F1
//int buttonState2 = 0;
//int buttonState3 = 0;
//int buttonStateF1 = 0;
//
//int buttonState4 = 0;  //tombol keypad 4,5,6,F2
//int buttonState5 = 0;
//int buttonState6 = 0;
//int buttonStateF2 = 0;
//
//int buttonState7 = 0;  //tombol keypad 7,8,9,F3
//int buttonState8 = 0;
//int buttonState9 = 0;
//int buttonStateF3 = 0;
//
//int buttonStateSTART = 0;  //tombol keypad START,0,STOP,F4
//int buttonState0 = 0;
//int buttonStateSTOP = 0;
//int buttonStateF4 = 0;

#define sensor1 A0 
#define sensor2 A1
#define sensor11 A10 
#define sensor12 A11

int s1, s2, s11, s12;
int sensorgaris_pinggir;
int station;
int simpanganke = 1;
int lastbuttonStateSTOP = 0;
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;


void setup()
{
  Serial1.begin(19200);
  Serial.begin(115200);
  Serial.print("Starting...\n");

  pinMode(MotorKiri, OUTPUT);
  pinMode(MotorKanan, OUTPUT);

  pinMode(sensor1, INPUT);  
  pinMode(sensor2, INPUT);
  pinMode(sensor11, INPUT);
  pinMode(sensor12, INPUT);
  
  pixy.init();
  Serial.println(pixy.changeProg("line"));
  pixy.setLamp(1,1);

//  pinMode(PinA, OUTPUT);
//  pinMode(PinB, OUTPUT);
//  pinMode(PinC, OUTPUT);
//  pinMode(PinD, OUTPUT);
//  
//  pinMode(Pin1, INPUT_PULLUP);
//  pinMode(Pin2, INPUT_PULLUP);
//  pinMode(Pin3, INPUT_PULLUP);
//  pinMode(Pin4, INPUT_PULLUP);

  pinMode(STARTSTOP1, INPUT);
  pinMode(STARTSTOP2, INPUT);
  pinMode(STARTSTOP3, INPUT);

  Wire.begin();
  Wire.beginTransmission(0x27);
  Wire.endTransmission();

  lcd.begin(16, 2); // initialize the lcd
  lcd.setBacklight(255);
  
}

void loop()
{
  int8_t i;
  char buf[128];
 
  pixy.line.getMainFeatures();
  
//  if  (digitalRead(STARTSTOP2) == LOW) {
//      digitalWrite(PinA, LOW);
//      digitalWrite(PinB, HIGH);
//      digitalWrite(PinC, HIGH);
//      digitalWrite(PinD, HIGH);
//      buttonState1 = digitalRead(Pin1);
//      buttonState2 = digitalRead(Pin2);
//      buttonState3 = digitalRead(Pin3);
//      buttonStateF1 = digitalRead(Pin4);
//      
//          if (buttonStateF1 == LOW)   {  
//              delay(50);
//              gas=gas-5;
//              }
//          if (buttonState1 == LOW)   {  
//              delay(50);
//              kd=kd-100;
//              }
//              
//      digitalWrite(PinA, HIGH);
//      digitalWrite(PinB, LOW);
//      digitalWrite(PinC, HIGH);
//      digitalWrite(PinD, HIGH);
//      buttonState4 = digitalRead(Pin1);
//      buttonState5 = digitalRead(Pin2);
//      buttonState6 = digitalRead(Pin3);
//      buttonStateF2 = digitalRead(Pin4);
//      
//          if (buttonStateF2 == LOW)   {   
//              delay(50);
//              gas=gas+5;
//              }
//          if (buttonState4 == LOW)   {  
//              delay(50);
//              kd=kd+100;
//              }
//              
//      digitalWrite(PinA, HIGH);
//      digitalWrite(PinB, HIGH);
//      digitalWrite(PinC, LOW);
//      digitalWrite(PinD, HIGH);
//      buttonState7 = digitalRead(Pin1);
//      buttonState8 = digitalRead(Pin2);
//      buttonState9 = digitalRead(Pin3);
//      buttonStateF3 = digitalRead(Pin4);
//      
//          if (buttonStateF3 == LOW)   {  
//              delay(50);
//              kp--;
//              }
//      digitalWrite(PinA, HIGH);
//      digitalWrite(PinB, HIGH);
//      digitalWrite(PinC, HIGH);
//      digitalWrite(PinD, LOW);
//      buttonStateSTART = digitalRead(Pin1);
//      buttonState0 = digitalRead(Pin2);
//      buttonStateSTOP = digitalRead(Pin3);
//      buttonStateF4 = digitalRead(Pin4);
//      
//          if (buttonStateF4 == LOW)   {  
//              delay(50);
//              kp++;
//              }
//    PIDRight = 0;
//    PIDLeft = 0;
//    Serial1.write((uint8_t *) &PIDRight, sizeof(PIDRight));
//    Serial1.write((uint8_t *) &PIDLeft, sizeof(PIDLeft));
//    }
//    
//else {  
  if 
      (digitalRead(STARTSTOP2) == LOW)
      {
      PIDRight = 0;
      PIDLeft = 0;
      Serial1.write((uint8_t *) &PIDRight, sizeof(PIDRight));
      Serial1.write((uint8_t *) &PIDLeft, sizeof(PIDLeft));
      }
  else if 
      (digitalRead(STARTSTOP3) == LOW)
      {
      PIDRight = 0;
      PIDLeft = 0;
      Serial1.write((uint8_t *) &PIDRight, sizeof(PIDRight));
      Serial1.write((uint8_t *) &PIDLeft, sizeof(PIDLeft));
      }

else {    
   hitungPID();
   eksekusimotor();
   bacastation();
   prog_1();
}  

//}
//
   lcd.home();
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("SPEED ");
   lcd.print(gas);
   delay(50);

   lcd.setCursor(0, 1);
   lcd.print("KP ");
   lcd.print(kp);
   delay(20);

   lcd.setCursor(8, 1);
   lcd.print("KD ");
   lcd.print(kd);
   delay(20);
   
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
        

        Serial1.write((uint8_t *) &PIDRight, sizeof(PIDRight));
        Serial1.write((uint8_t *) &PIDLeft, sizeof(PIDLeft));
        delay(300);
    
      
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
    KonversiDecimalkeBinner();
    
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
      hitungPID();
      eksekusimotor ();        
      bacastation();
      
    if (station == 0) 
          {
          goto keluar;
          }
    goto majuduludong;
    }
    keluar:;                                                                                                                                                
}

