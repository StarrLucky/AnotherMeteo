#ifndef MQTT1_H
#define MQTT1_H


#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_PORT   1883
#define mqtt_user "Username"
#define mqtt_password "password"

// topics: 

#define humidity_topic "starrlucky/humidity"
#define temperature_topic "starrlucky/temperature"      





void mqttReconnect() ;
void mqttSetup() ;
void mqttLoop();
void mqttPublish(const char* topic, const char* payload);
void mqttPublish(String topic, int payload);
void mqttPublish(String topic, String payload);

#endif

