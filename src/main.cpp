#include <Arduino.h>
#include <Strings.h>
#include <wireless.h>
#include <narodmonitor.h>
#include <device.h>
#include <mqtt.h>


// Router APs
String ssid [] = {"ssid1","ssid2"};
String password [] = {"password1", "password2"};
int ssidnum = 2;

// setting devices that will be connected on corresponding pins
device dht11 = device(DEVICE_DHT11, 5);
device dht112 = device(DEVICE_DHT11, 4);
device mq1 = device(DEVICE_MQ2, A0);

W_LAN RouterAP = W_LAN();                 // access point handling

WiFiClient wificlient;                    // wifi client


bool diag = true;                         // Serial port diag messages

unsigned long time1 = 0, timeNarodmonCnt , lastUIupdate = 9999, lastcheck = 9999, timeNarodmonLastCheck = 1000;

void setup() {
      if (diag) { Serial.begin(9600); Serial.println("Serial Ready. Setup routine");}
      W_LAN();
      RouterAP.SetSSIDs(ssidnum, ssid, password);
      RouterAP.Connect();
           
      Serial.println("Local IP: ");
      Serial.println(WiFi.localIP());
      Serial.println("Local IP: ");
      
      if (!wificlient.connect("192.168.1.1", 80)) {Serial.println("connection failed"); }
      
      mqttSetup();

      if (diag) { Serial.println("Setup success \n");}       

      }



void loop() 
{

// updating  sensors data
      delay(10000);
      dht11.update();
      dht112.update();
      mq1.update();


// Showing data in serial:

      Serial.println("=========");
      Serial.println("Temp1 :" + String(dht11.primaryValue));
      Serial.println("Humidity1 :" + String(dht11.secondaryValue));
      Serial.println("Temp2 :" + String(dht112.primaryValue));
      Serial.println("Humidity1 :" + String(dht112.secondaryValue));
      Serial.println("CO :" + String(mq1.primaryValue));
      Serial.println("SMOKE :" + String(mq1.secondaryValue));



//    checking if wifi connection is ok for every 10 sec

      time1= timeNarodmonCnt = millis();
      
      if (time1 > (lastcheck + 10000))
      {
            RouterAP.WLanControl(RouterAP);        
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

