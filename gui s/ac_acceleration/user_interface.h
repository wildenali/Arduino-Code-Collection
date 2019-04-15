int address_tujuan = 1;
int address_kecepatan = 2;
int address_P = 3;
int address_D = 4;

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

int set_tujuan;
String tujuan;

int set_kecepatan;
String kecepatan;

int set_P;
String P;

int set_D;
String D;


String ui_tujuan() {
  if(tombol() == "F4")   {set_tujuan++;}
  if(tombol() == "F3")   {set_tujuan--;}
  if(set_tujuan <= 0)    {set_tujuan = 0;}    // batas minimal adalah 0
  if(set_tujuan >= 100)  {set_tujuan = 100;}    // batas minimal adalah 100

  tujuan = String(set_tujuan);        // konversi int ke String
  kecepatan = String(set_kecepatan);        // konversi int ke String  

  lcd.setCursor(0, 0);
  lcd.print(">Tujuan:");
  lcd.setCursor(9, 0);
  lcd.print(tujuan); 
  lcd.setCursor(0, 1);
  lcd.print(" Kecepatan:");
  lcd.setCursor(12, 1);
  lcd.print(kecepatan);

  if(tombol() != NULL) {delay(500);  lcd.clear();}
  
  EEPROM.write(address_tujuan, set_tujuan);
  return tujuan;
}

String ui_kecepatan() {
  if(tombol() == "F4")      {set_kecepatan++;}
  if(tombol() == "F3")      {set_kecepatan--;}
  if(set_kecepatan <= 0)    {set_kecepatan = 0;}    // batas minimal adalah 0
  if(set_kecepatan >= 100)  {set_kecepatan = 100;}    // batas minimal adalah 100

  tujuan = String(set_tujuan);        // konversi int ke String
  lcd.setCursor(0, 0);
  lcd.print(" Tujuan:");
  lcd.setCursor(9, 0);
  lcd.print(tujuan); 

  kecepatan = String(set_kecepatan);        // konversi int ke String  
  lcd.setCursor(0, 1);
  lcd.print(">Kecepatan:");
  lcd.setCursor(12, 1);
  lcd.print(kecepatan); 

  if(tombol() != NULL) {delay(500);  lcd.clear();}
  
  EEPROM.write(address_kecepatan, set_kecepatan);
  return kecepatan;
}

void ui_setting_P() {
  if(tombol() == "F4")   {set_P++;}
  if(tombol() == "F3")   {set_P--;}
  if(set_P <= 0)         {set_P = 0;}    // batas minimal adalah 0
  if(set_P >= 10)        {set_P = 10;}    // batas minimal adalah 100

  
  lcd.setCursor(0, 0);
  lcd.print("= Setting =");

  P = String(set_P);        // konversi int ke String
  lcd.setCursor(0, 1);
  lcd.print(">P:");
  lcd.setCursor(3, 1);
  lcd.print(P);
  
  D = String(set_D);        // konversi int ke String
  lcd.setCursor(7, 1);
  lcd.print(" D:");
  lcd.setCursor(10, 1);
  lcd.print(D);
  
  if(tombol() != NULL) {delay(500);  lcd.clear();}
  EEPROM.write(address_P, set_P);
}

void ui_setting_D() {
  if(tombol() == "F4")   {set_D++;}
  if(tombol() == "F3")   {set_D--;}
  if(set_D <= 0)         {set_D = 0;}      // batas minimal adalah 0
  if(set_D >= 100)       {set_D = 100;}    // batas minimal adalah 100
  
  lcd.setCursor(0, 0);
  lcd.print("= Setting =");

  P = String(set_P);        // konversi int ke String
  lcd.setCursor(0, 1);
  lcd.print(" P:");
  lcd.setCursor(3, 1);
  lcd.print(P);
  
  D = String(set_D);
  lcd.setCursor(7, 1);
  lcd.print(">D:");
  lcd.setCursor(10, 1);
  lcd.print(D);

  if(tombol() != NULL) {delay(500);  lcd.clear();}
  EEPROM.write(address_D, set_D);
}

void ui_go(int go) {
  lcd.setCursor(0, 0);
  lcd.print("= Menuju =");
  lcd.setCursor(3, 1);
  lcd.print(go);
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
