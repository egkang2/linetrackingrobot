
//모터
//IN1
#define            RIGHT_MOTOR_F                 14
//IN2
#define            RIGHT_MOTOR_B                 3
//ENA
#define            RIGHT_MOTOR_PWM               15

//IN3
#define            LEFT_MOTOR_F                  61
//IN4
#define            LEFT_MOTOR_B                  7
//ENB
#define            LEFT_MOTOR_PWM                18

//타미아
#define            MOTOR_F                       19
#define            MOTOR_B                       10

//적외선             안씀ㅅㄱ


//초음파
//
#define            ECHO                          11
#define            TRIC                          12

//트레킹 센서
#define            LEFT_LINE_CENSOR              4
#define            RIGHT_LINE_CENSOR             6
#define            CENTER_LINE_CENSOR            5


//변수 선원
int center_value, left_value, right_value = 0;
int pp = 0;

//기타센서            ㅁ?ㄹ

//변수 설정
int Mode =                                        0;
int Left_count =                                  0;
int Right_count =                                 0;
int Center_count=                                 0;

//함수
//전진함수
void forward(int MOTOR_SPEED=200){
  
  //입력값이 255넘을경우 255저장
  int pwm;
  if(MOTOR_SPEED>255){
    pwm = 255;
  }
  else{
    pwm = MOTOR_SPEED;
  }
  //Serial.println("aaaa");
  //우측모터속도제어
  digitalWrite(RIGHT_MOTOR_F,HIGH);
  digitalWrite(RIGHT_MOTOR_B,LOW);
  analogWrite(RIGHT_MOTOR_PWM,pwm);

  digitalWrite(LEFT_MOTOR_F,HIGH);
  digitalWrite(LEFT_MOTOR_B,LOW);
  analogWrite(LEFT_MOTOR_PWM,pwm-8);//원래 8.

}

//후진
void back(int MOTOR_SPEED=100){
  
  //입력값이 255넘을경우 255저장
  int pwm;
  if(MOTOR_SPEED>255){
    pwm = 255;
  }
  else{
    pwm = MOTOR_SPEED;
  }
  
  //우측모터속도제어
  digitalWrite(RIGHT_MOTOR_F,LOW);
  digitalWrite(RIGHT_MOTOR_B,HIGH);
  analogWrite(RIGHT_MOTOR_PWM,pwm);

  digitalWrite(LEFT_MOTOR_F,LOW);
  digitalWrite(LEFT_MOTOR_B,HIGH);
  analogWrite(LEFT_MOTOR_PWM,pwm);
}

//우회전
void turn_right(int LEFT_MOTOR_SPEED=240, int RIGHT_MOTOR_SPEED=240){
  
  //입력값이 255넘을경우 255저장
  int left_pwm;
  int right_pwm;
  
  if(LEFT_MOTOR_SPEED>255){
    left_pwm = 255;
  }
  else{
    left_pwm = LEFT_MOTOR_SPEED;
  }

  if(RIGHT_MOTOR_SPEED>255){
    right_pwm = 255;
  }
  else{
    right_pwm = RIGHT_MOTOR_SPEED;
  }
  
  //우측모터속도제어
  digitalWrite(RIGHT_MOTOR_F,LOW);
  digitalWrite(RIGHT_MOTOR_B,HIGH);
  analogWrite(RIGHT_MOTOR_PWM,right_pwm);

  digitalWrite(LEFT_MOTOR_F,HIGH);
  digitalWrite(LEFT_MOTOR_B,LOW);
  analogWrite(LEFT_MOTOR_PWM,left_pwm);


}

//직진하며 우회전
void turn_right_F(int LEFT_MOTOR_SPEED=240, int RIGHT_MOTOR_SPEED=240){
  
  //입력값이 255넘을경우 255저장
  int left_pwm;
  int right_pwm;
  
  if(LEFT_MOTOR_SPEED>255){
    left_pwm = 255;
  }
  else{
    left_pwm = LEFT_MOTOR_SPEED;
  }

  if(RIGHT_MOTOR_SPEED>255){
    right_pwm = 255;
  }
  else{
    right_pwm = RIGHT_MOTOR_SPEED;
  }
  
  //우측모터속도제어
  digitalWrite(RIGHT_MOTOR_F,HIGH);
  
  digitalWrite(RIGHT_MOTOR_B,LOW);
  analogWrite(RIGHT_MOTOR_PWM,right_pwm*(0.80));

  digitalWrite(LEFT_MOTOR_F,HIGH);
  
  digitalWrite(LEFT_MOTOR_B,LOW);
  analogWrite(LEFT_MOTOR_PWM,left_pwm);


}

//좌회전
void turn_left(int LEFT_MOTOR_SPEED=240, int RIGHT_MOTOR_SPEED=240){
  
  //입력값이 255넘을경우 255저장
  int left_pwm;
  int right_pwm;
  
  if(LEFT_MOTOR_SPEED>255){
    left_pwm = 255;
  }
  else{
    left_pwm = LEFT_MOTOR_SPEED;
  }

  if(RIGHT_MOTOR_SPEED>255){
    right_pwm = 255;
  }
  else{
    right_pwm = RIGHT_MOTOR_SPEED;
  }
  
  
  //우측모터속도제어
  digitalWrite(RIGHT_MOTOR_F,HIGH);
 
  digitalWrite(RIGHT_MOTOR_B,LOW);
  analogWrite(RIGHT_MOTOR_PWM,right_pwm);

  digitalWrite(LEFT_MOTOR_F,LOW);
  
  digitalWrite(LEFT_MOTOR_B,HIGH);
  analogWrite(LEFT_MOTOR_PWM,left_pwm);


}

//직진하며 좌회전
void turn_left_F(int LEFT_MOTOR_SPEED=240, int RIGHT_MOTOR_SPEED=240){
  
  //입력값이 255넘을경우 255저장
  int left_pwm;
  int right_pwm;
  
  if(LEFT_MOTOR_SPEED>255){
    left_pwm = 255;
  }
  else{
    left_pwm = LEFT_MOTOR_SPEED;
  }

  if(RIGHT_MOTOR_SPEED>255){
    right_pwm = 255;
  }
  else{
    right_pwm = RIGHT_MOTOR_SPEED;
  }
  
  
  //우측모터속도제어
  digitalWrite(RIGHT_MOTOR_F,HIGH);
  digitalWrite(RIGHT_MOTOR_B,LOW);
  analogWrite(RIGHT_MOTOR_PWM,right_pwm);

  digitalWrite(LEFT_MOTOR_F,HIGH);
  digitalWrite(LEFT_MOTOR_B,LOW);
  analogWrite(LEFT_MOTOR_PWM,(0.6)*left_pwm);


}

//안움직임
void not_moving(){
  
  digitalWrite(RIGHT_MOTOR_F,LOW);
  digitalWrite(RIGHT_MOTOR_B,LOW);
  analogWrite(RIGHT_MOTOR_PWM,0);

  digitalWrite(LEFT_MOTOR_F,LOW);
  digitalWrite(LEFT_MOTOR_B,LOW);
  analogWrite(LEFT_MOTOR_PWM,0);
}
//초음파센서 측정
double distance(){

  unsigned long duration;
  
  digitalWrite(TRIC, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIC, LOW);
   duration = pulseIn (ECHO, HIGH,30000UL);
  
  return duration*0.17;
  Serial.println(duration*0.17);
  Serial.println("aaaa");
}


//라인트레이싱  while써서 할 타이밍 지정해야됨, 첫 번째 부분
void line_tracing(int p = 1){
  
  //미리 값을 입력받음
  int a,b,c,data,censer_state = 0;

  //2번째 라인트레이싱 카운트
  int second_linetracing_count = 0;

  //
  a = digitalRead(LEFT_LINE_CENSOR);
  b = digitalRead(CENTER_LINE_CENSOR);
  c = digitalRead(RIGHT_LINE_CENSOR);

  //data abc
  

  if(p == 1){
  while(censer_state != 3){
    
    a = digitalRead(LEFT_LINE_CENSOR);
    b = digitalRead(CENTER_LINE_CENSOR);
    c = digitalRead(RIGHT_LINE_CENSOR);

    //data는 swich 작동 변수, censer_state은 while 작동 변수
    data = a*4 + b*2 +c;
    censer_state = a + b + c;
    Serial.println(data);
    delay(10000);
  switch(data){

    //000
    case 0:
      forward(240);
      break;

    //001
    case 1:
    
       turn_right(250,250);
       delay(150);
       break;

    //010
    case 2:
    
      forward(220);
      break;

    //011
    case 3:
      
      turn_right_F(250);
      break;

    //100
    case 4:
    
    turn_left(250,250);
    delay(150);
    break;

    //101 
    case 5:
      forward(240);
      break;

    //110
    case 6:
    
      turn_left_F(250);
      break;

    //111 
    case 7:
      forward(240);
      delay(50);

      default:
      break;
  }
 }
 }
  //2번쨰 부분 라인트레이싱
  if(p == 0){
    while(second_linetracing_count <=3){

    a = digitalRead(LEFT_LINE_CENSOR);
    b = digitalRead(CENTER_LINE_CENSOR);
    c = digitalRead(RIGHT_LINE_CENSOR);

    //data는 swich 작동 변수
    data = a*4 + b*2 +c;
  
    switch(data){

    //000
    case 0:
    
      forward(240);
      break;

    //001
    case 1:
    
       turn_right(250,250);
       delay(150);
       break;

    //010
    case 2:
    
      forward(220);
      break;

    //011
    case 3:
      
      turn_right_F(250);
      break;

    //100
    case 4:
    
      turn_left(250,250);
      delay(120);
      break;

    //101 
    case 5:
    
      forward(240);
      break;

    //110
    case 6:
    
      turn_left_F(250);
      break;

    //111 
    case 7:

    if(second_linetracing_count == 4){
      while(1){
      not_moving();
      }
    }
      second_linetracing_count = second_linetracing_count + 1;
      forward(240);
      delay(500);

    default:
      break;
   }
  
  }
 }
}

  void aaaa(){
    int a;
    a = distance();
    Serial.println(a);
    delay(3000);
  }
//목표지점까지 직진
  void go_to_check_point(int Motor_speed = 240){

  int a,b                      = 0;
  int total_count           = 0;

  
 
  int previous_total_check  = 0;
  int current_total_check   = 0;

  //center 측정값이 3번바뀌는 동안에
  while(total_count<=2){

    a = digitalRead(LEFT_LINE_CENSOR);
    b = digitalRead(RIGHT_LINE_CENSOR);
    
    //센트측정값을 current_center_check에 저장
    current_total_check = a && b;
    
    //만약 이전측정값과 현제측정값이 다르다면 카운트 추가 및 이전측정값에 현제측정값을 저장
    if(previous_total_check != current_total_check){
      total_count++;
      
      previous_total_check = current_total_check;

      //오류방지를 위해서 0.05초간 직진
      forward(240);
      delay(22);
    }
    //아닌경우에 계속 직진
    else{
      forward(220);
    }
  }
    forward(240);
    delay(400);
}


//수직맞추기
void vertical_chasing(int param){
  
  int a,b,data = 5;

  //검은색에서 시작 흰색을 기준으로 수직 맞추기
  if(param >= 1){
  
  
   while(data != 0){
    
    a = digitalRead(LEFT_LINE_CENSOR);
    b = digitalRead(RIGHT_LINE_CENSOR);
    //왼쪽 오른쪽 데이타
    data = a*2 + b;
   
    
  switch(data){
    
  //0x1 오른쪽 바퀴만 움직임
  
  case 1:
  turn_left(100);
  break;
  
  case 2:
    turn_right(100);
    break;
  
  //1x1
  case 3:
  forward();
    break;

   default:
   break;
  }
 }
  }
  //1보다 작은 파라미터를 줄 경우 흰색시작 검은색을 기준으로 수직을 맞추기
  else{
    
    while(data != 3){
    
    a = digitalRead(LEFT_LINE_CENSOR);
    b = digitalRead(RIGHT_LINE_CENSOR);
    
    //data 왼쪽 오른쪽값
    data = a*2 + b;
    
  switch(data){
    
  //0x1 오른쪽 바퀴만 움직임

  case 0: //0x0
    forward();
    break;
  
  case 1: //0x1
    turn_left(100);
    break;
  
  case 2: //1x0
    turn_right(100);
    break;

  case 3: //1x1
    not_moving();
    break;

   default:
   break;
  }
    
  }
 
}
}

//경기장진입
void enter_the_area(int param=1){

  int a,b,data = 0;

  //Right or Lefr 중 한개라도 검은색 감지시까지 직진
  while(data <=1){
    
    a = digitalRead(LEFT_LINE_CENSOR);
    b = digitalRead(RIGHT_LINE_CENSOR);
    
    data = a + b;
    forward(180);
  }

  //param 값이 1이면 물체 감지시까지 직진
  if(param == 1){
    double distance_value_sum = 20000;
  int distance_count = 1;
  int distance_value = 1000;
  int distance_error = 156;

  //distance값이 155이하가 될 때 직진
  while(1){
    
    forward(240);

    //측정오류 보안
    distance_error = distance();

    //측정 오류시 값
    if(distance_error ==0){
      distance_error = 156;
    }

    //측정값 합
    distance_value_sum = distance_value_sum + distance_error;

    //주기
    distance_count = distance_count + 1;

    //평균값 계산
    if(distance_count >= 10){
      distance_value = distance_value_sum /10;
      
      distance_count = 0;
      distance_value_sum = distance();
      
    }

    //평균값이 목표값 도달시 종료
    if(distance_value <= 155){
      Serial.println("end");
      break;
          }
  }
  }
  else{
    //param 값이 1이 아니면 실행

    //앞으로 직진 3초간
    forward(255);
    digitalWrite(MOTOR_F,HIGH);
    digitalWrite(MOTOR_B,LOW);
    delay(1200);

    a = digitalRead(LEFT_LINE_CENSOR);
    b = digitalRead(RIGHT_LINE_CENSOR);

    data = a*2 + b;

    //견제에 의해서 올라가지 못하였을 경우 실행 아닐경우 data 값은 1이상나옴
    while(data == 0){
      forward(255);
    }
    

    
  }
  
  
}

//경기장 회전  
void rotate_area(int Motor_speed=240,int Motor_speed_L=240, int Motor_speed_R=240){

  int center_value = digitalRead(CENTER_LINE_CENSOR);
  int left_value   = digitalRead(LEFT_LINE_CENSOR);
  int right_value  = digitalRead(RIGHT_LINE_CENSOR);
  int data = 0;
  
  //우회전
  turn_right(Motor_speed_L,Motor_speed_R);
  delay(200);

  forward(240);
  delay(1400);

  turn_left();
  delay(600);

  forward(240);
  delay(900);

  turn_left();
  delay(700);



  //center 측정값이 white 가 될떄까지 직진

  while(center_value == LOW){
    
    center_value = digitalRead(CENTER_LINE_CENSOR);
    forward(200);
  }

  back(200);
  delay(800);

  //약 90도 회전
  turn_right_F(240,160);
  delay(2333);
  
}

//경기장 탈출
 void exit_area(int Motor_speed=240,int Motor_speed_L=240, int Motor_speed_R=240){
  
  forward(250);
  delay(1500);
  
  int center_value, left_value, right_value = 0;
  int data = 0;
  
  while(data==0){
    center_value = digitalRead(CENTER_LINE_CENSOR);
    left_value =   digitalRead(LEFT_LINE_CENSOR);
    right_value =  digitalRead(RIGHT_LINE_CENSOR);

    data = center_value + left_value + right_value;
    forward(250);
    
  }
  
  
 }

//본성 경기 프로그램
void final_match(int Motor_speed=240,int Motor_speed_L=240, int Motor_speed_R=240){
  
  int a = digitalRead(LEFT_LINE_CENSOR);
  int b   = digitalRead(CENTER_LINE_CENSOR);
  int c  = digitalRead(RIGHT_LINE_CENSOR);
  
  int pp = 0;
  int data = 0;
  
  unsigned long millis_time     = 0;
  unsigned previous_millis_time = 0;
  
  while(true){
    
  millis_time = millis()/100;
  
  a = digitalRead(LEFT_LINE_CENSOR);
  b   = digitalRead(CENTER_LINE_CENSOR);
  c  = digitalRead(RIGHT_LINE_CENSOR);
  
  if((millis_time - previous_millis_time) >= 1){
    
    previous_millis_time = millis_time;
    
    if(distance() <=4){
      pp = 1;
    }
    else{
      pp = 0;
    }
    
  }
  

  data = pp*8 + a*4 + b*2 +c;
  
  switch(data){

    case 0:
      back(80);
      delay(10);
      break;
      
    case 1:
       turn_right();
       break;
       
    case 2:
        not_moving();
        break;

    case 3:
        turn_right();
        break;
    
    case 4:
        turn_left();
        break;
        
    case 5:
        back(80);
        delay(10);
        break;
        
    case 6:
        turn_left();
        break;
        
    case 7:
        forward();
        break;
        
    case 8:
      not_moving();
      break;
      
    case 9:
        turn_right();
        break;
    case 10:
        not_moving();
        break;

    case 11:
        turn_right();
        break;
        
    case 12:
        turn_left();
        break;
    
    case 13:
        back(80);
        delay(10);
        break;

    case 14:
        turn_left();
        break;
        
    case 15:
        forward(250);
        break;    
  }
  }
}


void setup() {

  //Serial 통신
  Serial.begin(9600);
  //우츨모터
  pinMode(RIGHT_MOTOR_F,OUTPUT);
  pinMode(RIGHT_MOTOR_B,OUTPUT);
  pinMode(RIGHT_MOTOR_PWM,OUTPUT);

  //좌측모터
  pinMode(LEFT_MOTOR_F,OUTPUT);
  pinMode(LEFT_MOTOR_B,OUTPUT);
  pinMode(LEFT_MOTOR_PWM,OUTPUT);

  //타미아모터
  pinMode(MOTOR_F,OUTPUT);
  pinMode(MOTOR_B,OUTPUT);

  //초음파센서
  pinMode(ECHO,INPUT);
  pinMode(TRIC,OUTPUT);

  //트레킹센서
  pinMode(LEFT_LINE_CENSOR,INPUT);
  pinMode(RIGHT_LINE_CENSOR,INPUT);
  pinMode(CENTER_LINE_CENSOR,INPUT);

  digitalWrite(LEFT_LINE_CENSOR,HIGH);
  digitalWrite(CENTER_LINE_CENSOR,HIGH);
  digitalWrite(RIGHT_LINE_CENSOR,HIGH);

  //모드


  // p 예선 본선 구분

}

void loop() {
  
  
  
  
  //line_tracing(1);
  //forward();
  aaaa();
  

  

  
}
