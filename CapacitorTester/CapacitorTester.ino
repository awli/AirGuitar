 const int interface = 15;

void setup() {
  Serial.begin(9600);
}

void loop() {
  pinMode(interface, OUTPUT);
  digitalWrite(interface, HIGH);
  delay(500);
  pinMode(interface, INPUT);
  int sensorValues[5] = {};
  for ( int i = 0; i < 500; i++) {
    int sensorValue = analogRead(interface);
    Serial.print(sensorValue);
    Serial.print(", ");
    delay(1);
  }
  Serial.println();
}
