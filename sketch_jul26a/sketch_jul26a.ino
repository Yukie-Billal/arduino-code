int ledPin = 8;
int touchSensorPin = 7;
int lastState = LOW;
int currentState;

void setup() {
  Serial.begin(9600);
  pinMode(touchSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  currentState = digitalRead(touchSensorPin);

  if (lastState == LOW && currentState == HIGH) {
    Serial.println("The sensor is touched");
  }

  lastState = currentState;


  if (lastState == HIGH) {
    digitalWrite(ledPin, HIGH);
    delay(1500);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
