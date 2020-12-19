#ifndef MQTT_H
#define MQTT_H


#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_PORT   1883
#define mqtt_user "Username"
#define mqtt_password "password"

// topics: 
 #define TOPIC_HUMIDITY        "starrlucky/humidity"
 #define TOPIC_TEMPERATURE     "starrlucky/temperature"     
 #define TOPIC_MQ_LPG          "starrlucky/mq_lpg"     
 #define TOPIC_MQ_SMOKE        "starrlucky/mq_smoke" 
 #define TOPIC_MQ_CO           "starrlucky/mq_co" 







void mqttReconnect() ;
void mqttSetup() ;
void mqttLoop();
void mqttPublish(const char* topic, const char* payload);
void mqttPublish(String topic, int payload);
void mqttPublish(String topic, String payload);

#endif

