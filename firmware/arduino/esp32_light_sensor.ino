const int trigPin = 27;
const int echoPin = 14;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("HC-SR04 Distance Test");
}

void loop() {
  // Clear TRIG
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send 10µs pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  long duration = pulseIn(echoPin, HIGH, 30000);  // 30ms = max 5m range

  if (duration == 0) {
    Serial.println("⚠️ No echo received.");
  } else {
    int distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(500);
}
