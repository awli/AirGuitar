 //for some reason, this circuit tests if you are touching it!
 
 const int interface = 15;

void setup() {
  Serial.begin(9600);
}

void loop() {
  pinMode(interface, OUTPUT);
  digitalWrite(interface, HIGH);
  delay(50);
  pinMode(interface, INPUT);
  int sensorValues[50] = {};
  int sum = 0;
  for ( int i = 0; i < 50; i++) {
    int sensorValue = analogRead(interface);
    sensorValues[i] = sensorValue;
    sum += sensorValue;
    delay(1);
  }
  values
  Serial.println(sum);
}
