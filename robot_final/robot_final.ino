#include <Servo.h>
#include <Pixy2I2C.h>

Pixy2I2C pixy;
const int X_CENTER = 58;

int startX = pixy.line.vectors[0].m_x0;  // 라인의 시작점 x 좌표
int endX = pixy.line.vectors[0].m_x1;    // 라인의 끝점 x 좌표
int startY = pixy.line.vectors[0].m_y0;
int endY = pixy.line.vectors[0].m_y1;
int startXError = X_CENTER - startX;         // 라인의 시작점 x 오차 계산
int endXError = X_CENTER - endX;             // 라인의 끝점 x 오차 계산
int errorX = (startXError + endXError) / 2;  // 라인의 중앙 x 오차 계산
int errorxchange = startX - endX;            // 변화량 측정

#define echo1 34      // 왼쪽 초음파센서 Echo pin
#define trigger1 35   // 왼쪽 초음파센서 Trigger pin
#define servo_pin 99  // 나중에 넣어야 함


int result = 0;  // 원래 0, 로봇만 돌릴때 5로 수정

Servo servo;

int distance_L, distance_F, distance_R, distance;
int target = 6;  //기본 목적지는 A
int carry = 0;
const int wheelPins[16] = { 2, 3, 5, 4, 7, 6, 8, 9, 10, 11, 12, 13 };  //36,38
const int Enpints[4] = { A0, A1, A2, A3 };

double gradient;

void setup() {

  Serial.begin(115200);

  for (int i = 0; i < 12; i++) {
    pinMode(wheelPins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(Enpints[i], OUTPUT);
  }
 Serial.println("1");
Serial.println("init start");
  pixy.init();         // Pixy lamp On/Off
  Serial.println("pixyinit");
  pixy.setLamp(0, 0);  // Pixy lamp (위, 아래)
  //픽시를 라인모드로 변환
  Serial.println("pixylamp");

  Serial.println(pixy.changeProg("line"));  //change pixy to line mode
Serial.println("pixy");
  servo.attach(servo_pin);  // 서보모터를 제어할 핀 번호를 지정합니다.
  servo.write(90);          // 모터를 90도(중앙 위치)로 이동시킵니다.
Serial.println("3");
  pinMode(echo1, INPUT);      // declare ultrasonic sensor Echo pin as input
  pinMode(trigger1, OUTPUT);  // declare ultrasonic sensor Trigger pin as Output
}


void advance(int A_pin, int B_pin, int EN_pin, int sp) {  // 정방향 회전
  digitalWrite(A_pin, HIGH);
  digitalWrite(B_pin, LOW);
  analogWrite(EN_pin, sp);
}

void reverse(int A_pin, int B_pin, int EN_pin, int sp) {  // 역방향 회전
  digitalWrite(A_pin, LOW);
  digitalWrite(B_pin, HIGH);
  analogWrite(EN_pin, sp);
}
void MStop(int A_pin, int B_pin) {  // 모터 정지
  digitalWrite(A_pin, LOW);
  digitalWrite(B_pin, LOW);
}
void Stop() {  // 정지
  MStop(wheelPins[0], wheelPins[1]);
  MStop(wheelPins[2], wheelPins[3]);
  MStop(wheelPins[4], wheelPins[5]);
  MStop(wheelPins[6], wheelPins[7]);
}
// 전진 함수
void forward(int delayValue = 30, int sp = 255) {
  advance(wheelPins[0], wheelPins[1], Enpints[0], sp);
  advance(wheelPins[2], wheelPins[3], Enpints[1], sp);
  advance(wheelPins[4], wheelPins[5], Enpints[2], sp);
  advance(wheelPins[6], wheelPins[7], Enpints[3], sp);
  delay(delayValue);  // 딜레이 적용
  Stop();
}
// 전진 함수
void forwardppppp(int delayValue = 30, int rsp = 255, int lsp = 255) {
  advance(wheelPins[0], wheelPins[1], Enpints[0], 255);
  advance(wheelPins[2], wheelPins[3], Enpints[1], 255);
  advance(wheelPins[4], wheelPins[5], Enpints[2], lsp);
  advance(wheelPins[6], wheelPins[7], Enpints[3], rsp);
  delay(delayValue);  // 딜레이 적용
  Stop();
}

// 후진 함수
void backward(int delayValue = 30, int sp = 255) {
  reverse(wheelPins[0], wheelPins[1], Enpints[0], sp);
  reverse(wheelPins[2], wheelPins[3], Enpints[1], sp);
  reverse(wheelPins[4], wheelPins[5], Enpints[2], sp);
  reverse(wheelPins[6], wheelPins[7], Enpints[3], sp);
  delay(delayValue);  // 딜레이 적용
  Stop();
}

// 좌회전 함수
void turnLeft(int delayValue = 30, int sp = 255) {
  reverse(wheelPins[0], wheelPins[1], Enpints[0], sp);
  advance(wheelPins[2], wheelPins[3], Enpints[1], sp);
  advance(wheelPins[4], wheelPins[5], Enpints[2], sp);
  reverse(wheelPins[6], wheelPins[7], Enpints[3], sp);
  delay(delayValue);  // 딜레이 적용
  Stop();
}

// 우회전 함수
void turnRight(int delayValue = 30, int sp = 255) {
  advance(wheelPins[0], wheelPins[1], Enpints[0], sp);
  reverse(wheelPins[2], wheelPins[3], Enpints[1], sp);
  reverse(wheelPins[4], wheelPins[5], Enpints[2], sp);
  advance(wheelPins[6], wheelPins[7], Enpints[3], sp);
  delay(delayValue);  // 딜레이 적용
  Stop();
}


// 좌측 이동 함수
void Left(int delayValue = 30, int sp = 255) {
  advance(wheelPins[0], wheelPins[1], Enpints[0], sp);
  reverse(wheelPins[2], wheelPins[3], Enpints[1], sp);
  advance(wheelPins[4], wheelPins[5], Enpints[2], sp);
  reverse(wheelPins[6], wheelPins[7], Enpints[3], sp);
  delay(delayValue);  // 딜레이 적용
  Stop();
}

// 우측 이동 함수
void Right(int delayValue = 30, int sp = 255) {
  reverse(wheelPins[0], wheelPins[1], Enpints[0], sp);
  advance(wheelPins[2], wheelPins[3], Enpints[1], sp);
  reverse(wheelPins[4], wheelPins[5], Enpints[2], sp);
  advance(wheelPins[6], wheelPins[7], Enpints[3], sp);
  delay(delayValue);  // 딜레이 적용
  Stop();
}

// 좌상 대각선 이동 함수
void fLeft(int delayValue = 30, int sp = 255) {
  advance(wheelPins[0], wheelPins[1], Enpints[0], sp);
  MStop(wheelPins[2], wheelPins[3]);
  advance(wheelPins[4], wheelPins[5], Enpints[2], sp);
  MStop(wheelPins[6], wheelPins[7]);
  delay(delayValue);  // 딜레이 적용
  Stop();
}

// 우상 대각선 이동 함수
void fRight(int delayValue = 30, int sp = 255) {
  MStop(wheelPins[0], wheelPins[1]);
  advance(wheelPins[2], wheelPins[3], Enpints[1], sp);
  MStop(wheelPins[4], wheelPins[5]);
  advance(wheelPins[6], wheelPins[7], Enpints[3], sp);
  delay(delayValue);  // 딜레이 적용
  Stop();
}

// 초음파센서 값을 읽어오는 함수
long Ultrasonic_read(int s, int n) {
  digitalWrite(s, LOW);
  delayMicroseconds(2);
  digitalWrite(s, HIGH);
  delayMicroseconds(10);
  long time = pulseIn(n, HIGH);
  return time / 29 / 2;
}

void Check_side() {  //양쪽 사이드 체크
  Stop();
  delay(100);

  for (int angle = 90; angle <= 135; angle += 5) {
    servo.write(angle);
  }
  delay(300);
  distance_R = Ultrasonic_read(trigger1, echo1);
  delay(100);
  for (int angle = 135; angle >= 45; angle -= 5) {
    servo.write(angle);
  }
  delay(500);
  distance_L = Ultrasonic_read(trigger1, echo1);
  delay(100);
  for (int angle = 45; angle <= 90; angle += 5) {
    servo.write(angle);
    ;
  }
  delay(300);
}


void logicCompareDistance() {  //논리있는 회피 동작

  Check_side();

  if (distance_L > distance_R) {
    unsigned long startTime = millis();

    while (distance < 20) {
      distance = Ultrasonic_read(trigger1, echo1);
      Left();
      delay(10);
    }
    // 이동한 시간 계산
    unsigned long endTime = millis();                 // 이동 종료 시간 저장
    unsigned long elapsedTime = endTime - startTime;  // 이동에 걸린 시간 계산

    //여기까지가 왼쪽으로 이동한 내용

    forward(30, 255);
    delay(3000);

    //이동후 다시 우측으로 이동
    Right();
    delay(elapsedTime);

  } else {
    unsigned long startTime = millis();
    while (distance < 20) {
      distance = Ultrasonic_read(trigger1, echo1);
      Right();
      delay(10);
    }
    // 이동한 시간 계산
    unsigned long endTime = millis();                 // 이동 종료 시간 저장
    unsigned long elapsedTime = endTime - startTime;  // 이동에 걸린 시간 계산

    forward(30, 255);
    delay(3000);

    //이동후 다시 좌측으로 이동
    Left();
    delay(elapsedTime);
  }
}
//수평이동
void adjustENAX(int enax) {

  int correction = map(abs(errorX), 0, 200, 0, 100);  // x축 오차에 비례하여 보정값 계산 (0~100 범위)
  int newENAX = 255 - correction;                     // 보정값을 ENA에 적용하여 속도 조절 (255에서 보정값을 뺌

  if (enax > 0) {
    // 왼쪽에서 오른쪽으로 이동
    Right(30, newENAX);
  } else if (enax < 0) {
    //  오른쪽에서 왼쪽으로 이동
    Left(30, newENAX);
  }
}

void adjustENAY(int enay) {
  int correction = map(abs(errorX), 0, 200, 0, 100);  // x축 오차에 비례하여 보정값 계산 (0~100 범위)
  int newENAY = 255 - correction;                     // 보정값을 ENA에 적용하여 속도 조절 (255에서 보정값을 뺌)
  if (enay > 0) {
    forwardppppp(30, newENAY, 255);
  } else if (enay < 0) {
    //  왼

    forwardppppp(30, 255, newENAY);
  }
}

void fuckingline(int erroX, int errorxchange) {


  if (abs(errorX) < 2 && abs(errorxchange) < 2) {
    // x축 오차와 y축 오차가 모두 오차 범위 내에 있는 경우
    forward(30, 255);
  } else {
    if (abs(errorX) >= 2) {
      // x축 오차가 있는 경우
      adjustENAX(errorX);
    } else if (abs(errorxchange) >= 2) {
      adjustENAY(errorxchange);
    }
  }
  Serial.println("end line");
}


void loop() {

  if (Serial.available()) {
    char data = Serial.read();  // 데이터를 읽음
    Serial.println(data);
    result = data - 'a';   // 읽은 문자를 정수로 변환하여 result에 저장
    Serial.print("Received data: ");
    Serial.println(result);
    while (Serial.available()) {
      Serial.read();  // 버퍼에 남은 데이터 모두 소비
    }
  }
  
  else{
      Serial.println("pass");
  if (result == 0) {
    Stop();
    Serial.println("stop");
    delay(100);
  } else if (result == 1) {
    Serial.println("forward");
    forward(5000, 255);
  } else if (result == 2) {
    Serial.println("turn left");
    turnLeft(5000);
  } else if (result == 3) {
    Serial.println("turn right");
    turnRight(5000);
  } else if (result == 4) {
    Serial.println("back");
    backward(5000);
  } else if (result == 5) {
    target = 5;
    Serial.println("A");
  } else if (result == 6) {
    target = 6;
    Serial.println("B");
  } else if (result == 7) {
    target = 7;
    Serial.println("C");
  } else if (result == 8) {
    target = 8;
    Serial.println("D");
  } else if (result == 9) {
    target = 9;
    Serial.println("E");
  } else if (result == 10) {
    target = 10;
    Serial.println("F");
  } else if (result == 11) {
    target = 11;
    Serial.println("G");
  } else if (result == 12) {
    target = 12;
    Serial.println("H");
  }




  int8_t res;
  res = pixy.line.getAllFeatures();        //get line features
  int startX = pixy.line.vectors[0].m_x0;  // 라인의 시작점 x 좌표
  int endX = pixy.line.vectors[0].m_x1;    // 라인의 끝점 x 좌표
  int startY = pixy.line.vectors[0].m_y0;
  int endY = pixy.line.vectors[0].m_y1;
  int startXError = X_CENTER - startX;         // 라인의 시작점 x 오차 계산
  int endXError = X_CENTER - endX;             // 라인의 끝점 x 오차 계산
  int errorX = (startXError + endXError) / 2;  // 라인의 중앙 x 오차 계산
  int errorxchange = startX - endX;            // 변화량 측정


  if (pixy.line.barcodes)  // detected road sign
  {
    int code = pixy.line.barcodes[0].m_code;
    switch (code) {
      case 0:  // stop
        Stop();
        delay(1000);
        break;

      case 1:  //go
        forward(500, 255);
        break;

      case 2:  //left
        turnLeft(3500);
        break;

      case 3:  //right
        turnRight(3500);
        break;

      default:
        if (code == target) {
          //회전
          while (pixy.line.barcodes[0].m_code != 0) {
            //라인 따라감
          }
          Stop();
          //뭐시깽이 코드를 뭔 코드를 보냄
          result = 0;
        }
        break;
    }
  } else {
    fuckingline(errorX, errorxchange);
  }
  }
}
