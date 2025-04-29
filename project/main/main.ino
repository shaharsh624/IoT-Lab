#define BLYNK_TEMPLATE_ID "TMPL3T-ACrkDD"
#define BLYNK_TEMPLATE_NAME "IOTPROJECT2"
#define BLYNK_AUTH_TOKEN "oT434sslDvn61k1InkXgrCVYjd17c35S"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "InternetByHarsh";
char pass[] = "helloharsh";

BlynkTimer timer;

// Pin Definitions
const int ledPin = 13;
const int buzzerPin = 12;
const int ldrPin = 34;
const int waterPin = 35;

// Blynk Virtual Pins
#define vpinLED V0
#define vpinBuzzer V1
#define vpinLDR V3
#define vpinWater V4

// Variables
int ldrValue;
int scaledLdrValue;
int waterLevel;
int ledState = 0;
int buzzerState = 0;

BLYNK_CONNECTED() {
  Blynk.syncVirtual(vpinLED);
  Blynk.syncVirtual(vpinBuzzer);
}

BLYNK_WRITE(vpinLED) {
  ledState = param.asInt();
  digitalWrite(ledPin, ledState ? HIGH : LOW);
  Serial.print("LED State: ");
  Serial.println(ledState ? "ON" : "OFF");
}

BLYNK_WRITE(vpinBuzzer) {
  buzzerState = param.asInt();
  digitalWrite(buzzerPin, buzzerState ? HIGH : LOW);
  Serial.print("Buzzer State: ");
  Serial.println(buzzerState ? "ON" : "OFF");
}

// Function to read LDR and scale the value
void readLDR() {
  ldrValue = analogRead(ldrPin);
  // Scale LDR value from 0-225 to 0-100 (inverted)
  scaledLdrValue = map(ldrValue, 0, 225, 100, 0);

  // Send scaled value to Blynk
  Blynk.virtualWrite(vpinLDR, scaledLdrValue);

  Serial.print("LDR Value: ");
  Serial.print(ldrValue);
  Serial.print("\tScaled LDR Value: ");
  Serial.println(scaledLdrValue);

  // If scaled LDR value is below 20, turn on LED automatically
  if (scaledLdrValue < 20) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Low light detected: LED turned ON automatically.");
  } else if (!ledState) {
    digitalWrite(ledPin, LOW);
  }
}

// Function to read Water Sensor and handle alerts
void readWaterSensor() {
  waterLevel = analogRead(waterPin);

  // Send water level to Blynk
  Blynk.virtualWrite(vpinWater, waterLevel);

  Serial.print("Water Level: ");
  Serial.println(waterLevel);

  // If water level exceeds 1000, blink LED and buzz
  if (waterLevel > 1000) {
    Serial.println("High water level detected: Blinking LED and buzzing.");
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(200);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize pins
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(waterPin, INPUT);

  // Set initial states
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);

  Blynk.begin(auth, ssid, pass);

  // Set timers to read sensors every second
  timer.setInterval(1000L, readLDR);
  timer.setInterval(1000L, readWaterSensor);

  Serial.println("ESP32 IoT Project Initialized with LDR and Water Sensor");
}

void loop() {
  Blynk.run();
  timer.run();
}