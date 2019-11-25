#include<Servo.h> 

Servo thumbMotor, indexMotor, middleMotor, ringMotor, littleMotor;
int thumbPin=10, indexPin=11, middlePin=9, ringPin=8, littlePin=7;
Servo motor_list[5] = {thumbMotor, indexMotor, middleMotor, ringMotor, littleMotor};
byte motor_angle_list[5] = {70, 0, 50, 40, 70};
int motor_pin_list[5]={thumbPin, indexPin, middlePin, ringPin, littlePin};

bool motionFlag = false;

int btnOnePin=2, btnTwoPin=3;
int BTN_PRESSED=0, BTN_UNPRESSED=1;
int pos = 0;
/*
 Name:		ArtificialHand.ino
 Created:	2019-11-19 ~
 Author:	10304 김민준
*/

// the setup function runs once when you press reset or power the board
void setup() {
  /*
   5개 서보 가로 폭 100.7mm
   볼트 홈 아래 ~ 서보모터 아래 24mm
   */
  for(int i=0;i<5;i++){
    motor_list[i].attach(motor_pin_list[i]);
    motor_list[i].write(0);
    delay(15);
  }

  /*
   택트 스위치는 아두이노에서 digitalRead() 함수로 읽어올 때 오작동이 생기는 것을 방지하기 위해 PULL_UP 저항을 사용하며, pinMode() 함수로 설정해줄 때 INPUT_PULLUP 으로 설정해준다.
   택트 스위치가 눌렸을때 digitalRead()값은 0이고, 눌리지 않았을 때의 digitalRead()의 
  */
  pinMode(btnOnePin, INPUT_PULLUP);
  pinMode(btnTwoPin, INPUT_PULLUP);
	
	Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {
  delay(1000);
  byte btnAvailable[] = {digitalRead(btnOnePin), digitalRead(btnTwoPin)};
  if(btnAvailable[0] == BTN_PRESSED && btnAvailable[1] == BTN_UNPRESSED&&!motionFlag){
    Serial.println("[Hand Mode] FIST");
    motionFlag = true;
    moveHand_fist();
  }
  else if(btnAvailable[0] == BTN_UNPRESSED && btnAvailable[1] == BTN_PRESSED&&!motionFlag){
    Serial.println("[Hand Mode] COUNT");
    motionFlag = true;
    moveHand_count();
  }
  else if (btnAvailable[0] == BTN_PRESSED && btnAvailable[1] == BTN_PRESSED&&!motionFlag){
    Serial.println("[Hand Mode] MODE 3");
    motionFlag = true;
    
  }
  else if(btnAvailable[0] == BTN_UNPRESSED && btnAvailable[1] == BTN_UNPRESSED){
    Serial.println("[Hand Mode] UNPRESSED");
    motionFlag = false;
  }
	Serial.println("Motor Loop Begins");

  for(double deg=0;deg<70;deg+=0.2){
    Serial.println(deg);
    //thumbMotor.write(deg);
    indexMotor.write(deg);
    middleMotor.write(deg);
    ringMotor.write(deg);
    littleMotor.write(deg);
  }
  for(double deg=70;deg>=0;deg-=0.2){
    Serial.println(deg);
    //thumbMotor.write(deg);
    indexMotor.write(deg);
    middleMotor.write(deg);
    ringMotor.write(deg);
    littleMotor.write(deg);
  }
 
	Serial.println("Motor Loop Ends");
}

void moveHand_fist(){
  Serial.println("Motion : <Fist> has started.");
  for(float deg=0;deg<180;deg+=0.2f){
    if(motor_angle_list[0]<=deg){
      motor_list[0].write(deg);
    }
    if(motor_angle_list[1]<=deg){
      motor_list[1].write(deg);
    }
    if(motor_angle_list[2]<=deg){
      motor_list[2].write(deg);
    }
    if(motor_angle_list[3]<=deg){
      motor_list[3].write(deg);
    }
    if(motor_angle_list[4]<=deg){
      motor_list[4].write(deg);
    }
  }
  for(float deg=0;deg<180;deg+=0.2f){
    if(motor_angle_list[0]<=deg){
      motor_list[0].write(deg);
    }
    if(motor_angle_list[1]<=deg){
      motor_list[1].write(deg);
    }
    if(motor_angle_list[2]<=deg){
      motor_list[2].write(deg);
    }
    if(motor_angle_list[3]<=deg){
      motor_list[3].write(deg);
    }
    if(motor_angle_list[4]<=deg){
      motor_list[4].write(deg);
    }
  }
  Serial.println("Motion : <Fist> has ended.");
  motionFlag==false;
}

void moveHand_count(){
 Serial.println("Motion : <Counting Numbers> has started.");
  for(int i=0;i<5;i++){
    for(float deg=0;deg<motor_angle_list[i];deg+=0.2f){
      motor_list[i].write(deg);
    }
  }
  for(int i=0;i<5;i++){
    for(float deg=motor_angle_list[4-i];deg>0;deg-=0.2f){
      motor_list[i].write(deg);
    }
  }
 Serial.println("Motion : <Counting Numbers> has ended.");
  motionFlag==false;
}

void servo_angle_debugger(Servo motor, int num){
  for(int deg = 0; deg <180; deg+=num){
    Serial.print("Starting Motor Test");
    Serial.print(" servo degree : ");
    Serial.println(deg);

    motor.write(deg);
    delay(20);
    Serial.println("Do you want to quit debugging? Y/N : ");
    delay(1000);
    char cmd = Serial.read();
    if(cmd == 'y'){
      Serial.print("Servor Motor [");
      Serial.print("] debugging ended. Final result : ");
      Serial.println(deg);
      return;
    }
    else{
      continue;
    }
    delay(1000);
  }
  Serial.print("Servor Motor [");
  Serial.print("] debugging ended. Final result : ");
  Serial.println(180); 
}
