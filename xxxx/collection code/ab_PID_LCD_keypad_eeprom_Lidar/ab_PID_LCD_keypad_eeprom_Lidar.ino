/*================ Pixy ========================================================*/
#include <Pixy2.h>
Pixy2 pixy;

/*================ Motor =======================================================*/
#define MotorKanan 6
#define MotorKiri 5

/*================ view LCD ====================================================*/
#include <Wire.h> 
#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int screenWidth = 16;
int screenHeight = 2;

String line1 = "  AGV WORKING "; // Static line
String line2 = "Clean My Path, Please"; // Scrolling line

/*----just some reference flags------*/
int stringStart, stringStop = 0;
int scrollCursor = screenWidth;

/*================ data EEPROM =================================================*/
#include <EEPROM.h>
// 50; /*---untuk alamat Speed (gas)----*/
// 51; /*---untuk alamat kp-------------*/
// 52; /*---untuk alamat kd-------------*/

/*================ PID =========================================================*/
unsigned long lastTime;
double PID;
double errSum, lastErr;

double kp = 1;       
double ki = 0;
double kd = 10;

int lastError;
int Error;

int16_t PIDLeft, PIDRight;
float gas = 197;

/*================ Tombol Pause, sensor, dll ==================================*/
#define STARTSTOP2 44 /*----LiDAR_HIGH----------------------*/
#define STARTSTOP3 45 /*----Pause Setup Keypad_ON/OFF-------*/

/*================ Pin Keypad =================================================*/
#define PinA 46
#define PinB 47
#define PinC 48
#define PinD 49

#define Pin1 50
#define Pin2 51
#define Pin3 52
#define Pin4 53

//int buttonState1 = 0;
//int buttonState2 = 0;
//int buttonState3 = 0;
//int buttonStateA = 0;
//
//int buttonState4 = 0;
//int buttonState5 = 0;
//int buttonState6 = 0;
//int buttonStateB = 0;
//
//int buttonState7 = 0;
//int buttonState8 = 0;
//int buttonState9 = 0;
//int buttonStateC = 0;
//
//int buttonStateSTART = 0;
//int buttonState0 = 0;
//int buttonStateSTOP = 0;
//int buttonStateD = 0;
//
//void tombolBarisPertama() {
//  digitalWrite(PinA, LOW);
//  digitalWrite(PinB, HIGH);
//  digitalWrite(PinC, HIGH);
//  digitalWrite(PinD, HIGH);
//  buttonState1 = digitalRead(Pin1);
//  buttonState2 = digitalRead(Pin2);
//  buttonState3 = digitalRead(Pin3);
//  buttonStateA = digitalRead(Pin4);  
//}
//
//void tombolBarisKedua() {
//  digitalWrite(PinA, HIGH);
//  digitalWrite(PinB, LOW);
//  digitalWrite(PinC, HIGH);
//  digitalWrite(PinD, HIGH);
//  buttonState4 = digitalRead(Pin1);
//  buttonState5 = digitalRead(Pin2);
//  buttonState6 = digitalRead(Pin3);
//  buttonStateB = digitalRead(Pin4);
//}
//
//void tombolBarisKetiga() {
//  digitalWrite(PinA, HIGH);
//  digitalWrite(PinB, HIGH);
//  digitalWrite(PinC, LOW);
//  digitalWrite(PinD, HIGH);
//  buttonState7 = digitalRead(Pin1);
//  buttonState8 = digitalRead(Pin2);
//  buttonState9 = digitalRead(Pin3);
//  buttonStateC = digitalRead(Pin4);
//}
//
//void tombolBarisKeempat() {
//  digitalWrite(PinA, HIGH);
//  digitalWrite(PinB, HIGH);
//  digitalWrite(PinC, HIGH);
//  digitalWrite(PinD, LOW);
//  buttonStateSTART = digitalRead(Pin1);
//  buttonState0 = digitalRead(Pin2);
//  buttonStateSTOP = digitalRead(Pin3);
//  buttonStateD = digitalRead(Pin4);
//}
void setup()
{
/*============== baca Pixy ====================================================*/
  Serial1.begin(19200);
  Serial.begin(115200);
  Serial.print("Starting...\n");

  pixy.init();
  Serial.println(pixy.changeProg("line"));
  pixy.setLamp(1,1);

/*============== baca Motor ===================================================*/
  pinMode(MotorKiri, OUTPUT);
  pinMode(MotorKanan, OUTPUT);
  
        constrain(MotorKiri,127,gas);
        constrain(MotorKanan,127,gas);  
        
        analogWrite(MotorKiri, gas);
        analogWrite(MotorKanan, gas);   

/*============== view LCD ====================================================*/
  Wire.begin();
  Wire.beginTransmission(0x27);
  Wire.endTransmission();
  lcd.begin(16, 2); // initialize the lcd
  lcd.home();
  lcd.setBacklight(180);
  
/*============== keypad ======================================================*/
//  pinMode(PinA, OUTPUT);
//  pinMode(PinB, OUTPUT);
//  pinMode(PinC, OUTPUT);
//  pinMode(PinD, OUTPUT);
//  
//  pinMode(Pin1, INPUT_PULLUP);
//  pinMode(Pin2, INPUT_PULLUP);
//  pinMode(Pin3, INPUT_PULLUP);
//  pinMode(Pin4, INPUT_PULLUP);

/*============== Pause Button ================================================*/
  pinMode(STARTSTOP2, INPUT_PULLUP);
  pinMode(STARTSTOP3, INPUT_PULLUP);
             
}

void loop()
{
  int8_t i;
  char buf[128];
  pixy.line.getMainFeatures();

  if    (digitalRead(STARTSTOP3) == LOW)/*-----Pin 45-----------*/
        {
        menuLCD(); 
        PIDLeft = 127;
        PIDRight = 127;
        
        Serial.print("Kiwo ");
        Serial.print(PIDLeft);    Serial.print("\t");
        Serial.print("Tengen ");
        Serial.print(PIDRight);   Serial.print("\n");
        delay(300);
        }
  else if(digitalRead(STARTSTOP2) == HIGH)/*-----Pin 44-----------*/
        {        
        PIDLeft = 127;
        PIDRight = 127;
        
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("Ada Halangan...");
        
        Serial.print("Left ");
        Serial.print(PIDLeft);    Serial.print("\t");
        Serial.print("Right ");
        Serial.print(PIDRight);   Serial.print("\n");
        delay(300);
        }        
  else  {  
        hitungPID();
        eksekusimotor();
        awalLcd();
   
//        analogWrite(MotorKiri, PIDLeft);
//        analogWrite(MotorKanan, PIDRight); 
//        constrain(PIDLeft,127,gas);
//        constrain(PIDRight,127,gas);
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
        PIDLeft = gas - PID;
        PIDRight = gas + PID;
    
        if(PIDLeft > gas)           {PIDLeft = gas;}
        if(PIDLeft <= 127)          {PIDLeft = 127;}
        if(PIDRight > gas)          {PIDRight = gas;}
        if(PIDRight <= 127)         {PIDRight = 127;}
    
        constrain(PIDLeft,127,gas);
        constrain(PIDRight,127,gas);
    
        analogWrite(MotorKiri, PIDLeft);
        analogWrite(MotorKanan, PIDRight);       

        Serial.print("Kiri ");
        Serial.print(PIDLeft);    Serial.print("\t");
        Serial.print("Kanan ");
        Serial.print(PIDRight);   Serial.print("\n");

}
/*---------------Home (tombol START ganti label HOME)------------------*/
void awalLcd()
{
        lcd.setCursor(0, 0);
        lcd.print(line1);
  
        lcd.setCursor(scrollCursor, 1);
        lcd.print(line2.substring(stringStart,stringStop));
        delay(500);  
        lcd.clear();
  
        if(stringStart == 0 && scrollCursor > 0){
                scrollCursor--;
                stringStop++;
                } 
        else if (stringStart == stringStop){
                stringStart = stringStop = 0;
                scrollCursor = screenWidth;
                } 
        else if (stringStop == line2.length() && scrollCursor == 0) {
                stringStart++;
                } 
        else {
                stringStart++;
                stringStop++;
                }  
}
/*---------------Menu (tombol STOP ganti label SETUP)-------------------*/
void menuLCD()
{
      int Gas = gas;
      int Kp = kp;
      int Kd = kd*100;

      int resetgas = 197;
      int resetkp = 1;
      int resetkd = 10; /*--Kd bisa di disimpan & direset jika nilai dibawah 255---*/ 

      gas =EEPROM.read(50);
      kp  =EEPROM.read(51);
      kd  =EEPROM.read(52); /*----untuk nilai Kd-----*/   
              
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Rpm  Kp  Kd   Er");
   
      lcd.setCursor(0,1); 
      lcd.print(Gas  );
  
      lcd.setCursor(5,1);
      lcd.print(Kp);   
  
      lcd.setCursor(8,1);
      lcd.print(Kd);
      delay(50);  
    
      lcd.setCursor(14,1);
      lcd.print(Error); 
      
//  tombolBarisPertama(); 
//      if (buttonState1 == LOW)    {gas=gas-5;  delay(20);lcd.setCursor(0,1);}EEPROM.write(50,gas) ;delay(20); /*---adjust gas--*/
//      if (buttonState2 == LOW)    {kp--;       delay(20);lcd.setCursor(5,1);}EEPROM.write(51,kp)  ;delay(20);      /*---adjust kp--*/
//      if (buttonState3 == LOW)    {kd--;     delay(20);lcd.setCursor(8,1);}EEPROM.write(52,kd);delay(20); /*---adjust kd--*/
//      if (buttonStateA == LOW)    {EEPROM.write(50,resetgas);EEPROM.write(51,resetkp);EEPROM.write(52,resetkd);lcd.clear();delay(50);}     
//
//  tombolBarisKedua();
//      if (buttonState4 == LOW)    {gas=gas+5;  delay(20);lcd.setCursor(0,1);}EEPROM.write(50,gas) ;delay(20); /*---adjust gas++ ---*/
//      if (buttonState5 == LOW)    {kp++;       delay(20);lcd.setCursor(5,1);}EEPROM.write(51,kp)  ;delay(20);      /*---adjust Kp--*/
//      if (buttonState6 == LOW)    {kd++;     delay(20);lcd.setCursor(8,1);}EEPROM.write(52,kd);delay(20); /*---adjust Kd--*/
//
//      if (buttonStateA == LOW)    {EEPROM.write(50,resetgas);EEPROM.write(51,resetkp);EEPROM.write(52,resetkd);lcd.clear();delay(50);}     
        
}


