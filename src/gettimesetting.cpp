#include <Arduino.h>
#include "gettimesetting.h"

void getTimesetting(unsigned long &warningInterval, unsigned long &dangerInterval) {
    // Get data from SPIFFS and send it to global variable

    String inputWaktu = "";
    File file = LittleFS.open("time.csv", "r");

    if(!file){
    Serial.println("Failed to open file for reading");
    return;
    }

    while (file.available()) {
        inputWaktu += (char)file.read();
    }

    int pembatas = inputWaktu.indexOf("#");
    warningInterval = inputWaktu.substring(0, pembatas).toInt() * 60000;
    dangerInterval = inputWaktu.substring(pembatas+1, inputWaktu.length()).toInt() * 60000;
    file.close();
}