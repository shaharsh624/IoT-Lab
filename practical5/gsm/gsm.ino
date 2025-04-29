#include <HardwareSerial.h>

HardwareSerial mySerial(1); // Use UART1 for the serial communication

// Pins for UART1
#define RXD2 16
#define TXD2 14

void setup() {
  // Begin serial communication with the GSM module
  mySerial.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.begin(115200); // Serial monitor for debugging
  
  delay(1000); // Give time for GSM module to initialize
  
  // Check if the module is ready
  mySerial.println("AT");
  delay(1000);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  
  // Send SMS
  sendSMS("1234567890", "Hello from ESP32!");
}

void loop() {
  // Keep reading from the GSM module
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }

  // Keep reading from the Serial Monitor
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

void sendSMS(const char* number, const char* message) {
  mySerial.println("AT+CMGF=1");  // Set SMS mode to text
  delay(1000);
  
  mySerial.print("AT+CMGS=\"");
  mySerial.print(number);
  mySerial.println("\"");
  delay(1000);
  
  mySerial.print(message);
  delay(1000);
  
  mySerial.write(26); // ASCII code for Ctrl+Z to send the SMS
  delay(1000);
  
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}
