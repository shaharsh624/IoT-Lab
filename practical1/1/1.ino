int ledPin = 3;  // Write pin of output device

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  Serial.println("Hello Arduino!!!");c:\Users\harsh\OneDrive - pdpu.ac.in\HARSH\_PDEU\SEM 7\Internet of Things\IoT Lab\practical1\2\2.ino
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH);
  Serial.println("LED ON");
  delay(500);
  digitalWrite(ledPin, LOW);
  Serial.println("LED OFF");
  delay(500);
}
