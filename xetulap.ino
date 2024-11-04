#include <AFMotor.h>
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(1,0);

// Khởi tạo 4 động cơ trên Motor Shield
AF_DCMotor motor1(1, MOTOR12_1KHZ); // Motor 1 được kết nối tại kênh M1
AF_DCMotor motor2(2, MOTOR12_1KHZ); // Motor 2 được kết nối tại kênh M2
AF_DCMotor motor3(3, MOTOR34_1KHZ); // Motor 3 được kết nối tại kênh M3
AF_DCMotor motor4(4, MOTOR34_1KHZ); // Motor 4 được kết nối tại kênh M4
int speed = 200;
char dieu_khien;
#define sensor_1  A0
#define sensor_2  A1
#define sensor_3  A4
#define sensor_4  A5


void bluetoooth(){
  if (bluetooth.available() > 0) {
    dieu_khien = bluetooth.read();
    Serial.print(dieu_khien);
    Stop(); // Dừng xe trước khi thực hiện lệnh mới

    switch (dieu_khien) {
      case 'F': // Tiến
        tien();
        break;
      case 'B': // Lùi
        lui();
        break;
      case 'L': // Rẽ trái
        trai();
        break;
      case 'R': // Rẽ phải
        phai();
        break;
    }
  }
}

void tien(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
}

void lui(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);

  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
}

void phai(){
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);

  motor1.setSpeed(100);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(100);
}

void trai(){
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);

  motor1.setSpeed(speed);
  motor2.setSpeed(100);
  motor3.setSpeed(100);
  motor4.setSpeed(speed);
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void follow_line(){
  bool DL, DR;
  if(analogRead(sensor_2) > 600) 
    DR = HIGH;
  else DR = LOW;

  if(analogRead(sensor_3) > 600) 
    DL = HIGH;
  else DL = LOW;

  if (DR == HIGH && DL == HIGH){
    tien();
  }

  if (DR == HIGH && DL == LOW){
    phai();
  }

  if (DR == LOW && DL == HIGH){
    trai();
  }

  if (DR == LOW && DL == LOW){
    Stop();
  }
}



void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(sensor_1, INPUT);
  pinMode(sensor_2, INPUT);
  pinMode(sensor_3, INPUT);
  pinMode(sensor_4, INPUT);
}

void loop() {
  //follow_line();
  // phai();
  //trai();
  // tien();
  // lui();
  // int S4 = analogRead(sensor_4);
  // Serial.println(S4);
}
