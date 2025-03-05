#include <SoftwareSerial.h>
SoftwareSerial sim800l(10, 9); // Kết nối SIM800L với pin (TX) và pin (RX)

int smokePin = A1; // Kết nối cảm biến MQ2 với chân A0
int buzzerPin = A0; // Kết nối còi báo động với chân 9
int relay = 12;
char phoneNumber[] = "0347050637"; // Số điện thoại cần gọi 0347050637

void setup() {
  pinMode(smokePin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(smokePin, INPUT_PULLUP);
  pinMode(relay, OUTPUT);
  pinMode(13, OUTPUT); // Chỉ để kiểm tra hoạt động
  digitalWrite(buzzerPin, HIGH); // Bật còi báo động
  digitalWrite(relay, HIGH); // Bật còi báo động
  Serial.begin(9600);
  sim800l.begin(9600);

  // Chờ khởi động của SIM800L
  delay(10000);
}

void loop() {
  int smokeValue = digitalRead(smokePin);
  Serial.println(smokeValue);
  if (smokeValue == 0) { // Điều kiện cảnh báo, bạn có thể điều chỉnh ngưỡng
    digitalWrite(buzzerPin, LOW); // Bật còi báo động
    digitalWrite(relay, LOW); // Bật còi báo động
    makeCall(); // Thực hiện cuộc gọi
    delay(5000); // Đợi 5 giây trước khi tiếp tục kiểm tra
  }
  digitalWrite(buzzerPin, HIGH); // Bật còi báo động
    digitalWrite(relay, HIGH); // Bật còi báo động
  delay(100); // Kiểm tra cảm biến MQ2 mỗi giây
}

void makeCall() {
  Serial.println("DANG GOI");
  sim800l.println("ATD" + String(phoneNumber) + ";"); // Gọi đến số điện thoại
  delay(20000); // Đợi 30 giây cho cuộc gọi (có thể điều chỉnh)
  sim800l.println("ATH"); // Kết thúc cuộc gọi
  Serial.println("DA GOI");
}
