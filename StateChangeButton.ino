const int ledPin = 25;       // the pin that the LED is attached to
const int buttonPin = 15;    // the pin that the pushbutton is attached to
bool lastTombolState = 0;

void setup() {
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}


void loop() {
  
  Serial.println(tombol(buttonPin));

}

bool tombol(const int pin){
  bool buttonState;
  bool buttonPushCounter = false;
  buttonState = digitalRead(pin);
  if (buttonState != lastTombolState) {
    if (buttonState == HIGH){
      buttonPushCounter = true;
      Serial.println("cek");
    }
  }
  lastTombolState = buttonState;

  if (buttonPushCounter == true) {
    buttonPushCounter = false;
    return true;
  }else{
    return false;
  }
  
}

