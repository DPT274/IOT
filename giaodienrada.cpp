import processing.serial.*;

Serial myPort;
String data;
int angle = 0;
int distance = 0;

void setup() {
  size(800, 600);
  println(Serial.list()); // In danh sách cổng COM
  myPort = new Serial(this, Serial.list()[0], 9600); // Chọn COM phù hợp nếu cần
  myPort.bufferUntil('\n');
}

void draw() {
  background(0);
  translate(width / 2, height);  // Gốc tọa độ ở đáy giữa

  stroke(0, 255, 0);
  noFill();

  // Vẽ các vòng radar
  for (int r = 100; r <= 400; r += 100) {
    arc(0, 0, r * 2, r * 2, PI, TWO_PI);
  }

  // Vẽ vạch chia và số độ
  for (int a = 0; a <= 180; a += 10) {
    float x = cos(radians(a)) * 400;
    float y = -sin(radians(a)) * 400;
    line(0, 0, x, y);

    if (a % 30 == 0) {
      float tx = cos(radians(a)) * 430;
      float ty = -sin(radians(a)) * 430;
      fill(0, 255, 0);
      textSize(12);
      textAlign(CENTER, CENTER);
      text(a + "°", tx, ty);
    }
  }

  // Tính vị trí điểm đo từ dữ liệu nhận được
  float x = cos(radians(angle)) * distance * 2;
  float y = -sin(radians(angle)) * distance * 2;

  // Vẽ tia quét và chấm đo
  stroke(255, 0, 0);
  line(0, 0, x, y);
  fill(255, 0, 0);
  ellipse(x, y, 8, 8);

  // Hiển thị góc và khoảng cách
  fill(0, 255, 0);
  textSize(16);
  textAlign(LEFT, CENTER);
  text("Góc: " + angle + "°", -width / 2 + 20, -height + 40);
  text("Khoảng cách: " + distance + " cm", -width / 2 + 20, -height + 70);
}

void serialEvent(Serial p) {
  data = trim(p.readStringUntil('\n'));
  if (data != null && data.contains(",")) {
    String[] parts = split(data, ',');
    if (parts.length == 2) {
      angle = int(parts[0]);
      distance = int(parts[1]);

      // Giới hạn khoảng cách hiển thị (tùy bạn)
      if (distance > 200) distance = 200;
    }
  }
}