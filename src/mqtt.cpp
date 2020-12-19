#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <mqtt.h>

WiFiClient espClient;
PubSubClient client(espClient);


unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;


void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if ((char)payload[0] == '1') {
  } else {
  }
}


void mqttReconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "AnotherMeteo-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqttSetup() {
  client.setServer(MQTT_SERVER,MQTT_PORT);
  client.setCallback(mqttCallback);
}

void mqttLoop() {

  if (!client.connected()) 
  {
    mqttReconnect();
  }
  client.loop();
}




void mqttPublish(const char* topic, const char* payload) 
{
  if (client.connected()) 
  {
    client.publish(topic, payload);
  }
  else if (!client.connected())
  {
    mqttReconnect();
  }
}

void mqttPublish(String topic, int payload) 
{
  mqttPublish(topic.c_str(), String(payload).c_str());
}

void mqttPublish(String topic, String payload)
{
  mqttPublish(topic.c_str(), payload.c_str());
}

