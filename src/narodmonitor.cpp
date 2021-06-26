#include <ESP8266WiFi.h>        
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <wireless.h>




String SendToNarodmon(String hostname, String value) { // Собственно формирование пакета и отправка.
    WiFiClient client;

    if (!client.connect("192.168.0.1", 80)) {
        Serial.println("connection failed"); }
    String buf;
    String line;
    buf = "#" + hostname + "\r\n"; // заголовок
    buf = buf + "#";
    buf = buf + "DHT_11"; // имя датчика
    buf = buf + "#" + value + "\r\n"; //и температура
    buf = buf + "##\r\n"; // закрываем пакет

      if (!client.connect("narodmon.ru", 8283)) { // попытка подключения
      Serial.println("connection failed");
      return "Connection failed"; // не удалось;
    } else
    {
      client.print(buf); // и отправляем данные
      while (client.available()) {
        String line = client.readStringUntil('\r'); // если что-то в ответ будет - все в Serial
        Serial.print(line);      }
    }
      return line;
  }