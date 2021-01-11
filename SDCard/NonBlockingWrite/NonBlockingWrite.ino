#include <SD.h>

const char filename[] = "demo.txt";

File txtFile;

String buffer;

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // reserve 1kB for String used as a buffer
  buffer.reserve(1024);

  pinMode(LED_BUILTIN, OUTPUT);

  // init the SD card
  if (!SD.begin()) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }

  // If you want to start from an empty file,
  // uncomment the next line:
  // SD.remove(filename);

  // try to open the file for writing
  txtFile = SD.open(filename, FILE_WRITE);
  if (!txtFile) {
    Serial.print("error opening ");
    Serial.println(filename);
    while (1);
  }

  // add some new lines to start
  txtFile.println();
  txtFile.println("Hello World!");

  Serial.println("Next...");
}

void loop() {
  // check if it's been over 10 ms since the last line added
  unsigned long now = millis();
  if ((now - lastMillis) >= 10) {
    // add a new line to the buffer
    buffer += "Hello ";
    buffer += now;
    buffer += "\r\n";

    lastMillis = now;
  }

  // check if the SD card is available to write data without blocking
  // and if the buffered data is enough for the full chunk size
  unsigned int chunkSize = txtFile.availableForWrite();
  if (chunkSize && buffer.length() >= chunkSize) {
    // write to file and blink LED
    digitalWrite(LED_BUILTIN, HIGH);
    txtFile.write(buffer.c_str(), chunkSize);
    digitalWrite(LED_BUILTIN, LOW);

    // remove written data from buffer
    buffer.remove(0, chunkSize);
  }

  // re-open the file for reading:
  txtFile = SD.open("demo.txt");
  if (txtFile) {
    Serial.println("demo.txt:");

    // read from the file until there's nothing else in it:
    while (txtFile.available()) {
      Serial.write(txtFile.read());
    }
    // close the file:
    txtFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening demo.txt");
  }
}
