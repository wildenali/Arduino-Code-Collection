#include <usbhid.h>
#include <usbhub.h>
#include <hiduniversal.h>
#include <hidboot.h>
#include <SPI.h>

// download usb shield library from
// https://github.com/felis/USB_Host_Shield_2.0

String scanResult;
String scanResult2;
bool scanFinished;

class MyParser : public HIDReportParser {
  public:
    MyParser();
    void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
  protected:
    uint8_t KeyToAscii(bool upper, uint8_t mod, uint8_t key);
    virtual void OnKeyScanned(bool upper, uint8_t mod, uint8_t key);
    virtual void OnScanFinished();
};

MyParser::MyParser() {}
USB          Usb;
HIDUniversal Hid(&Usb);
MyParser     Parser;

void MyParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
  if (buf[2] == 1 || buf[2] == 0) return;   // If error or empty, return
  for (uint8_t i = 7; i >= 2; i--) {
    if (buf[i] == 0) continue;              // If empty, skip
    if (buf[i] == UHS_HID_BOOT_KEY_ENTER) { // If enter signal emitted, scan finished
      OnScanFinished();
    }
    else {                                  // If not, continue normally
      OnKeyScanned(i > 2, buf, buf[i]);     // If bit position not in 2, it's uppercase words
    }
    return;
  }
}

uint8_t MyParser::KeyToAscii(bool upper, uint8_t mod, uint8_t key) {
  if (VALUE_WITHIN(key, 0x04, 0x1d)) {      // Letters
    if (upper) return (key - 4 + 'A');
    else return (key - 4 + 'a');
  }
  else if (VALUE_WITHIN(key, 0x1e, 0x27)) { // Numbers
    return ((key == UHS_HID_BOOT_KEY_ZERO) ? '0' : key - 0x1e + '1');
  }
  return 0;
}

void MyParser::OnKeyScanned(bool upper, uint8_t mod, uint8_t key) {
  uint8_t ascii = KeyToAscii(upper, mod, key);
  scanResult = scanResult + (char)ascii;
}

void MyParser::OnScanFinished() {
  scanResult = scanResult.substring(scanResult.length() - 5, scanResult.length());
  scanFinished = true;
  Serial.println(scanResult);
  Serial1.println(scanResult);  // Send to other arduino
}

void setupRFID_Data(){
  Serial.println("Start RFID Reader");
  if (Usb.Init() == -1) {
    Serial.println("OSC did not start.");
  }
  delay(200);
  Hid.SetReportParser(0, &Parser);
}

//String dummyDataRFID(){
////  String res;
////  if     (analogRead(1) == 0 && analogRead(2) == 0)                                                 res = "----------";
////  else if(analogRead(1) == 0 && analogRead(2) > 0 && analogRead(2) <= 1000)                         res = "2000000001";
////  else if(analogRead(1) == 0 && analogRead(2) > 1000)                                               res = "2000000002";
////  else if(analogRead(1) > 0 && analogRead(1) < 1000 && analogRead(2) == 0)                          res = "2000000003";
////  else if(analogRead(1) > 0 && analogRead(1) < 1000 && analogRead(2) > 0 && analogRead(2) <= 1000)  res = "2000000004";
////  else if(analogRead(1) > 0 && analogRead(1) < 1000 && analogRead(2) > 1000)                        res = "2000000005";
////  else if(analogRead(1) > 1000 && analogRead(2) == 0)                                               res = "2000000006";
////  else if(analogRead(1) > 1000 && analogRead(2) > 0 && analogRead(2) <= 1000)                       res = "2000000007";
////  else if(analogRead(1) > 1000 && analogRead(2) > 1000)                                             res = "2000000008";
////  return res;
//  if(scanFinished == true){
//    Serial.print("Panjang Data: ");   Serial.println(scanResult.length());
//    
//    scanResult = scanResult.substring(scanResult.length() - 10, scanResult.length());
//    Serial.print("Hasil       : ");   Serial.println(scanResult);
//    scanFinished = false;
//    scanResult = "";
//  }
//}
//String abc;
//String scanRFID(){
//  if(scanFinished == true){
//    abc = scanResult;
//    scanFinished = false;
//    scanResult = "";
//  }
//  return "";
//}
