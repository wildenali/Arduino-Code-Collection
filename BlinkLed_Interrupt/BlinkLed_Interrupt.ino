#include <TimerOne.h>

// This example uses the timer interrupt to blink an LED
// and also demonstrates how to share a variable between
// the interrupt and the main program.


const int led = 3;  // the pin with a LED
const int lad = 4;  // the pin with a LED

void setup(void)
{
  pinMode(led, OUTPUT);
  pinMode(lad, OUTPUT);
  Timer1.initialize(1250);          // 0.00125 seconds = 1250 * 1000000
  Timer1.attachInterrupt(blinkLED);
  Serial.begin(115200);

  digitalWrite(lad, LOW);
}


// The interrupt will blink the LED, and keep
// track of how many times it has blinked.
int ledState = LOW;
volatile unsigned long blinkCount = 0; // use volatile for shared variables

void blinkLED(void)
{
  if (ledState == LOW) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }
  digitalWrite(led, ledState);
}


void loop(void)
{
  Serial.println("Cek");
  delay(5000);
}
