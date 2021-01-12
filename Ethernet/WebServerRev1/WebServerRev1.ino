#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <SD.h>

const char filename[] = "dbsl1.svn";
File databaseFile;

#include "Restart.h"
#include "MqttConfig.h"
#include "webServer.h"
#include "SDCard.h"


void setup() {
  Serial.begin(115200);
  
  SDCard_setup();
  Mqtt_Setup();
  webServer_setup();

    // Check Database File
    // if (SD.exists("example.txt")) {
    //   Serial.println("example.txt exists.");
    // } else {
    //   Serial.println("example.txt doesn't exist.");
    // }

    // Delete Database file
    // Serial.println("Deleting Database File...");
    // SD.remove(filename);

    // Create Database
    // databaseFile = SD.open(filename, FILE_WRITE);
    // if (databaseFile)
    // {
    //   Serial.println("Create database...");
    //   databaseFile.println("User: dua,");
    //   databaseFile.println("Nilai: 43,");
    //   databaseFile.println("Time: 02/21/2021 10:33,");
    //   Serial.println("Create database...done");
    //   databaseFile.close();
    // }

    // Read Database
    if (SD.exists(filename)) {
      databaseFile = SD.open(filename);
      if (databaseFile)
      {
        Serial.println("Read database...");
        while (databaseFile.available())
        {
          String list = databaseFile.readStringUntil('\n');
          Serial.println(list);

          // if (list.indexOf("User"))
          // {
            userName = "";
            int firstDelimiterUsername = list.indexOf("User=");
            int lastDelimiterUsername = list.indexOf(",Nilai=");
            // Serial.println("firstDelimiterUsername= " + String(firstDelimiterUsername) + " lastDelimiterUsername= " + String(lastDelimiterUsername));
            userName = list.substring(firstDelimiterUsername+5, lastDelimiterUsername);
            Serial.print("userName=");
            Serial.println(userName);

            nilaiUser = "";
            int firstDelimiterNilaiUser = list.indexOf("Nilai=");
            int lastDelimiterNilaiUser = list.indexOf(",Time=");
            // Serial.println("firstDelimiterNilaiUser= " + String(firstDelimiterNilaiUser) + " lastDelimiterNilaiUser= " + String(lastDelimiterNilaiUser));
            nilaiUser = list.substring(firstDelimiterNilaiUser+6, lastDelimiterNilaiUser);
            Serial.print("nilaiUser=");
            Serial.println(nilaiUser);

            timeStamp = "";
            int firstDelimiterTimeStamp = list.indexOf("Time=");
            int lastDelimiterTimeStamp = list.lastIndexOf(",");
            // Serial.println("firstDelimiterTimeStamp= " + String(firstDelimiterTimeStamp) + " lastDelimiterTimeStamp= " + String(lastDelimiterTimeStamp));
            timeStamp = list.substring(firstDelimiterTimeStamp+5, lastDelimiterTimeStamp);
            Serial.print("timeStamp=");
            Serial.println(timeStamp);

          // }
          // if (list.indexOf("Nilai"))
          // {
          //   nilaiUser = "";
          //   int firstDelimiter = list.indexOf("Nilai=");
          //   int lastDelimiter = list.indexOf(",Time=");
          //   Serial.println("firstDelimiter= " + String(firstDelimiter) + " lastDelimiter= " + String(lastDelimiter));
          //   nilaiUser = list.substring(firstDelimiter+6, lastDelimiter);
          //   Serial.print("nilaiUser=");
          //   Serial.println(nilaiUser);
          // }

          // if (list.startsWith("User"))
          // {
          //   userName = "";
          //   int firstDelimiter = list.lastIndexOf("=");
          //   int lastDelimiter = list.lastIndexOf(",");
          //   userName = list.substring(firstDelimiter+1, lastDelimiter);
          //   Serial.print("userName=");
          //   Serial.println(userName);
          // }
          // if (list.startsWith("Nilai"))
          // {
          //   nilaiUser = "";
          //   int firstDelimiter = list.lastIndexOf("=");
          //   int lastDelimiter = list.lastIndexOf(",");
          //   nilaiUser = list.substring(firstDelimiter+1, lastDelimiter);
          //   Serial.print("nilaiUser=");
          //   Serial.println(nilaiUser);
          // }
          // if (list.startsWith("Time"))
          // {
          //   timeStamp = "";
          //   int firstDelimiter = list.lastIndexOf("=");
          //   int lastDelimiter = list.lastIndexOf(",");
          //   timeStamp = list.substring(firstDelimiter+1, lastDelimiter);
          //   Serial.print("timeStamp=");
          //   Serial.println(timeStamp);
          // }

        }
        databaseFile.close();
      } else {
        Serial.println("error Read database...");
      }
    } else {
      Serial.println("file doesn't exist.");
    }
    

    Serial.println("Go to loop");
}


void loop() {

  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 1000) {
      lastReconnectAttempt = now;
      connectionAttempt++;
      Serial.print("Attempt to reconnect... ");
      Serial.println(connectionAttempt);
      if (connectionAttempt == 60)
      {
        Serial.println("Restart...!!!");
        delay(1000);
        ku_restart(); 
      }
      if (reconnect()) {
        lastReconnectAttempt = 0;
        connectionAttempt = 0;
      }
    }
  } else {
    client.loop();
  }

  if (Serial.available()) {
    char inChar = Serial.read();
    Serial.println(inChar);
    

    // Save to SDCard
    int nilaiLong = random(0, 100);

    if (inChar == 'y')
    {
      databaseFile = SD.open(filename, FILE_WRITE);
      if (databaseFile)
      {
        Serial.println("Create database...");
        // Serial.println("User=" + userName + ",");
        // Serial.print("Nilai=" + String(nilaiLong) + ",");
        // Serial.println("Time=" + timeStamp + ",");

        if (userName != "" && String(nilaiLong) != "" && timeStamp != "")
        {
          Serial.println("User=" + userName + "," + "Nilai=" + String(nilaiLong) + "," + "Time=" + timeStamp + ",");
          databaseFile.println("User=" + userName + "," + "Nilai=" + String(nilaiLong) + "," + "Time=" + timeStamp + ",");
          // databaseFile.println("User=" + userName + ",");
          // databaseFile.println("Nilai=" + String(nilaiLong) + ",");
          // databaseFile.println("Time=" + timeStamp + ",");
          Serial.println("Create database...done!!!");
        }
        
        databaseFile.close();
        delay(1000);
      }
    }
    
    if (inChar == 'd')
    {
      Serial.println("Delete Database File...");
      delay(1000);
      SD.remove(filename);
    }
  }


  webServer_response();
  
}
