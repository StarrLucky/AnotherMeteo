#include <Arduino.h>
#include <wireless.h>
#include <wlan.h>
#include <narodmonitor.h>
#include <device.h>

// "I got the urge to code again"  - THE DEVIL ALL THE TIME,  2020.

// List of supported devices. 
#define DEVICE_DHT11 1
#define DEVICE_MQ2   2


bool diag = true;

// Router APs
String ssid [] = {"ssid","ssid2"};
String password [] = {"password", "password"};
int ssidnum = 2;
unsigned long time1 = 0, time2 , lastUIupdate = 9999, lastcheck = 9999, lastcheckNarod = 1000;

W_LAN RouterAP = W_LAN();

// setting devices that will be connected on corresponding pins
device dht11 = device(DEVICE_DHT11, 5);
device dht112 = device(DEVICE_DHT11, 2);

void setup() {
      if (diag) { Serial.begin(9600); Serial.println("Serial Ready. Setup routine");}
      W_LAN();
      RouterAP.SetSSIDs(ssidnum, ssid, password);
      RouterAP.Connect();
      Serial.println("Local IP: ");
      Serial.println(WiFi.localIP());
      Serial.println("Local IP: ");

      WiFiClient client;
      if (!client.connect("192.168.1.1", 80)) {Serial.println("connection failed"); }
      if (diag) { Serial.println("Setup success \n");}
      
      }

void loop() 
{
      delay(5000);
      dht11.update();
      dht112.update();
      Serial.println("=========");
      Serial.println("Temp1 :" + String(dht11.primaryValue));
      Serial.println("Temp2 :" + String(dht112.primaryValue));

//    checking if wifi connection is ok for every 10 sec
      time1= time2 = millis();
      
      if (time1 > (lastcheck + 10000))
{
      RouterAP.WLanControl(RouterAP);        
      lastcheck = millis();
      }

//    Sending to NarodMonitor Every 5 min
if (time2>lastcheckNarod+300000) {
      Serial.println ( SendToNarodmon("14-F6-D8-D8-99-F6", String(dht11.primaryValue)));
      lastcheckNarod = millis();
      }
}
