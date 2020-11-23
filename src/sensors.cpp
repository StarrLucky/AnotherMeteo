#include <iarduino_DHT.h>
#include <MQ2.h>
#include <sensors.h>


int MQ2_lpg, MQ2_co, MQ2_smoke;


int DHTt_max = -9999;


iarduino_DHT sensor(PIN_DHT11);
MQ2 mq2(PIN_MQ2);
/*

String DHT11Update() {
  switch(sensor.read()){    // читаем показания датчика
      case DHT_OK:               return ((String) "CEHCOP B KOMHATE: " + sensor.hum + "% - " + sensor.tem + "*C");  break;
      case DHT_ERROR_CHECKSUM:   return (         "CEHCOP B KOMHATE: HE PABEHCTBO KC");                     break;
      case DHT_ERROR_DATA:       return (         "CEHCOP B KOMHATE: OTBET HE COOTBETCTB. CEHCOPAM 'DHT'"); break;
      case DHT_ERROR_NO_REPLY:   return (         "CEHCOP B KOMHATE: HET OTBETA");                          break;
      default:                   return (         "CEHCOP B KOMHATE: ERROR");
      }
}
*/


void SensorsInit() {
  MQInit();

}

void MQInit( )
 {
  mq2.begin();
 }




void DHT11Update() {
  sensor.read();
  if (sensor.tem > DHTt_max) {
    DHTt_max = sensor.tem;

  }

}

String DHT11GetTemp() {
  return String(sensor.tem,0);
}
String DHT11GetHumidity()
{
  return String (sensor.hum,0);
}


String DHT11GetAll() {
  return "DHT11 Temperature:  " + String(sensor.tem) + " humidity: " + String(sensor.hum) ;
   
}

/*


String DHT11UpdateTemp() {
 switch(sensor.read()){
      case DHT_OK:              return ((String(sensor.tem,2)));  break;
     default:                    return (         "CEHCOP B KOMHATE: ERROR");
}
}
*/


// MQ2 Sensor 
void MQ2Update() 
{
  MQ2_lpg = mq2.readLPG();
  MQ2_co = mq2.readCO();
  MQ2_smoke = mq2.readSmoke();
}

String MQGetAll() {
   return "lpg " + String(MQ2_lpg) +  " co: " + String(MQ2_co) + " smoke: " + MQ2_smoke;
 }
String MQ2GetLPG()    { return String(MQ2_lpg);   }
String MQ2GetCO()     { return String(MQ2_co);    }
String MQ2GetSmoke()  { return String(MQ2_smoke); }



