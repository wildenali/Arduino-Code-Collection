int16_t steer;
int16_t gas;



void setup() {
  Serial1.begin(19200);
}

void loop(void) {
  steer = 0;//map(analogRead(potA), 0, 1023, -100, 100);
  gas = 100;//map(analogRead(potB), 0, 1023, -100, 100);
  Serial1.write((uint8_t *) &steer, sizeof(steer));
  Serial1.write((uint8_t *) &gas, sizeof(gas));
}
