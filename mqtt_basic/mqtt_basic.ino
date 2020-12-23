#include "CountDown.h"
#include "CountDownConfig.h"
#include "MqttConfig.h"


void setup()
{
  Serial.begin(115200);

  Mqtt_Setup();

  
}

void loop()
{
  if (!client.connected()) {
    Serial.println("Ga konek");
    disconnected_CD.start(60);
    reconnect();
  }
  client.loop();
}
