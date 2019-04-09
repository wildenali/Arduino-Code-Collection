/*================ PID =============================================*/
unsigned long lastTime;
double errSum, lastErr;

double kp = 1;       
double ki = 0;
double kd = 2000;

int Error;

void hitungPID() 
{
/*-----------Cara Baca DATA satu satu si pixycam2-------*/

  if (pixy.line.numVectors) 
      {
        unsigned long now = millis();
        double timeChange = (double)(now - lastTime);
        
        Error = (int32_t)pixy.frameWidth/2 - pixy.line.vectors->m_x1;
        Serial.println(Error);
        
        errSum += (Error * timeChange);
        double dErr = (Error - lastErr) / timeChange;
        
        PID = kp * Error + ki * errSum + kd * dErr;
        
        lastErr = Error;                                                          
        lastTime = now;
      }
}

