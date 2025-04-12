#include <SimpleKalmanFilter.h>
SimpleKalmanFilter bo_loc(2, 2, 0.001);
// Khai báo các chân kết nối
const int mq2Pin = A0;
const int buzzerPin = 9;
const int relayPin = 12;
// Giá trị ngưỡng cho mức khí độc
int smokeThreshold = 350;

void setup() {
  // Khởi tạo cổng Serial
  Serial.begin(9600);

  // Khởi tạo chân kết nối cho các thiết bị
  pinMode(mq2Pin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Đọc giá trị từ cảm biến MQ2
  int smoke = analogRead(mq2Pin);
  smoke = bo_loc.updateEstimate(smoke);
  // In giá trị lên Serial Monitor để theo dõi
 // Serial.print("Smoke:300 ");
  Serial.println(smoke);

  // Kiểm tra nếu giá trị khí độc vượt quá ngưỡng
  if (smoke > smokeThreshold) {
    digitalWrite(buzzerPin, HIGH);  // Kích hoạt còi
    digitalWrite(relayPin, HIGH);
  }
  else {
    digitalWrite(buzzerPin, LOW);  // Tắt còi
    digitalWrite(relayPin, LOW);  // Tắt quạt
  }
}