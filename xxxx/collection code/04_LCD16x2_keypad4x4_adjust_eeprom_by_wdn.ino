#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#include <EEPROM.h>
// 50; /*---untuk alamat Speed (Rpm)----*/
// 51; /*---untuk alamat Kp-------------*/
// 52; /*---untuk alamat Kd-------------*/

//alamat ganti aja jadi seperti ini
int alamat_speed = 0;
int alamat_kp = 1;
int alamat_kd = 2;

int Rpm = 100;
int Kp = 1;
int Kd = 1000;
int Er = 10;

int resetRpm = 100;
int resetKp = 1;
int resetKd = 1000;

#define PinA 46
#define PinB 47
#define PinC 48
#define PinD 49

#define Pin1 50
#define Pin2 51
#define Pin3 52
#define Pin4 53

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonStateA = 0;

int buttonState4 = 0;
int buttonState5 = 0;
int buttonState6 = 0;
int buttonStateB = 0;

int buttonState7 = 0;
int buttonState8 = 0;
int buttonState9 = 0;
int buttonStateC = 0;

int buttonStateSTART = 0;
int buttonState0 = 0;
int buttonStateSTOP = 0;
int buttonStateD = 0;

void setup() {
  Serial.begin(9600);
  
  Wire.begin();
  Wire.beginTransmission(0x27);
  Wire.endTransmission();
  lcd.begin(16, 2); // initialize the lcd 

  pinMode(PinA, OUTPUT);
  pinMode(PinB, OUTPUT);
  pinMode(PinC, OUTPUT);
  pinMode(PinD, OUTPUT);
  
  pinMode(Pin1, INPUT_PULLUP);
  pinMode(Pin2, INPUT_PULLUP);
  pinMode(Pin3, INPUT_PULLUP);
  pinMode(Pin4, INPUT_PULLUP);

// baca disini
  Rpm=EEPROM.read(alamat_speed);
  Kp=EEPROM.read(alamat_kp);
  Kd=EEPROM.read(alamat_kd);


}

void loop() {

//  Rpm=EEPROM.read(50);
//  Kp=EEPROM.read(51);
//  Kd=EEPROM.read(52);  
  
  lcd.home();
  lcd.setBacklight(150);
  lcd.setCursor(0,0); 
  lcd.print("Rpm  Kp  Kd   Er");
  
  lcd.setCursor(0,1); 
  lcd.print(Rpm  );
  
  lcd.setCursor(5,1);
  lcd.print(Kp);  
  
  lcd.setCursor(8,1);
  lcd.print(Kd);  
    
  lcd.setCursor(14,1);
  lcd.print(Er);  

  digitalWrite(PinA, LOW);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, HIGH);
  buttonState1 = digitalRead(Pin1);
  buttonState2 = digitalRead(Pin2);
  buttonState3 = digitalRead(Pin3);
  buttonStateA = digitalRead(Pin4);
  
  if (buttonState1 == LOW)    {
	Rpm=Rpm+5;
	delay(50);
	lcd.setCursor(0,1);
	EEPROM.write(alamat_speed,Rpm);
   }
  if (buttonState2 == LOW)    {
	Kp++;
	delay(50);
	lcd.setCursor(5,1);
	EEPROM.write(alamat_kp,Kp);
  }
  if (buttonState3 == LOW)    {
	Kd++;
	delay(50);
	lcd.setCursor(9,1);
	EEPROM.write(alamat_kd,Kd);
	delay(50);
  }
  if (buttonStateA == LOW){
                    EEPROM.write(alamat_speed,resetRpm);
                    EEPROM.write(alamat_kp,resetKp);
                    EEPROM.write(alamat_kd,resetKd);
                    lcd.clear();
                    delay(50);
                    }     

  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, LOW);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, HIGH);
  buttonState4 = digitalRead(Pin1);
  buttonState5 = digitalRead(Pin2);
  buttonState6 = digitalRead(Pin3);
  buttonStateB = digitalRead(Pin4);
  if (buttonState4 == LOW)    {lcd.clear();lcd.setCursor(0,0); lcd.print("4");}
  if (buttonState5 == LOW)    {lcd.clear();lcd.setCursor(0,0); lcd.print("5");}
  if (buttonState6 == LOW)    {lcd.clear();lcd.setCursor(0,0); lcd.print("6");}
  if (buttonStateB == LOW)   {lcd.clear();lcd.setCursor(0,0); lcd.print("B");}

  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, LOW);
  digitalWrite(PinD, HIGH);
  buttonState7 = digitalRead(Pin1);
  buttonState8 = digitalRead(Pin2);
  buttonState9 = digitalRead(Pin3);
  buttonStateC = digitalRead(Pin4);
  if (buttonState7 == LOW)    {lcd.clear();lcd.setCursor(0,0); lcd.print("7");}
  if (buttonState8 == LOW)    {lcd.clear();lcd.setCursor(0,0); lcd.print("8");}
  if (buttonState9 == LOW)    {lcd.clear();lcd.setCursor(0,0); lcd.print("9");}
  if (buttonStateC == LOW)   {lcd.clear();lcd.setCursor(0,0); lcd.print("C");}

  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, LOW);
  buttonStateSTART = digitalRead(Pin1);
  buttonState0 = digitalRead(Pin2);
  buttonStateSTOP = digitalRead(Pin3);
  buttonStateD = digitalRead(Pin4);
  if (buttonStateSTART == LOW)    {lcd.clear();lcd.setCursor(0,0); lcd.print("START");}
  if (buttonState0     == LOW)    {lcd.clear();lcd.setCursor(0,0); lcd.print("0");}
  if (buttonStateSTOP  == LOW)    {lcd.clear();lcd.setCursor(0,0); lcd.print("STOP");}
  if (buttonStateD    == LOW)    {lcd.clear();lcd.setCursor(0,0); lcd.print("D");}  
}
