String htmlHead ="<head> <title>Bootstrap Example</title> <meta charset=\"utf-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css\"> <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js\"></script> <script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js\"></script> </head>";
String htmlBody ="<body> <div> <h2 class=\"text-center\">SELENA 1</h2> <div class=\"container\"> <section> <table class=\"table table-striped\"> <thead> <tr> <th>No</th> <th>User</th> <th>Nilai</th> <th>Time</th> </tr> </thead> <tbody> <tr> <td>1</td> <td>Ucup</td> <td>75</td> <td>07/01/2021 18:00:31</td> </tr> <tr class=\"success\"> <td>2</td> <td>Doe</td> <td>4</td> <td>07/01/2021 19:00:31</td> </tr> <tr> <td>3</td> <td>Moe</td> <td>10</td> <td>07/01/2021 20:00:31</td> </tr> <tr class=\"success\"> <td>4</td> <td>Dooley</td> <td>100</td> <td>07/01/2021 21:00:31</td> </tr> <tr> <td>5</td> <td>Refs</td> <td>0</td> <td>07/01/2021 22:00:31</td> </tr> <tr class=\"success\"> <td>6</td> <td>Activeson</td> <td>3</td> <td>07/01/2021 23:00:31</td> </tr> </tbody> </table> </section> </div> </div> </body>";
String htmlTHead ="<thead> <tr> <th>No</th> <th>User</th> <th>Nilai</th> <th>Time</th> </tr> </thead>";

String nama[5] = {"Ucup", "Suaeb", "Otong", "Jhon", "Michael"};
int nilai[5] = {45, 11, 9, 100, 77};
String date[5] = {"07/01/2020 09:41", "07/01/2020 11:23", "08/01/2020 12:21", "08/01/2020 15:00", "08/01/2020 21:41"};


// byte mac[] = {
//   0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAA
// };
// IPAddress ip(192, 168, 88, 48);

EthernetServer serverLocal(80);


void webServer_setup()
{
//   Serial.println("Ethernet WebServer Example");

//   Ethernet.begin(mac, ip);

//   if (Ethernet.hardwareStatus() == EthernetNoHardware) {
//     Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
//     while (true) {
//       delay(1); // do nothing, no point running without Ethernet hardware
//     }
//   }
//   if (Ethernet.linkStatus() == LinkOFF) {
//     Serial.println("Ethernet cable is not connected.");
//   }

//   // start the server
  serverLocal.begin();
//   Serial.print("server is at ");
//   Serial.println(Ethernet.localIP());
}

void webServer_response()
{
  // listen for incoming clients
  EthernetClient client = serverLocal.available();
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

          client.println("<!DOCTYPE html>");
          client.println("<html lang=\"en\">");
          client.println(htmlHead);
          client.println("<body>");

          client.println("<div>");
            client.println("<h2 class=\"text-center\">SELENA 1</h2>");
            client.println("<div class=\"container\">");
              client.println("<table class=\"table table-striped\">");
              client.println(htmlTHead);
              client.println("<tbody>");
              int i = 1;
                // for (int i = 0; i < 5; i++)
                // {
                  // if (i % 2 == 0) client.println("<tr>");
                  // else            client.println("<tr class=\"success\">");
                    // client.println("<td>"); client.println(i+1); client.println("</td>");
                    // client.println("<td>"); client.println(nama[i]); client.println("</td>");
                    // client.println("<td>"); client.println(nilai[i]); client.println("</td>");
                    // client.println("<td>"); client.println(date[i]); client.println("</td>");
                    
                    // client.println("<td>"); client.println(i+1); client.println("</td>");
                    // client.println("<td>"); client.println(userName); client.println("</td>");

                    ////////////////////////////////////////////////////////////////////////////////////////////////
                    if (SD.exists(filename)) {
                      databaseFile = SD.open(filename);
                      if (databaseFile)
                      {
                        Serial.println("Read database...");
                        while (databaseFile.available())
                        {
                          String list = databaseFile.readStringUntil('\n');
                          Serial.println(list);

                          userName = "";
                          int firstDelimiterUsername = list.indexOf("User=");
                          int lastDelimiterUsername = list.indexOf(",Nilai=");
                          userName = list.substring(firstDelimiterUsername+5, lastDelimiterUsername);
                          Serial.print("userName=");
                          Serial.println(userName);

                          nilaiUser = "";
                          int firstDelimiterNilaiUser = list.indexOf("Nilai=");
                          int lastDelimiterNilaiUser = list.indexOf(",Time=");
                          nilaiUser = list.substring(firstDelimiterNilaiUser+6, lastDelimiterNilaiUser);
                          Serial.print("nilaiUser=");
                          Serial.println(nilaiUser);

                          timeStamp = "";
                          int firstDelimiterTimeStamp = list.indexOf("Time=");
                          int lastDelimiterTimeStamp = list.lastIndexOf(",");
                          timeStamp = list.substring(firstDelimiterTimeStamp+5, lastDelimiterTimeStamp);
                          Serial.print("timeStamp=");
                          Serial.println(timeStamp);

                          client.println("<tr>");
                            client.println("<td>"); client.println(i++); client.println("</td>");
                            client.println("<td>"); client.println(userName); client.println("</td>");
                            client.println("<td>"); client.println(nilaiUser); client.println("</td>");
                            client.println("<td>"); client.println(timeStamp); client.println("</td>");
                          client.println("</tr>");
                        }
                        databaseFile.close();
                      } else {
                        Serial.println("error Read database...");
                      }
                    }
                    ////////////////////////////////////////////////////////////////////////////////////////////////
                  // client.println("</tr>");
                // }
              client.println("</tbody>");
              client.println("</table>");
            client.println("</div>");
          client.println("</div>");

          client.println("</body>");
          client.println("</html>");

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
    // delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}