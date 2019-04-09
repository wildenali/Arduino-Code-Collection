#include <Pixy2.h>

#define MotorKanan 13
#define MotorKiri 12

Pixy2 pixy;

unsigned long lastTime;
double PID;
double errSum, lastErr;

double kp = 3;       
double ki = 0;
double kd = 2500;

int lastError;
int Error;

int16_t PIDLeft, PIDRight;
float gas = 150;

void setup()
{
  Serial1.begin(19200);
  Serial.begin(115200);
  Serial.print("Starting...\n");

  pinMode(MotorKiri, OUTPUT);
  pinMode(MotorKanan, OUTPUT);
  
  pixy.init();
  Serial.println(pixy.changeProg("line"));
  pixy.setLamp(1,1);
}

void loop()
{
  int8_t i;
  char buf[128];
 
  pixy.line.getMainFeatures();

  hitungPID();
  eksekusimotor();
}

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
void eksekusimotor()
{
        PIDLeft = gas - PID;
        PIDRight = gas + PID;
    
        if(PIDLeft > gas)           {PIDLeft = gas;}
        if(PIDLeft <= 0)            {PIDLeft = 0;}
        if(PIDRight > gas)          {PIDRight = gas;}
        if(PIDRight <= 0)           {PIDRight = 0;}

    
        constrain(PIDLeft,0,gas);
        constrain(PIDRight,0,gas);
    
        analogWrite(MotorKiri, PIDLeft);
        analogWrite(MotorKanan, PIDRight);
        

        Serial.print("Kiri ");
        Serial.print(PIDLeft);    Serial.print("\t");
        Serial.print("Kanan ");
        Serial.print(PIDRight);   Serial.print("\n");
        

        Serial1.write((uint8_t *) &PIDRight, sizeof(PIDRight));
        Serial1.write((uint8_t *) &PIDLeft, sizeof(PIDLeft));
        delay(300);
    
      
}

