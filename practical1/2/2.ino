int ledPin = 3;
int buttonPin = 9;
int buttonStatus = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT); // Button in input device
  Serial.println("Hello Arduino!!!");
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonStatus = digitalRead(buttonPin);
  if (buttonStatus == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
