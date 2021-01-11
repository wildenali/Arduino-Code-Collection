#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

byte mac[]    = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
int ipA, ipB, ipC, ipD;
IPAddress server(180, 210, 205, 235); // main server

// const char* mqtt_topic1 = "robotics/kicktarget";
const char* mqtt_topic2 = "robotics/crazytoy2";
const char* clientID = "kicktarget_machine1";


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0; i<length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

EthernetClient ethClient;
PubSubClient client(ethClient);

void(* ku_reset) (void) = 0;

bool reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientID)) {
      Serial.println("connected");
      // client.subscribe(mqtt_topic1);
      client.subscribe(mqtt_topic2);
      return true;
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(500);
    }
    Serial.println(disconnected_CD.remaining());
    if (disconnected_CD.remaining() == 0)
    {
      Serial.println("Soft Reset");
      delay(1000);
      ku_reset();
    }
    
  }
}

void Mqtt_Setup()
{
  client.setServer(server, 1883);
  client.setCallback(callback);

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // no point in carrying on, so do nothing forevermore:
    while (true) {
      Serial.println("Soft Reset");
      delay(1000);
      ku_reset();
      // Serial.println("DO NOTHING FOREVER");
      // delay(1);
    }
  }
  // print your local IP address:
  Serial.print("IP address Nya: ");
  Serial.println(Ethernet.localIP());
  ipA = Ethernet.localIP()[0];
  ipB = Ethernet.localIP()[1];
  ipC = Ethernet.localIP()[2];
  ipD = Ethernet.localIP()[3];
  IPAddress ip(ipA, ipB, ipC, ipD);
  Ethernet.begin(mac, ip);

  if (reconnect()) {
    Serial.println("Connected Successfully to MQTT Broker!");
  }
  else {
    Serial.println("Connection Failed!");
  }
  
  delay(1000);
  Serial.println("Mqtt config...Done");
}