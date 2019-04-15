int address_tujuan = 1;
int address_kecepatan = 2;
int address_P = 3;
int address_D = 4;

int set_tujuan;
String tujuan;

int set_kecepatan;
String kecepatan;



String Pstring;
String Dstring;
String Istring;


void user_interface_setup() {
  lcd.begin(16, 2); // initialize the lcd
  lcd.setBacklight(180);
  
  lcd.home();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  AGV WORKING");
  delay(1000);
  lcd.clear();
}


String ui_tujuan() {
  if(tombol() == "D")   {set_tujuan++;}
  if(tombol() == "C")   {set_tujuan--;}
  if(set_tujuan <= 0)    {set_tujuan = 0;}    // batas minimal aDstringalah 0
  if(set_tujuan >= 100)  {set_tujuan = 100;}    // batas minimal aDstringalah 100

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

  EEPROM.write(address_tujuan, set_tujuan);
  if(tombol() != NULL) {delay(250);  lcd.clear();}
  
  return tujuan;
}

String ui_kecepatan() {
  if(tombol() == "D")      {set_kecepatan++;}
  if(tombol() == "C")      {set_kecepatan--;}
  if(set_kecepatan <= 0)    {set_kecepatan = 0;}    // batas minimal aDstringalah 0
  if(set_kecepatan >= 100)  {set_kecepatan = 100;}    // batas minimal aDstringalah 100

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

  EEPROM.write(address_kecepatan, set_kecepatan);
  if(tombol() != NULL) {delay(250);  lcd.clear();}
  
  return kecepatan;
}

void ui_setting_P() {
  if(tombol() == "D")   {kp++;}
  if(tombol() == "C")   {kp--;}
  if(kp <= 0)         {kp = 0;}    // batas minimal aDstringalah 0
  if(kp >= 10)        {kp = 10;}    // batas minimal aDstringalah 100

  
  lcd.setCursor(0, 0);
  lcd.print("= Setting =");

  Pstring = String(kp);        // konversi int ke String
  lcd.setCursor(0, 1);
  lcd.print(">P:");
  lcd.setCursor(3, 1);
  lcd.print(Pstring);
  
  Dstring = String(kd);        // konversi int ke String
  lcd.setCursor(7, 1);
  lcd.print(" D:");
  lcd.setCursor(10, 1);
  lcd.print(Dstring);
  
  EEPROM.write(address_P, kp);
  if(tombol() != NULL) {delay(250);  lcd.clear();}
}

void ui_setting_D() {
  if(tombol() == "D")   {kd++;}
  if(tombol() == "C")   {kd--;}
  if(kd <= 0)         {kd = 0;}      // batas minimal adalah 0
  if(kd >= 100)       {kd = 100;}    // batas minimal adalah 100
  
  lcd.setCursor(0, 0);
  lcd.print("= Setting =");

  Pstring = String(kp);        // konversi int ke String
  lcd.setCursor(0, 1);
  lcd.print(" P:");
  lcd.setCursor(3, 1);
  lcd.print(Pstring);
  
  Dstring = String(kd);
  lcd.setCursor(7, 1);
  lcd.print(">D:");
  lcd.setCursor(10, 1);
  lcd.print(Dstring);

  EEPROM.write(address_D, kd);
  if(tombol() != NULL) {delay(250);  lcd.clear();}
}

void ui_go(int go) {
  lcd.setCursor(0, 0);
  lcd.print("= Menuju =");
  lcd.setCursor(3, 1);
  lcd.print(go);
}


int menu;
bool ui_menu = true;
bool menu_tujuan = false;
int goal = 0;

void user_interface_menu_utama() {
  while(ui_menu == true) {
    if(tombol() == "B") {menu++;}
    if(tombol() == "A") {menu--;}
    if(menu >= 3)        {menu = 3;}
    if(menu <= 0)        {menu = 0;}
    
    if(menu == 0)        {goal = ui_tujuan().toInt();}    // konversi String to Int
    else if(menu == 1)   {ui_kecepatan();}
    else if(menu == 2)   {ui_setting_P();}
    else if(menu == 3)   {ui_setting_D();}
  
    if(tombol() == "OK" && menu == 0) {menu_tujuan = true; accel_aktif = true;}
    
    while(menu_tujuan == true){
      ui_go(goal);
      if(tombol() == "STARTSTOP3") {
        menu_tujuan = false;
        ui_menu = false;
      }
      else if(tombol() == "BACK") {
        menu_tujuan = false;
      }
    } 
  }
}
