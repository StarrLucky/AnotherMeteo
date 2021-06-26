#include <Arduino.h>
#include <Strings.h>
#include <narodmonitor.h>
#include <device.h>
#include <mqtt.h>
#include <ESP8266mDNS.h>


// setting devices that will be connected on corresponding pins
device dht11 = device(DEVICE_DHT11, 16);
device dht112 = device(DEVICE_DHT11, 4);
device mq1 = device(DEVICE_MQ2, A0);

// Router APs
const char * ssid = "AP";
const char * pass = "password";
const char * routerIP = "192.168.0.1";

WiFiClient wificlient;                    // wifi client


unsigned long time1 = 0, timeNarodmonCnt , lastUIupdate = 9999, lastcheck = 9999, timeNarodmonLastCheck = 1000;

void setup() 
{     Serial.begin(9600);
      WiFi.begin(ssid, pass);
      Serial.println("Local IP: ");
      delay(5000);
      Serial.println(WiFi.localIP());
      if (!wificlient.connect(routerIP, 80)) {Serial.println("Connection failed"); }
      mqttSetup();
      Serial.println("Setup success.");
}

void loop() 
{
// updating  sensors data
      delay(10000);
      dht11.update();
      dht112.update();
      mq1.update();
//////////////////////////

// Showing data in serial:
      Serial.println("=========");
      Serial.println("Temp1 :" + String(dht11.primaryValue));
      Serial.println("Humidity1 :" + String(dht11.secondaryValue));
      Serial.println("Temp2 :" + String(dht112.primaryValue));
      Serial.println("Humidity1 :" + String(dht112.secondaryValue));
      Serial.println("CO :" + String(mq1.primaryValue));
      Serial.println("SMOKE :" + String(mq1.secondaryValue));

      time1= timeNarodmonCnt = millis();
      if (time1 > (lastcheck + 10000))
      {        
            lastcheck = millis();
      }
//    Sending to NarodMonitor every 5 min
      if (timeNarodmonCnt>timeNarodmonLastCheck+300000) 
      {
            Serial.println ( SendToNarodmon("14-F6-D8-D8-99-F6", String(dht11.primaryValue)));
            timeNarodmonLastCheck = millis();
      }

// sending to MQTT broker
     mqttLoop();
     mqttPublish(TOPIC_TEMPERATURE, dht11.primaryValue);
     mqttPublish(TOPIC_HUMIDITY, dht11.secondaryValue);
     mqttPublish(TOPIC_MQ_CO, mq1.primaryValue);
     mqttPublish(TOPIC_MQ_SMOKE, mq1.secondaryValue);


}

