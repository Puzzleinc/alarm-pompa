#ifndef gettimesetting_h

#define gettimesetting_h
#include "Arduino.h"
#include <ArduinoJson.h>
#include <LittleFS.h>

// the #include statement and code go here...

// Initialize rtc variable and tell sketch to use it on every links
void getTimesetting(unsigned long &warningInterval, unsigned long &dangerInterval);

#endif