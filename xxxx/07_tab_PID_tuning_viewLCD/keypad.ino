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

void tombolBarisPertama() {
  digitalWrite(PinA, LOW);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, HIGH);
  buttonState1 = digitalRead(Pin1);
  buttonState2 = digitalRead(Pin2);
  buttonState3 = digitalRead(Pin3);
  buttonStateA = digitalRead(Pin4);  
}

void tombolBarisKedua() {
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, LOW);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, HIGH);
  buttonState4 = digitalRead(Pin1);
  buttonState5 = digitalRead(Pin2);
  buttonState6 = digitalRead(Pin3);
  buttonStateB = digitalRead(Pin4);
}

void tombolBarisKetiga() {
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, LOW);
  digitalWrite(PinD, HIGH);
  buttonState7 = digitalRead(Pin1);
  buttonState8 = digitalRead(Pin2);
  buttonState9 = digitalRead(Pin3);
  buttonStateC = digitalRead(Pin4);
}

void tombolBarisKeempat() {
  digitalWrite(PinA, HIGH);
  digitalWrite(PinB, HIGH);
  digitalWrite(PinC, HIGH);
  digitalWrite(PinD, LOW);
  buttonStateSTART = digitalRead(Pin1);
  buttonState0 = digitalRead(Pin2);
  buttonStateSTOP = digitalRead(Pin3);
  buttonStateD = digitalRead(Pin4);
}

