/*================ data EEPROM =========================================*/
#include <EEPROM.h>
// 50; /*---untuk alamat Speed (Rpm)----*/
// 51; /*---untuk alamat Kp-------------*/
// 52; /*---untuk alamat Kd-------------*/

int kade=10;
int Rpm = 100;
int Kp = 1;

int Er = 12;
int i=0;

int resetRpm = 100;
int resetKp = 1;
int resetkade = 10; /*--Kd bisa di disimpan & direset jika nilai dibawah 255---*/

/*================ view LCD =========================================*/
int screenWidth = 16;
int screenHeight = 2;

String line1 = "  AGV WORKING "; // Static line
String line2 = "Clean My Path, Please"; // Scrolling line

int stringStart, stringStop = 0;
int scrollCursor = screenWidth;

void viewLCD(){
    tombolBarisPertama();
    tombolBarisKedua();
    tombolBarisKetiga();
    tombolBarisKeempat();
  
/*---------------Home (tombol START ganti label HOME)------------------*/
setHome:   
        lcd.setCursor(0, 0);
        lcd.print(line1);
  
        lcd.setCursor(scrollCursor, 1);
        lcd.print(line2.substring(stringStart,stringStop));
        delay(500);  
        lcd.clear();
  
        if(stringStart == 0 && scrollCursor > 0){
                scrollCursor--;
                stringStop++;
                } 
        else if (stringStart == stringStop){
                stringStart = stringStop = 0;
                scrollCursor = screenWidth;
                } 
        else if (stringStop == line2.length() && scrollCursor == 0) {
                stringStart++;
                } 
        else {
                stringStart++;
                stringStop++;
                }
          
        tombolBarisKeempat();
        if (buttonStateSTOP  == LOW){
            lcd.clear();
            goto setMenu;
            delay(50);
            }          
               
      goto setHome;
  
/*---------------Menu (tombol STOP ganti label SETUP)-------------------*/
setMenu: 
      int Kd = 100*kade; /*perkalian Kd agar bisa simpan di eeprom*/ 
      Rpm =EEPROM.read(50);
      Kp  =EEPROM.read(51);
      kade=EEPROM.read(52); /*----untuk nilai Kd-----*/
  
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Rpm  Kp  Kd   Er");
   
      lcd.setCursor(0,1); 
      lcd.print(Rpm  );
  
      lcd.setCursor(5,1);
      lcd.print(Kp);   
  
      lcd.setCursor(8,1);
      lcd.print(Kd);
      delay(50);  
    
      lcd.setCursor(14,1);
      lcd.print(Er);  

  tombolBarisPertama(); 
      if (buttonState1 == LOW)    {Rpm=Rpm-5;  delay(20);lcd.setCursor(0,1);}EEPROM.write(50,Rpm) ;delay(20); /*---adjust Rpm--*/
      if (buttonState2 == LOW)    {Kp--;       delay(20);lcd.setCursor(5,1);}EEPROM.write(51,Kp)  ;delay(20);      /*---adjust Kp--*/
      if (buttonState3 == LOW)    {kade--;     delay(20);lcd.setCursor(8,1);}EEPROM.write(52,kade);delay(20); /*---adjust Kd--*/
      if (buttonStateA == LOW)    {EEPROM.write(50,resetRpm);EEPROM.write(51,resetKp);EEPROM.write(52,resetkade);lcd.clear();delay(50);}     

  tombolBarisKedua();
      if (buttonState4 == LOW)    {Rpm=Rpm+5;  delay(20);lcd.setCursor(0,1);}EEPROM.write(50,Rpm) ;delay(20); /*---adjust Rpm--*/
      if (buttonState5 == LOW)    {Kp++;       delay(20);lcd.setCursor(5,1);}EEPROM.write(51,Kp)  ;delay(20);      /*---adjust Kp--*/
      if (buttonState6 == LOW)    {kade++;     delay(20);lcd.setCursor(8,1);}EEPROM.write(52,kade);delay(20); /*---adjust Kd--*/

  if (buttonStateA == LOW)    {EEPROM.write(50,resetRpm);EEPROM.write(51,resetKp);EEPROM.write(52,resetkade);lcd.clear();delay(50);}     
                    
  tombolBarisKeempat();
      if (buttonStateSTART == LOW){lcd.clear();goto setHome;}  
                    
  goto setMenu;    
}

