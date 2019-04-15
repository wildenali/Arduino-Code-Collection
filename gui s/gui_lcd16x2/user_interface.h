void user_interface_setup() {
  lcd.begin(16, 2); // initialize the lcd
  lcd.setBacklight(255);
  
  lcd.home();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  AGV WORKING");
  delay(1000);
  lcd.clear();
}

String ui_tujuan(String tujuan) {
  lcd.setCursor(0, 0);
  lcd.print("Tujuan: ");
  lcd.setCursor(8, 0);
  lcd.print(tujuan); 
  delay(500);
  lcd.clear();
  return tujuan;
}

int cek(int cok){
  return cok;
}







//  lcd.setCursor(11, 0);
//  lcd.print(tombol()); 
//
//  lcd.setCursor(0, 1);
//  lcd.print(tombolBarisPertama()); 
//  lcd.setCursor(3, 1);
//  lcd.print(tombolBarisKedua()); 
//  lcd.setCursor(7, 1);
//  lcd.print(tombolBarisKetiga()); 
//  lcd.setCursor(11, 1);
//  lcd.print(tombolBarisKeempat());
