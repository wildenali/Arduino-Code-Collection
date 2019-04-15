//  Serial.print("Kiri ");
//  Serial.print(PIDLeft);    Serial.print("\t");
//  Serial.print("Kanan ");
//  Serial.print(PIDRight);   Serial.print("\n");

////       unsigned long currentMillis = millis(); // grab current time
//       unsigned int currentMillis = millis(); // grab current time
//       
//       // check if "interval" time has passed (1000 milliseconds)
//       if ((unsigned long)(currentMillis - previousMillis) >= interval) {
//         previousMillis = millis();
//       }
//       int count_down = interval - (currentMillis - previousMillis);
//       
//       lcd.setCursor(0, 1);
//       lcd.print(interval);
//       
//       lcd.setCursor(9, 1);
//       lcd.print(count_down);
//       
//       lcd.setCursor(0, 0);
//       lcd.print(currentMillis);
//        
//       lcd.setCursor(9, 0);
//       lcd.print(previousMillis);
//       
//       delay(100);  
//       lcd.clear();  


//String abc;
//  ui_go(abc);
//  if(digitalRead(12) == LOW && digitalRead(11) == LOW) {
//    ui_tujuan();
//  }
//  else if(digitalRead(12) == HIGH && digitalRead(11) == LOW) {
//    ui_kecepatan();
//  }
//  else if(digitalRead(12) == LOW && digitalRead(11) == HIGH) {
//    ui_setting_P();    
//  }
//  else if(digitalRead(12) == HIGH && digitalRead(11) == HIGH) {
//    ui_setting_D();    
//  }
