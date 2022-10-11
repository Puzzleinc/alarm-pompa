#include <Arduino.h>
#define buzz 1
#define redled 3
#define greenled 2
#define blueled 0

// Define millis variable #1
const unsigned long dangerInterval = 30000; // 30 menit
const unsigned long warningInterval = 20000; // 20 menit
const unsigned long okInterval = 0;
unsigned long previousTime = 0;

void setup() {
  // put your setup code here, to run once:

 /*  Common cathode led RGB */
  Serial.begin(115200);
  // pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);
  digitalWrite(blueled, HIGH);
  Serial.println("Hello, ESP01!");
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
