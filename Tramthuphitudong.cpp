#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 3;

Servo barrierServo;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  barrierServo.attach(servoPin);
  barrierServo.write(0); // Đóng barrier ban đầu
}

long getDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  long distance = getDistanceCM();
  Serial.print("Khoang cach: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= 15) { // Xe tiến gần
    Serial.println("Xe phát hiện - Mở barrier");
    barrierServo.write(90); // Mở barrier
    delay(3000);            // Chờ 3 giây (giả lập xe đi qua)
    barrierServo.write(0);  // Đóng lại
    delay(1000);            // Chờ tránh rung servo
  }

  delay(200); // Đọc cảm biến định kỳ
}#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 3;

Servo barrierServo;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  barrierServo.attach(servoPin);
  barrierServo.write(0); // Đóng barrier ban đầu
}

long getDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  long distance = getDistanceCM();
  Serial.print("Khoang cach: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= 15) { // Xe tiến gần
    Serial.println("Xe phát hiện - Mở barrier");
    barrierServo.write(90); // Mở barrier
    delay(3000);            // Chờ 3 giây (giả lập xe đi qua)
    barrierServo.write(0);  // Đóng lại
    delay(1000);            // Chờ tránh rung servo
  }

  delay(200); // Đọc cảm biến định kỳ
}