#ifndef wificonnect_h

#define wificonnect_h
#include "Arduino.h"
#include <ESP8266WiFi.h>

// the #include statement and code go here...

void wificonnect(const char* ssid, const char* password, const char* deviceName);

#endif