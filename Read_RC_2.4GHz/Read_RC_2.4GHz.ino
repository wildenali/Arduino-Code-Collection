#define ch1 3   // Pin 3 Colokin ke Channel 1 Receiver Remot
#define ch2 4   // Pin 4 Colokin ke Channel 2 Receiver Remot

int ch1Raw = 0;
int ch2Raw = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ch1,INPUT);
  pinMode(ch2,INPUT);
}

void loop(void) {
  ch1Raw = pulseIn(ch1, HIGH);
  ch2Raw = pulseIn(ch2, HIGH);
  Serial.print(ch1Raw);
  Serial.print("\t");
  Serial.println(ch2Raw);
}
