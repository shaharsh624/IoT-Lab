class LEDBlinker {
  private:
    int pin;

  public:
    // Constructor to initialize the pin
    LEDBlinker(int p) {
      pin = p;
      pinMode(pin, OUTPUT); // Set the pin mode
    }

    // Method to turn the LED on
    void turnOn() {
      digitalWrite(pin, HIGH);
    }

    // Method to turn the LED off
    void turnOff() {
      digitalWrite(pin, LOW);
    }

    // Method to blink the LED with a specified delay
    void blink(int delayTime) {
      turnOn();
      delay(delayTime);
      turnOff();
      delay(delayTime);
    }
};

LEDBlinker led(23); // Create an object of LEDBlinker with the LED pin set to 32

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
}

void loop() {
  led.blink(500); // Blink the LED with a 500ms delay
}
