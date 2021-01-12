void SDCard_setup()
{
  // initialize SD card
  Serial.println("Initializing SD card...");
  if (!SD.begin(4)) {
      Serial.println("ERROR - SD card initialization failed!");
      Serial.println("Restart...");
      delay(1000);
      ku_restart();
      return;    // init failed
  }
  Serial.println("SUCCESS - SD card initialized.");
}