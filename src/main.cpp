#include <Arduino.h>
#include <Wire.h>

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

// Initialize server
AsyncWebServer server(80);
// Make variable prototype
void handleRequest(AsyncWebServerRequest *request);

// Define millis variable #1
const unsigned long dangerInterval = 30000; // 30 menit
const unsigned long warningInterval = 20000; // 20 menit
const unsigned long okInterval = 0;
unsigned long previousTime = 0;

void setup() {
 /*  Common cathode led RGB */
  Serial.begin(115200);

  pinMode(buzz, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);

  //  Connecting to wifi -----------------------
  ssid = "Puzzle24";  // Enter SSID here
  password = "gzcmb94463";  //Enter Password here
  wificonnect(ssid, password);

    //  Creating handle request from client -----------------------
  server.on("/", HTTP_ANY, handleRequest);
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
  // unsigned long thisTime = millis();
  // String result = "";

  // while (thisTime) {
  //     result += (char)thisTime;
  // }

  request->send(200, "text/plain", "Waktu saat ini : ???");
}
