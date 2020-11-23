#ifndef NARODMONITOR_H
#define NARODMONITOR_H
#include <Strings.h>

#define NARODMONITOR_POSTING_INTERVAL  30000 // интервал между отправками данных в миллисекундах (5 минут)
#define HOSTNAME 14-F6-D8-D8-99-F6 //имя железки - выглядит как ESPAABBCCDDEEFF т.е. ESP+mac адрес.

unsigned long lastConnectionTime = 0;
int NumberOfDevices; //сколько датчиков найдем.

String SendToNarodmon(String hostname, String value);


#endif