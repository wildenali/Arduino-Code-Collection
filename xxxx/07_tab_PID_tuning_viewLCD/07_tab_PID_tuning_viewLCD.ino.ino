/*================ view LCD ====================================================*/
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

/*================ Pixy ========================================================*/
#include <Pixy2.h>
Pixy2 pixy;

/*================ Motor =======================================================*/
#define MotorKanan 6
#define MotorKiri 5

float gas = 187;

/*================ Pin Keypad =================================================*/
#define PinA 46
#define PinB 47
#define PinC 48
#define PinD 49

#define Pin1 50
#define Pin2 51
#define Pin3 52
#define Pin4 53

void setup() {
  Serial.begin(9600);
/*============== baca Pixy ====================================================*/
  Serial1.begin(19200);
  Serial.begin(115200);
  Serial.print("Starting...\n");

  pixy.init();
  Serial.println(pixy.changeProg("line"));
  pixy.setLamp(1,1);

/*============== baca Motor ====================================================*/
  pinMode(MotorKiri, OUTPUT);
  pinMode(MotorKanan, OUTPUT);
  // supaya pas nyala tidak muter ban nya
  analogWrite(MotorKiri, 127);
  analogWrite(MotorKanan, 127);

/*============== view LCD =====================================================*/
//  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(0x27);
  Wire.endTransmission();
  lcd.begin(16, 2); // initialize the lcd
  lcd.setBacklight(180);

/*============== keypad ======================================================*/
  pinMode(PinA, OUTPUT);
  pinMode(PinB, OUTPUT);
  pinMode(PinC, OUTPUT);
  pinMode(PinD, OUTPUT);

  pinMode(Pin1, INPUT_PULLUP);
  pinMode(Pin2, INPUT_PULLUP);
  pinMode(Pin3, INPUT_PULLUP);
  pinMode(Pin4, INPUT_PULLUP);
}

void loop() {
/*============== baca Pixy ====================================================*/
  int8_t i;
  char buf[128];
  pixy.line.getMainFeatures();

  hitungPID();
  eksekusimotor();
  viewLCD();

}
