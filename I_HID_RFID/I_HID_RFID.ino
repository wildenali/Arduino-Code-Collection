#include "HID_RFID.h"

// Simulation if Arduino A send to Arduino B
// Arduino A (Tx1)
// Arduino B (Rx2
String inData;

void setup(){
  Serial.begin(115200);
  Serial1.begin(9600);
  Serial2.begin(9600);
  setupRFID_Data();
}

void loop(){
  Usb.Task();
  while (Serial2.available() > 0) // Receive from 
  {
    char recieved = Serial2.read();
    inData += recieved; 

    // Process message when new line character is recieved
    if (recieved == '\n')
    {
      Serial.print("Arduino Received: ");
      Serial.print(inData);

      inData = ""; // Clear recieved buffer
    }
  }
}
