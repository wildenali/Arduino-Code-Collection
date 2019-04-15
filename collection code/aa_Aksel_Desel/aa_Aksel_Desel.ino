int sensVal = 0;    //Value read from pot
int val = 0;        //Desired speed value
int spd = 0;        //Actual speed to run train
int accel = 150;    // Speed to accelerate, lower numbers are faster
int decel = 60;     //Speed to decelerate, lower numbers are faster 
int outPin = 10;    //Motor control pin
   
   static unsigned long lastAccelTime = 0;
   static unsigned long lastDecelTime = 0;

   unsigned long currentTime = millis();

void setup() {
 //set inputs and outputs:
 pinMode(outPin, OUTPUT);
 pinMode(0, INPUT);

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
 Serial.print("\t"); 
 delay (200);
 
  // ****Acceleration**** 
  if (currentTime - lastAccelTime > accel) {
      lastAccelTime = currentTime;
      if (spd < val) {
          spd++;
          analogWrite(outPin, spd);
      
      Serial.print(spd);
      Serial.print("\t");
      Serial.println((byte)spd);
          }
      }

  // ****Deceleration**** 
  if (currentTime - lastDecelTime > decel) {
      lastDecelTime = currentTime;
      if (spd > val) {
          spd = spd / 1.01;
          analogWrite(outPin, spd);
          }
      }
}
