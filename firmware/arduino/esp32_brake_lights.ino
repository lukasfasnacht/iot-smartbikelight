#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

const int ledPin1 = 2;
const int ledPin2 = 25;
const int ledPin3 = 26;
float prevAccelZ = 0;
const float BRAKE_THRESHOLD = -2.0; 

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);

  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW);
  pinMode(ledPin3, OUTPUT);
  digitalWrite(ledPin3, LOW);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) delay(10);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(1000);
  Serial.println("MPU6050 ready!");
}

void loop() {
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  float accelZ = accel.acceleration.z;
  float deltaZ = accelZ - prevAccelZ;

  Serial.print("Accel Z: ");
  Serial.print(accelZ);
  Serial.print("  ΔZ: ");
  Serial.println(deltaZ);

  if (deltaZ < BRAKE_THRESHOLD) {
    Serial.println("Braking detected");
    blinkLED();
  }

  prevAccelZ = accelZ;
  delay(100);
}

void blinkLED() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    delay(150);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    delay(150);
  }
}
