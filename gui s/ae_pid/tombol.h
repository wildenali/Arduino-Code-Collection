#define PinA 46 //keypad 8 kabel
#define PinB 47
#define PinC 48
#define PinD 49

#define Pin1 50  //keypad 8 kabel, lanjutan
#define Pin2 51
#define Pin3 52
#define Pin4 53

#define PinSTARTSTOP1 43
#define PinSTARTSTOP2 44 /*----LiDAR_HIGH----------------------*/
#define PinSTARTSTOP3 45 /*----Pause Setup Keypad_ON/OFF-------*/

bool buttonState1 = 0;  //tombol keypad 1,2,3,A
bool buttonState2 = 0;
bool buttonState3 = 0;
bool buttonStateA = 0;

bool buttonState4 = 0;  //tombol keypad 4,5,6,B
bool buttonState5 = 0;
bool buttonState6 = 0;
bool buttonStateB = 0;

bool buttonState7 = 0;  //tombol keypad 7,8,9,C
bool buttonState8 = 0;
bool buttonState9 = 0;
bool buttonStateC = 0;

bool buttonStateBINTANG = 0;  //tombol keypad BINTANG,0,PAGAR,D
bool buttonState0 = 0;
bool buttonStatePAGAR = 0;
bool buttonStateD = 0;

bool buttonStateSTARTSTOP2 = 0;
bool buttonStateSTARTSTOP3 = 0;


String tombolBarisPertama() {
  digitalWrite(PinA, LOW);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, HIGH);
  buttonState1 = digitalRead(Pin1);
  buttonState2 = digitalRead(Pin2);
  buttonState3 = digitalRead(Pin3);
  buttonStateA = digitalRead(Pin4);
  String ini_tombol;
  if(buttonState1 == LOW)  ini_tombol = "1";
  if(buttonState2 == LOW)  ini_tombol = "2";
  if(buttonState3 == LOW)  ini_tombol = "3";
  if(buttonStateA == LOW)  ini_tombol = "A";
  return ini_tombol;
}

String tombolBarisKedua() {
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, LOW);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, HIGH);
  buttonState4 = digitalRead(Pin1);
  buttonState5 = digitalRead(Pin2);
  buttonState6 = digitalRead(Pin3);
  buttonStateB = digitalRead(Pin4);
  String ini_tombol;
  if(buttonState4 == LOW)  ini_tombol = "4";
  if(buttonState5 == LOW)  ini_tombol = "5";
  if(buttonState6 == LOW)  ini_tombol = "6";
  if(buttonStateB == LOW)  ini_tombol = "B";
  return ini_tombol;
}

String tombolBarisKetiga() {
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, LOW);
  digitalWrite(PinD, HIGH);
  buttonState7 = digitalRead(Pin1);
  buttonState8 = digitalRead(Pin2);
  buttonState9 = digitalRead(Pin3);
  buttonStateC = digitalRead(Pin4);
  String ini_tombol;
  if(buttonState7 == LOW)  ini_tombol = "7";
  if(buttonState8 == LOW)  ini_tombol = "8";
  if(buttonState9 == LOW)  ini_tombol = "9";
  if(buttonStateC == LOW)  ini_tombol = "C";
  return ini_tombol;
}

String tombolBarisKeempat() {
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, LOW);
  buttonStateBINTANG = digitalRead(Pin1);
  buttonState0 = digitalRead(Pin2);
  buttonStatePAGAR = digitalRead(Pin3);
  buttonStateD = digitalRead(Pin4);
  String ini_tombol;
  if(buttonStateBINTANG == LOW)  ini_tombol = "OK";
  if(buttonState0 == LOW)        ini_tombol = "0";
  if(buttonStatePAGAR == LOW)    ini_tombol = "BACK";
  if(buttonStateD == LOW)        ini_tombol = "D";
  return ini_tombol;
}

String tombolSTARTSTOP() {
  buttonStateSTARTSTOP3 = digitalRead(PinSTARTSTOP3);
  String ini_tombol;
  if(buttonStateSTARTSTOP3 == LOW)  ini_tombol = "STARTSTOP3";
  return ini_tombol;
}

void tombol_setup(){
  pinMode(PinA, OUTPUT);
  pinMode(PinB, OUTPUT);
  pinMode(PinC, OUTPUT);
  pinMode(PinD, OUTPUT);
  
  pinMode(Pin1, INPUT_PULLUP);
  pinMode(Pin2, INPUT_PULLUP);
  pinMode(Pin3, INPUT_PULLUP);
  pinMode(Pin4, INPUT_PULLUP);

  pinMode(PinSTARTSTOP1, INPUT_PULLUP);
  pinMode(PinSTARTSTOP2, INPUT_PULLUP);
  pinMode(PinSTARTSTOP3, INPUT_PULLUP);
}

String tombol(){
  String hasil_tombol;
  if(tombolBarisPertama() != NULL)   hasil_tombol = tombolBarisPertama();
  if(tombolBarisKedua() != NULL)     hasil_tombol = tombolBarisKedua();
  if(tombolBarisKetiga() != NULL)    hasil_tombol = tombolBarisKetiga();
  if(tombolBarisKeempat() != NULL)   hasil_tombol = tombolBarisKeempat();
  if(tombolSTARTSTOP() != NULL)      hasil_tombol = tombolSTARTSTOP();
  return hasil_tombol;
}



