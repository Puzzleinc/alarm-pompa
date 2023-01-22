#include <Arduino.h>
#include <Wire.h>
#include <CTBot.h>

#include "wificonnect.h"

/* Put your SSID & Password */
const char* ssid;  // Enter SSID here
const char* password;  //Enter Password here
const char* deviceName;

/* Init Telegram class */
CTBot myBot;
TBMessage msg;
String token = "5818046411:AAEv_uG0gr_Sn3eUncC5cMo3IkvBVsR73Pk";   // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
CTBotInlineKeyboard myKbd;   // reply keyboard object helper

/* Init CTBot query */
#define LIGHT_ON_CALLBACK  "ON1"  // callback data sent when "LIGHT ON" button is pressed
#define LIGHT_OFF_CALLBACK "OFF1" // callback data sent when "LIGHT OFF" button is pressed

/* ESP pin configuration */
// uint8_t conled = 4;
#define buzz 1
#define redled 3
#define greenled 0
#define blueled 2

// Define millis variable #1
const unsigned long dangerInterval = 1800000; // formula (x/60000) = 30 menit
const unsigned long warningInterval = 900000; // 15 menit
const unsigned long okInterval = 0;
unsigned long previousTime = 0;

void setup() {
	Serial.begin(115200);
	while (!Serial); // wait for serial port to connect. Needed for native USB

	// set the pin connected to the LED to act as output pin
	// pinMode(conled, OUTPUT);
	pinMode(buzz, OUTPUT);
	pinMode(redled, OUTPUT);
	pinMode(greenled, OUTPUT);
	pinMode(blueled, OUTPUT);

	//  Connecting to wifi -----------------------
	ssid = "Puzzle24";  // Enter SSID here
	password = "gzcmb94463";  // Enter Password here
	deviceName = "Telegram Bot"; // DHCP Hostname (useful for finding device for static lease)
	wificonnect(ssid, password, deviceName);

	Serial.println(WiFi.gatewayIP());

	//  Connecting to telegram -----------------------
	myBot.setTelegramToken(token);
	// check if all things are ok
	if (myBot.testConnection())
		Serial.println("\nTest connection Succes");
	else
		Serial.println("\nTest connection Failed");

	//  Creating Keyboard button class -----------------------
	myKbd.addButton("Lampu Nyala", LIGHT_ON_CALLBACK, CTBotKeyboardButtonQuery);
	myKbd.addButton("Lampu Mati", LIGHT_OFF_CALLBACK, CTBotKeyboardButtonQuery);
	myKbd.addRow();
	myKbd.addButton("Contact request", "https://github.com/shurillu/CTBot", CTBotKeyboardButtonURL);
}

void loop() {
	TBMessage msg;
	unsigned long currentTime = millis();
	uint8_t thisTime = currentTime / 60000;

	// 3 Relay switch
	String welcome = "Halo\n";
	welcome += "Ini adalah bot untuk app esp8266\n";
	welcome += "ketik /Keyboard untuk menampilkan menu\n";
	welcome += "ketik /Time untuk waktu timer\n\n";

	if(myBot.getNewMessage(msg)) {
		if(msg.messageType == CTBotMessageText) {
			if(msg.text.equalsIgnoreCase("/Start") || msg.text.equalsIgnoreCase("/Keyboard")) {
				myBot.sendMessage(msg.sender.id, welcome, myKbd);
			} else if (msg.text.equalsIgnoreCase("/Time")) {
				myBot.sendMessage(msg.sender.id, "Waktu berjalan: " + String(thisTime));
			} else {
				myBot.sendMessage(msg.sender.id, "Perintah tidak dikenal, coba ketik /Keyboard");
			}
		} else if (msg.messageType == CTBotMessageQuery) {
			if (msg.callbackQueryData.equals(LIGHT_ON_CALLBACK)) {
				// pushed "LIGHT ON" button...
				digitalWrite(redled, HIGH); // ...turn on the LED (inverted logic!)
				// terminate the callback with an alert message
				myBot.endQuery(msg.callbackQueryID, "Light on", true);
			} else if (msg.callbackQueryData.equals(LIGHT_OFF_CALLBACK)) {
				// pushed "LIGHT OFF" button...
				digitalWrite(redled , LOW); // ...turn off the LED (inverted logic!)
				// terminate the callback with a popup message
				myBot.endQuery(msg.callbackQueryID, "Light off", true);
			}
		}
	}

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