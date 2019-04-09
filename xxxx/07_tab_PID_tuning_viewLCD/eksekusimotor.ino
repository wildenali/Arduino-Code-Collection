int16_t PIDLeft, PIDRight;
double PID;

void eksekusimotor()
{
        PIDLeft = gas - PID;
        PIDRight = gas + PID;
    
        if(PIDLeft  >  gas)         {PIDLeft  = gas;}
        if(PIDLeft  <= 127)         {PIDLeft  = 127;}
        if(PIDRight >  gas)         {PIDRight = gas;}
        if(PIDRight <= 127)         {PIDRight = 127;}
    
        constrain(PIDLeft,127,gas);
        constrain(PIDRight,127,gas);
    
        analogWrite(MotorKiri, PIDLeft);
        analogWrite(MotorKanan, PIDRight);       

        Serial.print("Kiri ");
        Serial.print(PIDLeft);    Serial.print("\t");
        Serial.print("Kanan ");
        Serial.print(PIDRight);   Serial.print("\n");
        delay(50);
}
