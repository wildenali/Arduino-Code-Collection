/*================ Motor =======================================================*/
#define MotorKanan 6
#define MotorKiri 5

/*================ PID =========================================================*/
unsigned long lastTime;
double PID;
double errSum, lastErr;
int lastError;
int Error;
int16_t PIDLeft, PIDRight;
float gas = 150;
int potensio;

int kp;
int kd;
int ki;

float persen_accel;
int kec_awal_accel;

void hitungPID()
{
/*-----------Cara Baca DATA satu satu si pixycam2-------*/
  if (pixy.line.numVectors) 
      {
        unsigned long now = millis();
        double timeChange = (double)(now - lastTime);
        
        Error = (int32_t)pixy.frameWidth/2 - pixy.line.vectors->m_x1;
        lcd.setCursor(6, 0);
        lcd.print(Error);

//        potensio = analogRead(A0);
//        lcd.setCursor(0, 0);
//        lcd.print(potensio);
//         
//        Error = 512 - potensio;
//        lcd.setCursor(6, 0);
//        lcd.print(Error);
        
        errSum += (Error * timeChange);
        double dErr = (Error - lastErr) / timeChange;
        
        PID = kp * Error + ki * errSum + kd * dErr;
        
        lastErr = Error;                                                          
        lastTime = now;
      }
}

void eksekusimotor()
{
  PIDLeft = gas - PID + (kec_awal_accel * persen_accel);
  PIDRight = gas + PID + (kec_awal_accel * persen_accel);
//  PIDLeft = gas - PID;
//  PIDRight = gas + PID;
        
  if(PIDLeft > 255)           {PIDLeft = 255;}
  if(PIDLeft <= 127)          {PIDLeft = 127;}
  if(PIDRight > 255)          {PIDRight = 255;}
  if(PIDRight <= 127)         {PIDRight = 127;}

  analogWrite(MotorKiri, PIDLeft);
  analogWrite(MotorKanan, PIDRight);
  lcd.setCursor(0, 1);
  lcd.print(PIDLeft);
  lcd.setCursor(6, 1);
  lcd.print(PIDRight);
}
