enum Menu{menu_utama, mode_1, mode_2, pengaturan};
Menu menu = menu_utama;

char input;

int pilih_menu;

void tampilan_pilih_menu_utama(){
  Serial.print(">Menu_Utama\t");
  Serial.print(" Mode_1\t\t");
  Serial.print(" Mode_2\t\t");
  Serial.print(" Pengaturan");
  Serial.println();
}

void tampilan_pilih_mode_1(){
  Serial.print(" Menu_Utama\t");
  Serial.print(">Mode_1\t\t");
  Serial.print(" Mode_2\t\t");
  Serial.print(" Pengaturan");
  Serial.println();
}

void tampilan_pilih_mode_2(){
  Serial.print(" Menu_Utama\t");
  Serial.print(" Mode_1\t\t");
  Serial.print(">Mode_2\t\t");
  Serial.print(" Pengaturan");
  Serial.println();
}

void tampilan_pilih_pengaturan(){
  Serial.print(" Menu_Utama\t");
  Serial.print(" Mode_1\t\t");
  Serial.print(" Mode_2\t\t");
  Serial.print(">Pengaturan");
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  Serial.print(">Menu_Utama\t");
  Serial.print(" Mode_1\t\t");
  Serial.print(" Mode_2\t\t");
  Serial.print(" Pengaturan");
  Serial.println();
}

void loop() {
  while(menu == menu_utama) {
    if(Serial.available() > 0) {
      input = Serial.read();

      if(input == '0') {
        tampilan_pilih_menu_utama();
        pilih_menu = input - '0';
      }
      else if(input == '1') {
        tampilan_pilih_mode_1();
        pilih_menu = input - '0';
      }
      else if(input == '2') {
        tampilan_pilih_mode_2();
        pilih_menu = input - '0';
      }
      else if(input == '3') {
        tampilan_pilih_pengaturan();
        pilih_menu = input - '0';
      }
      
      if(input == 'o') {
        menu = pilih_menu;
      }
      
    }
  }

  while(menu == mode_1) {
    Serial.println("mode 1");
//    if(Serial.available() > 0) {
//      input = Serial.read();
//
//      if(input == '2') {
//        tampilan_pilih_mode_1();
//        menu = mode_1;
//      }
//      if(input == 'g') {
//        Serial.println("Gooooooo....");
//      }
//      if(input == 'b') {
//        menu = menu_utama;
//        tampilan_pilih_menu_utama();
//      }
//    }
  }

  //Serial.println("di luar while");
}











//  menu = menu_utama;
//  Serial.print(menu);   Serial.print("\t");
//
//  menu = mode_1;
//  Serial.print(menu);   Serial.print("\t");
//
//  menu = mode_2;
//  Serial.print(menu);   Serial.print("\t");
//
//  menu = setting;
//  Serial.print(menu);   Serial.print("\n");
