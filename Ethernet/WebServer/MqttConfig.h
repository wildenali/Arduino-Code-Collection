int timerFromServer;

byte mac[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xDD, 0x03 };
int ipA, ipB, ipC, ipD;

IPAddress server(192, 168, 88, 31); // local host wilden
// IPAddress server(192, 168, 88, 47); // local host zikri
// IPAddress server(180, 210, 205, 235); // main server

EthernetClient ethClient;
PubSubClient client(ethClient);

const char* mqtt_topic1 = "robotics/selena2";
const char* clientID = "machine_selena2";

long lastReconnectAttempt = 0;
int connectionAttempt = 0;

String userName;
String timeStamp;
String nilaiUser;

void callback(char* topic, byte* payload, unsigned int length) {
  String receivedTopic = topic;
  String payloadString;
  String gameCode;
  
  Serial.print("Msg subscribed [");
  Serial.print(topic);
  Serial.print("]");
  Serial.print(" : ");
  for (int i=0; i<length; i++) {
    Serial.print((char)payload[i]);
    payloadString += (char)payload[i];
  }
  Serial.println();

  for (int i = 0; i <= 2; i++) {
    gameCode += (char)payload[i];
  }
    
  if (payloadString.startsWith("username", 3))  // startsWith() at an offset position, 3 berarti setelah SL_
  {
    userName = "";
    int firstDelimiter = payloadString.lastIndexOf("=");
    int lastDelimiter = payloadString.lastIndexOf(",");
    for (int i=firstDelimiter+1; i<lastDelimiter; i++) {
      userName += (char)payload[i];
    }
    Serial.println(userName);
  }
  if (payloadString.startsWith("timestamp", 3))  // startsWith() at an offset position, 3 berarti setelah SL_
  {
    timeStamp = "";
    int firstDelimiter = payloadString.lastIndexOf("=");
    int lastDelimiter = payloadString.lastIndexOf(",");
    for (int i=firstDelimiter+1; i<lastDelimiter; i++) {
      timeStamp += (char)payload[i];
    }
    Serial.println(timeStamp);
  }
  
  // if(receivedTopic == mqtt_topic1){
  //   if(gameCode == "SL_"){
  //     if((char)payload[3] == 't' && length <= 6){
  //       String receivedPayload;
  //       for (int i = 4; i < length; i++) {
  //         receivedPayload += (char)payload[i];
  //       }
  //       timerFromServer = receivedPayload.toInt() + 1;
  //     }
  //     if((char)payload[3] == 'c'){
  //       ballExistCheckStatus = true;
  //       start_CD.start(timerFromServer);
  //       Serial.print("Start Remaining: ");
  //       Serial.println(start_CD.remaining());
        
  //       Serial.print("Ready???");
  //       digitalWrite(ledPin, HIGH);  // Led Button Nyala

  //     }
  //     if((char)payload[3] == 's'){
  //       Serial.println("Start");
  //       startButtonStatus = true;
  //     }
  //   }
  // }
}

boolean reconnect() {
  if (client.connect(clientID)) {
    Serial.println("Connected to Mqtt Broker !!!");
    client.subscribe(mqtt_topic1);
  }
  return client.connected();
}

void Mqtt_Setup()
{
  client.setServer(server, 1883);
  client.setCallback(callback);

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Serial.println("Restart...!!!");
    delay(1000);
    ku_restart();
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // no point in carrying on, so do nothing forevermore:
    while (true) {
      // Serial.println("DO NOTHING FOREVER");
      delay(1);
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
  
  delay(1000);
  Serial.println("Mqtt config...Done");
}