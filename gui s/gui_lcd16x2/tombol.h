#define PinA 46 //keypad 8 kabel
#define PinB 47
#define PinC 48
#define PinD 49

#define Pin1 50  //keypad 8 kabel, lanjutan
#define Pin2 51
#define Pin3 52
#define Pin4 53

#define STARTSTOP1 43
#define STARTSTOP2 44 /*---tombol PAUSE----*/
#define STARTSTOP3 45

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

String tombolBarisPertama() {
  digitalWrite(PinA, LOW);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, HIGH);
  buttonState1 = digitalRead(Pin1);
  buttonState2 = digitalRead(Pin2);
  buttonState3 = digitalRead(Pin3);
  buttonStateF1 = digitalRead(Pin4);
  String ini_tombol;
  if(buttonState1 == LOW)  ini_tombol = "1";
  if(buttonState2 == LOW)  ini_tombol = "2";
  if(buttonState3 == LOW)  ini_tombol = "3";
  if(buttonStateF1 == LOW) ini_tombol = "F1";
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
  buttonStateF2 = digitalRead(Pin4);
  String ini_tombol;
  if(buttonState4 == LOW)  ini_tombol = "4";
  if(buttonState5 == LOW)  ini_tombol = "5";
  if(buttonState6 == LOW)  ini_tombol = "6";
  if(buttonStateF2 == LOW) ini_tombol = "F2";
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
  buttonStateF3 = digitalRead(Pin4);
  String ini_tombol;
  if(buttonState7 == LOW)  ini_tombol = "7";
  if(buttonState8 == LOW)  ini_tombol = "8";
  if(buttonState9 == LOW)  ini_tombol = "9";
  if(buttonStateF3 == LOW) ini_tombol = "F3";
  return ini_tombol;
}

String tombolBarisKeempat() {
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, LOW);
  buttonStateSTART = digitalRead(Pin1);
  buttonState0 = digitalRead(Pin2);
  buttonStateSTOP = digitalRead(Pin3);
  buttonStateF4 = digitalRead(Pin4);
  String ini_tombol;
  if(buttonStateSTART == LOW)  ini_tombol = "START";
  if(buttonState0 == LOW)      ini_tombol = "0";
  if(buttonStateSTOP == LOW)   ini_tombol = "STOP";
  if(buttonStateF4 == LOW)     ini_tombol = "F4";
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

  pinMode(STARTSTOP1, INPUT);
  pinMode(STARTSTOP2, INPUT);
  pinMode(STARTSTOP3, INPUT);
}

String tombol(){
  String hasil_tombol;
  if(tombolBarisPertama() != NULL)   hasil_tombol = tombolBarisPertama();
  if(tombolBarisKedua() != NULL)     hasil_tombol = tombolBarisKedua();
  if(tombolBarisKetiga() != NULL)    hasil_tombol = tombolBarisKetiga();
  if(tombolBarisKeempat() != NULL)   hasil_tombol = tombolBarisKeempat();
  return hasil_tombol;
}



