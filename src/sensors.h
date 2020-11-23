#ifndef SENSORS_H
#define SENSORS_H
#include <Strings.h>

#define PIN_DHT11   5
#define PIN_MQ2     (A0)



void MQInit( );
void MQ2Update();
void SensorsInit();


void DHT11Update();
String DHT11GetAll();
String DHT11GetTemp();
String DHT11GetHumidity();

String MQGetAll();
String MQ2GetLPG();
String MQ2GetCO();
String MQ2GetSmoke();







#endif
