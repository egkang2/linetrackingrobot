
int result = 0;

const int motor1Pin[4] = {2, 4, 3, 5}; // A 상, B 상, A' 상, B' 상
const int motor2Pin[4] = {6, 8, 7, 9}; // A 상, B 상, A' 상, B' 상

const int stepDelay = 3;         // 스텝 간 딜레이 (조정 가능) / 단, 3 밑으로 내리지 말기

void forward() {
  digitalWrite(motor1Pin[3], LOW);
  digitalWrite(motor1Pin[0], HIGH);
  digitalWrite(motor2Pin[3], LOW);
  digitalWrite(motor2Pin[0], HIGH);
  delay(stepDelay);

  digitalWrite(motor1Pin[0], LOW);
  digitalWrite(motor1Pin[1], HIGH);
  digitalWrite(motor2Pin[0], LOW);
  digitalWrite(motor2Pin[1], HIGH);
  delay(stepDelay);

  digitalWrite(motor1Pin[1], LOW);
  digitalWrite(motor1Pin[2], HIGH);
  digitalWrite(motor2Pin[1], LOW);
  digitalWrite(motor2Pin[2], HIGH);
  delay(stepDelay);

  digitalWrite(motor1Pin[2], LOW);
  digitalWrite(motor1Pin[3], HIGH);
  digitalWrite(motor2Pin[2], LOW);
  digitalWrite(motor2Pin[3], HIGH);
  delay(stepDelay);
}

void backward() {
  digitalWrite(motor1Pin[1], LOW);
  digitalWrite(motor1Pin[0], HIGH);
  digitalWrite(motor2Pin[1], LOW);
  digitalWrite(motor2Pin[0], HIGH);
  delay(stepDelay);

  digitalWrite(motor1Pin[0], LOW);
  digitalWrite(motor1Pin[3], HIGH);
  digitalWrite(motor2Pin[0], LOW);
  digitalWrite(motor2Pin[3], HIGH);
  delay(stepDelay);

  digitalWrite(motor1Pin[3], LOW);
  digitalWrite(motor1Pin[2], HIGH);
  digitalWrite(motor2Pin[3], LOW);
  digitalWrite(motor2Pin[2], HIGH);
  delay(stepDelay);

  digitalWrite(motor1Pin[2], LOW);
  digitalWrite(motor1Pin[1], HIGH);
  digitalWrite(motor2Pin[2], LOW);
  digitalWrite(motor2Pin[1], HIGH);
  delay(stepDelay);
}

void Stop() {
  digitalWrite(motor1Pin[1], HIGH);
  digitalWrite(motor1Pin[0], HIGH);
  digitalWrite(motor2Pin[1], HIGH);
  digitalWrite(motor2Pin[0], HIGH);

  digitalWrite(motor1Pin[2], LOW);
  digitalWrite(motor1Pin[3], LOW);
  digitalWrite(motor2Pin[2], LOW);
  digitalWrite(motor2Pin[3], LOW);
}

void forward_step(int Step) {
  for (int i = 0; i < Step; i++) {
    forward();
    if(result==13)
      Stop();
  }
}

void backward_step(int Step) {
  for (int i = 0; i < Step; i++) {
    backward();
    if(result==13)
      Stop();
    
  }
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 4; i++) {
    pinMode(motor1Pin[i], OUTPUT);
    pinMode(motor2Pin[i], OUTPUT);
  }
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
  else {
    if (result == 13) { // n
      Stop();
    }
    else if (result == 14) { // o
      forward_step(250);
      result = 13;
    }
    else if (result == 15) { // p
      backward_step(250);
      result = 13;
    }
  }
}
