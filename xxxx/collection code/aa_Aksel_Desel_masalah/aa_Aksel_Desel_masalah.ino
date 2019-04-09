
int sensVal = 0;    //Value read from pot
int val = 0;        //Desired speed value
int spd = 0;        //Actual speed to run train
int accel = 150;    // Speed to accelerate, lower numbers are faster
int decel = 60;     //Speed to decelerate, lower numbers are faster
int outPin = 10;    //Motor control pin

void setup() {
 //set inputs and outputs:
 pinMode(outPin, OUTPUT);
 pinMode(0, INPUT);
 
 setPwmFrequency(10,1); //set a higher, inaudible PWM frequency on pins 9 and 10
 
 Serial.begin(9600);
 
 //Leave voltage at 0 while pot is low, reset button can thus be used as emergency stop:
 analogWrite(outPin, 0);
 while (sensVal < 100) {
   sensVal = analogRead(0);
 }
}

void loop() {
 sensVal = analogRead(0);                   //get value from pot
 sensVal = map(sensVal, 0, 1023, 0, 140);   //map to PWM range
 sensVal = constrain(sensVal, 0, 255);      //allows for pot range tweaking
 
 //stops powering the motor below stall
 if (sensVal < 20) {
      val = 0;
      }
 else val = sensVal;
 
 Serial.println(sensVal); //debugging
 Serial.println(val);     //""
 Serial.println(spd);     //""
 
 // ****Acceleration**** 
 if (spd < val) {
   analogWrite(outPin, spd);
   //Serial.println(spd);
   delay(accel);
   spd++;
 }
 else if (spd > val) {
   analogWrite(outPin, spd);
   //Serial.println(spd);
   delay(decel);
   spd = spd / 1.01;
 }
 
}

//-------------------------------------------------------------------------------------

void setPwmFrequency(int pin, int divisor) {
 byte mode;
 if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
   switch(divisor) {
     case 1:    mode = 0x01; break;
     case 8:    mode = 0x02; break;
     case 64:   mode = 0x03; break;
     case 256:  mode = 0x04; break;
     case 1024: mode = 0x05; break;
     default: return;
   }
   if(pin == 5 || pin == 6) {
     TCCR0B = TCCR0B & 0b11111000 | mode;
   } else {
     TCCR1B = TCCR1B & 0b11111000 | mode;
   }
 } else if(pin == 3 || pin == 11) {
   switch(divisor) {
     case 1: mode = 0x01; break;
     case 8: mode = 0x02; break;
     case 32: mode = 0x03; break;
     case 64: mode = 0x04; break;
     case 128: mode = 0x05; break;
     case 256: mode = 0x06; break;
     case 1024: mode = 0x7; break;
     default: return;
   }
   TCCR2B = TCCR2B & 0b11111000 | mode;
 }
}
