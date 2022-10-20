#include <Arduino.h>
#include <Wire.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#include "wificonnect.h"

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define buzz 1
#define redled 3
#define greenled 2
#define blueled 0

/* Put your SSID & Password */
const char* ssid;  // Enter SSID here
const char* password;  //Enter Password here
const char* deviceName;

// Initialize server
AsyncWebServer server(80);
// Make variable prototype -----------------------
void handleRequest(AsyncWebServerRequest *request);
void getTimesetting(AsyncWebServerRequest *request);

// Define millis variable #1 ------------------------
const unsigned long dangerInterval = 1800000; // 30 menit
const unsigned long warningInterval =  900000; // 15 menit
const unsigned long okInterval = 0;
unsigned long previousTime = 0;

void setup() {
  // Initialize Serial port and I2C pin -----------------------
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for native USB

  // Initialize peripehalps pin -----------------------
  /*  Common cathode led RGB */
  pinMode(buzz, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);

  // Initialize filesystem -----------------------
  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  //  Connecting to wifi -----------------------
  ssid = "Puzzle24";  // Enter SSID here
  password = "gzcmb94463";  // Enter Password here
  deviceName = "Sensor Pompa"; // DHCP Hostname (useful for finding device for static lease)
  wificonnect(ssid, password, deviceName);

  server.on("/post", HTTP_POST,[](AsyncWebServerRequest * request){},NULL,[](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {

    String json = "";
    for (size_t i = 0; i < len; i++) {
      json += (char)data[i]; //binary strean to char array
    }

    File this_file = LittleFS.open("/config.json", "w");
    if (!this_file) { // failed to open the file, return false
      const char* openfail = "Failed to open file for reading";
      request->send(200, "text/plain", openfail);
      return;
    }
    int bytesWritten = this_file.print(json);

    if (bytesWritten == 0) { // write failed
      const char *writefail = "Gagal menulis data";
      request->send(200, "text/plain", writefail);
      return;
    }

    const char *writedone = "Berhasil menulis data, resetting device..";
    request->send(200, "text/plain", writedone);
    this_file.close();

    delay(2000);
    //ESP.restart(); //ESP.reset();    
  });

    //  Creating handle request from client -----------------------
  server.on("/", HTTP_ANY, handleRequest);
  server.on("/setting", HTTP_ANY, getTimesetting);
  server.begin();
}

void loop() {
  // Millis Function #1
  unsigned long currentTime = millis();

  if (currentTime >= dangerInterval) {
    /* Event code */
    digitalWrite(buzz, HIGH);
    delay(500);
    digitalWrite(buzz, LOW);
    delay(500);
    digitalWrite(greenled, LOW);
    digitalWrite(redled, HIGH);
    digitalWrite(blueled, LOW);
  } else if (currentTime >= warningInterval && dangerInterval) {
    digitalWrite(greenled, HIGH);
    digitalWrite(redled, LOW);
    digitalWrite(blueled, LOW);
  } else {
    digitalWrite(greenled, LOW);
    digitalWrite(redled, LOW);
    digitalWrite(blueled, HIGH);
  }
}

void handleRequest(AsyncWebServerRequest *request){
  unsigned long thisTime = millis() / 60000;
  request->send(200, "text/plain", "Waktu berjalan = " + String(thisTime) + " menit");
}

void getTimesetting(AsyncWebServerRequest *request) {
    String result = "";
    File file = LittleFS.open("/data.json", "r");

    if(!file){
    // Serial.println("Failed to open file for reading");
    request->send(200, "text/plain", "File history data tidak ditemukan");
    return;
    }

    while (file.available()) {
        result += (char)file.read();
    }
    file.close();

    request->send(200, "text/plain", "History waktu = " + result);
}
