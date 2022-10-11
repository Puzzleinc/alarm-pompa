#include <Arduino.h>
#include "wificonnect.h"

void wificonnect(const char* ssid, const char* password) {
    
    // Mengatur WiFi -----------------------
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);  // Mode Station
    WiFi.begin(ssid, password); // Mencocokan SSID dan Password
        
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }

    Serial.println("WiFi connected");  
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}