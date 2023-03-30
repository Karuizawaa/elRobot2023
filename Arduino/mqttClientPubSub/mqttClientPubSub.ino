#include "Ethernet.h"
#include "ArduinoMqttClient.h"

#define port 1883

EthernetClient eth;
MqttClient mqtt(eth);


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 5);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress myDns(8, 8, 8, 8);

const char broker[] = "192.168.0.3";
char topic[] = "arduino/eak";

const long interval = 1000;
unsigned long previousMillis = 0;

int count ;
void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  mqtt.setId("roda1");
  // put your setup code here, to run once:
  if (!mqtt.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqtt.connectError());
    while (1);
  }
  Serial.println("berhasil kehubung");
}

void loop() {
  mqtt.poll();
  unsigned long currentMillis = millis();
  int messageSize = mqtt.parseMessage();
  // put your main code here, to run repeatedly:
  if (currentMillis - previousMillis >= interval) {
      // save the last time a message was sent
      previousMillis = currentMillis;
  
      Serial.print("Sending message to topic: ");
      Serial.println(topic);
      Serial.print("hello ");
      Serial.println(count);
  
      // send message, the Print interface can be used to set the message contents
      mqtt.beginMessage(topic);
      mqtt.print("hello ");
      mqtt.print(count);
      mqtt.endMessage();
  
      Serial.println();
  
      count++;
    }
    
}
