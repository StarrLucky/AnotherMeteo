
#include <Arduino.h>
#include <MQ2.h>
#include <iarduino_DHT.h>


#define DEVICE_DHT11 1
#define DEVICE_MQ2   2

class device
{
private:
    iarduino_DHT sensorDHT11 = iarduino_DHT();
    MQ2 sensorMQ = MQ2();
    void MinMax(int val)  {  
        if (val > max) {  max = val; }
        if (val < min)  { min = val; }
    }

public:
    int type;
    int max, min;
    int primaryValue;
    int secondaryValue;
    device(int type, int pin);
    ~device();
    void update();
};

device::~device()
{
}

device::device(int type, int pin) {
    this->type = type;
    if (type == DEVICE_DHT11)   { sensorDHT11.setPin(pin);   }
    if (type == DEVICE_MQ2)     { sensorMQ.setPin(pin);      }
}

void device::update() {
    
    switch (type)
    {
    case DEVICE_DHT11:
        sensorDHT11.read();
        MinMax(sensorDHT11.tem);
        primaryValue = sensorDHT11.tem;
        secondaryValue = sensorDHT11.hum;
        break;
    case DEVICE_MQ2:
        sensorMQ.read(true);
        primaryValue = sensorMQ.getCO();
        secondaryValue = sensorMQ.getSmoke();
    default:
        break;
    }

}

