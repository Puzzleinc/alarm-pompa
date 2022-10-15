#include <Arduino.h>
#include <Wire.h>
#include <LittleFS.h>

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
void getTimehistory(AsyncWebServerRequest *request);

// Define millis variable #1 ------------------------
const unsigned long dangerInterval = 1800000; // 30 menit
const unsigned long warningInterval =  900000; // 15 menit
const unsigned long okInterval = 0;
unsigned long previousTime = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for native USB

  /*  Common cathode led RGB */
  pinMode(buzz, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);

  //  Connecting to wifi -----------------------
  ssid = "Puzzle24";  // Enter SSID here
  password = "gzcmb94463";  // Enter Password here
  deviceName = "Sensor Pompa"; // DHCP Hostname (useful for finding device for static lease)
  wificonnect(ssid, password, deviceName);

  Serial.println(WiFi.gatewayIP());

    //  Creating handle request from client -----------------------
  server.on("/", HTTP_ANY, handleRequest);
  server.on("/history", HTTP_ANY, getTimehistory);
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

void getTimehistory(AsyncWebServerRequest *request) {
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
