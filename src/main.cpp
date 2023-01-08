#include <Arduino.h>
#include <Wire.h>

#include "wificonnect.h"

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define buzz 1
#define redled 3
#define greenled 0
#define blueled 2

/* Put your SSID & Password */
const char* ssid;  // Enter SSID here
const char* password;  //Enter Password here
const char* deviceName;

// Initialize server
AsyncWebServer server(80);
// Make variable prototype
void handleRequest(AsyncWebServerRequest *request);

// Define millis variable #1
const unsigned long dangerInterval = 1800000; // formula (x/60000) = 30 menit
const unsigned long warningInterval = 900000; // 15 menit
const unsigned long okInterval = 0;
unsigned long previousTime = 0;
unsigned long currentTime = millis();

void setup() {
 /*  Common cathode led RGB */
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for native USB

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
  server.begin();
}

void loop() {
  // Millis Function #1
  if (currentTime >= dangerInterval) {
    /* Event code */
    digitalWrite(buzz, HIGH);
    delay(500);
    digitalWrite(buzz, LOW);
    delay(500);
    digitalWrite(greenled, LOW);
    digitalWrite(redled, HIGH);
    digitalWrite(blueled, LOW);
  } else if (currentTime >= warningInterval) {
    digitalWrite(greenled, LOW);
    digitalWrite(redled, LOW);
    digitalWrite(blueled, HIGH);
  } else {
    digitalWrite(greenled, HIGH);
    digitalWrite(redled, LOW);
    digitalWrite(blueled, LOW);
  }
}

void handleRequest(AsyncWebServerRequest *request){
  int thisTime = currentTime / 60000;
  request->send(200, "text/plain", "Waktu berjalan = " + String(thisTime) + " menit");
}
