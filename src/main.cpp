#include <Arduino.h>
#include <sensors.h>
#include <wireless.h>
#include <wlan.h>
#include <narodmonitor.h>
// StarrLucky, nov 2020  
// "P.S I got the urge to code again"  - THE DEVIL ALL THE TIME,  2020.
bool diag = true;

// Router APs
String ssid [] = {"StarrLucky","Lan_Indoor"};
String password [] = {"luckys322", "luckys322"};
int ssidnum = 2;
unsigned long time1 = 0, time2 , lastUIupdate = 9999, lastcheck = 9999, lastcheckNarod = 1000;

W_LAN RouterAP = W_LAN();



void setup() {
  if (diag) { Serial.begin(9600); Serial.println("Serial Ready. Setup routine");}
  SensorsInit();

  W_LAN();
  RouterAP.SetSSIDs(ssidnum, ssid, password);
  RouterAP.Connect();

  if (diag) { Serial.println("Setup success");}
  Serial.println("Local IP:");
  Serial.println(WiFi.localIP());


  WiFiClient client;
  if (!client.connect("192.168.1.1", 80)) {Serial.println("connection failed"); }

}

void loop() {

delay(5000);
DHT11Update();
MQ2Update();

Serial.println(DHT11GetAll());
Serial.println(MQGetAll());




//    // checking if wifi connection is ok for every 10 sec
      time1= time2 = millis();
      if (time1 > (lastcheck + 10000))
      {
        RouterAP.WLanControl(RouterAP);        
        lastcheck = millis();
      }
//    Sending to NarodMonitor Every 5 min
      if (time2>lastcheckNarod+300000) {
      Serial.println ( SendToNarodmon("14-F6-D8-D8-99-F6", DHT11GetTemp()));
      lastcheckNarod = millis();
}




}
