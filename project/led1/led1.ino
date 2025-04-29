// BLYNK SETUP
#define BLYNK_TEMPLATE_ID "TMPL3T-ACrkDD"
#define BLYNK_TEMPLATE_NAME "IOTPROJECT2"
#define BLYNK_AUTH_TOKEN "oT434sslDvn61k1InkXgrCVYjd17c35S"
#define vpinLED V0
#define vpinBuzzer V1
#define vpinLDR V3
#define vpinWater V4

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "InternetByHarsh";
char pass[] = "helloharsh";

// Pin Definitions
const int ledPin = 13;
const int buzzerPin = 12;
const int ldrPin = 34;
const int waterPin = 35;

int ldrValue;
int scaledLdrValue;
int waterLevel;
int ledState = 0;
int buzzerState = 0;

BlynkTimer timer;

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

// LDR Sensor
void readLDR() {
  ldrValue = analogRead(ldrPin);
  scaledLdrValue = map(ldrValue, 0, 225, 100, 0);

  Blynk.virtualWrite(vpinLDR, scaledLdrValue);

  Serial.print("LDR Value: ");
  Serial.println(scaledLdrValue);

  // If scaled LDR value is below 20, turn on LED automatically
  if (scaledLdrValue < 20) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Low light detected: LED turned ON automatically.");
  } else if (!ledState) {
    digitalWrite(ledPin, LOW);
  }
}

// Water Level Sensor
void readWaterSensor() {
  waterLevel = analogRead(waterPin);

  Blynk.virtualWrite(vpinWater, waterLevel);

  Serial.print("Water Level: ");
  Serial.println(waterLevel);

  // If water level exceeds 1000, blink LED and buzzer
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

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(waterPin, INPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, readLDR);
  timer.setInterval(1000L, readWaterSensor);

  Serial.println("Welcome to our Home Automation System");
}

void loop() {
  Blynk.run();
  timer.run();
}

