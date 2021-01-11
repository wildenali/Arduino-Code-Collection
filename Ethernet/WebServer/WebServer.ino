#include <SPI.h>
#include <Ethernet.h>

//String html ="<!DOCTYPE html> <html> <head> <style>table {font-family: arial, sans-serif;border-collapse: collapse;width: 100%;}td, th {border: 1px solid #dddddd;text-align: left;padding: 8px;}tr:nth-child(even) {background-color: #dddddd;} </style> </head> <body> <h2>HTML Table</h2> <table> <tr> <th>Company</th> <th>Contact</th> <th>Country</th> </tr> <tr> <td>Alfreds Futterkiste</td> <td>Maria Anders</td> <td>Germany</td> </tr> <tr> <td>Centro comercial Moctezuma</td> <td>Francisco Chang</td> <td>Mexico</td> </tr> <tr> <td>Ernst Handel</td> <td>Roland Mendel</td> <td>Austria</td> </tr> <tr> <td>Island Trading</td> <td>Helen Bennett</td> <td>UK</td> </tr> <tr> <td>Laughing Bacchus Winecellars</td> <td>Yoshi Tannamuri</td> <td>Canada</td> </tr> <tr> <td>Magazzini Alimentari Riuniti</td> <td>Giovanni Rovelli</td> <td>Italy</td> </tr> </table> </body> </html>";
//String html ="<!DOCTYPE html> <html> <head> <style>table {font-family: arial, sans-serif;border-collapse: collapse;width: 100%;}td, th {border: 1px solid #dddddd;text-align: left;padding: 8px;}tr:nth-child(even) {background-color: #dddddd;} </style> </head> <body> <h2>HTML Table</h2> <table> <tr> <th>PERUSAHAAN</th> <th>Contact</th> <th>Country</th> </tr> <tr> <td>Alfreds Futterkiste</td> <td>Maria Anders</td> <td>Germany</td> </tr> <tr> <td>Centro comercial Moctezuma</td> <td>Francisco Chang</td> <td>Mexico</td> </tr> <tr> <td>Ernst Handel</td> <td>Roland Mendel</td> <td>Austria</td> </tr> <tr> <td>Island Trading</td> <td>Helen Bennett</td> <td>UK</td> </tr> <tr> <td>Laughing Bacchus Winecellars</td> <td>Yoshi Tannamuri</td> <td>Canada</td> </tr> <tr> <td>Magazzini Alimentari Riuniti</td> <td>Giovanni Rovelli</td> <td>Italy</td> </tr> </table> </body> </html>";
//String html ="<!DOCTYPE html> <html lang=\"en\"> <head> <title>Bootstrap Example</title> <meta charset=\"utf-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css\"> <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js\"></script> <script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js\"></script> <script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js\"></script> </head> <body> <div class=\"container\"> <div class=\"jumbotron\"> <h1>Bootstrap Tutorial</h1> <p>Bootstrap is the most popular HTML, CSS, and JS framework for developing responsive, mobile-first projects on the web.</p> </div> <p>This is some text.</p> <p>This is another text.</p> </div> </body> </html>";
String html ="<!DOCTYPE html> <html lang=\"en\"> <head> <title>Bootstrap Example</title> <meta charset=\"utf-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css\"> <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js\"></script> <script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js\"></script> <script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js\"></script> </head> <body> <div class=\"container\"> <h2>Basic Table</h2> <p>The .table class adds basic styling (light padding and horizontal dividers) to a table:</p> <table class=\"table\"> <thead> <tr> <th>Firstname</th> <th>Lastname</th> <th>Email</th> </tr> </thead> <tbody> <tr> <td>John</td> <td>Doe</td> <td>john";

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAA
};
IPAddress ip(192, 168, 88, 48);

EthernetServer server(80);

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

  Ethernet.begin(mac, ip);

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    bool currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          client.println(html);
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
