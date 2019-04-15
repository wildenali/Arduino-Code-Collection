unsigned long currentTime = millis();
static unsigned long lastAccelTime = 0;
int selisih_waktu = 0;
int count_down;
int persen_acc;
int accel_aktif = true;

void accel_motor(int berapa_milidetik, int kecepatan_accel){
  kec_awal_accel = kecepatan_accel;
  lastAccelTime = millis();
  while(accel_aktif){
    currentTime = millis();
    selisih_waktu = currentTime - lastAccelTime;
    count_down = berapa_milidetik - (currentTime - lastAccelTime);
    
    if (count_down < 0) {
      count_down = 0;
      lastAccelTime = millis();
      accel_aktif = false;
    }
    
    persen_acc = map(count_down, 0, berapa_milidetik, 0, 100);
    persen_accel = (float)persen_acc / 100;
    
    lcd.setCursor(12, 0);
    lcd.print(count_down);
    
    hitungPID();
    eksekusimotor();
    
    delay(50);
    lcd.clear();
  }
}









// contoh penggunaan Acceleration
////========================= Accel =========================
//    while(menu_tujuan == true){
//    accel_motor(3000, 100);        //accel_motor(milidetik, pertambahan_kecepatan)
//      
//   
//      if(tombol() == "OK") {
//        menu_tujuan = false;
//        ui_menu = false;
//      }
//      else if(tombol() == "BACK") {
//        menu_tujuan = false;
//      }
//    }
////========================= Accel =========================
