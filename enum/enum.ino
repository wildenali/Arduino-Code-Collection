enum Menu{menu_utama, mode_1, mode_2};

Menu menu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  menu = menu_utama;
  Serial.print(menu);
  Serial.print("\t");
  
  menu = mode_1;
  Serial.print(menu);
  Serial.print("\t");
  
  menu = mode_2;
  Serial.print(menu);
  Serial.print("\n");
}
