#include <Servo.h>

const int trigPin = 2;    // Chân Trig của HC-SR04
const int echoPin = 3;    // Chân Echo của HC-SR04
Servo radarServo;         // Đối tượng servo để điều khiển servo

long duration;
int distance;
int servoPos = 0;  // Vị trí góc của servo (0 - 180)

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  radarServo.attach(9);  // Servo gắn vào chân D9
}

void loop() {
  // Quét radar nhanh hơn với tốc độ cao hơn
  for (servoPos = 0; servoPos <= 180; servoPos++) {
    radarServo.write(servoPos);  // Di chuyển servo tới góc hiện tại
    delay(5);  // Giảm thời gian delay để tăng tốc độ quay của servo

    // Tính khoảng cách bằng cảm biến HC-SR04
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.0344 / 2;  // Tính khoảng cách (cm)

    // In ra khoảng cách
    Serial.print("Góc: ");
    Serial.print(servoPos);
    Serial.print("° - Khoảng cách: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  // Quét ngược lại từ 180° về 0°
  for (servoPos = 180; servoPos >= 0; servoPos--) {
    radarServo.write(servoPos);  // Di chuyển servo tới góc hiện tại
    delay(5);  // Giảm thời gian delay để tăng tốc độ quay của servo

    // Tính khoảng cách bằng cảm biến HC-SR04
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.0344 / 2;  // Tính khoảng cách (cm)

    // In ra khoảng cách
    Serial.print("Góc: ");
    Serial.print(servoPos);
    Serial.print("° - Khoảng cách: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
}
