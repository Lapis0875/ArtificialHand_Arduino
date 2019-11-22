#include<Servo.h> 

Servo thumbMotor, indexMotor, middleMotor, ringMotor, littleMotor;
int thumbPin=7, indexPin=8, middlePin=9, ringPin=10, littlePin=11;
Servo motor_list[5] = {thumbMotor, indexMotor, middleMotor, ringMotor, littleMotor};
int motor_pin_list[5]={thumbPin, indexPin, middlePin, ringPin, littlePin};

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
  byte btnAvailable[] = {digitalRead(btnOnePin), digitalRead(btnTwoPin)};
  if(btnAvailable[0] == BTN_PRESSED && btnAvailable[1] == BTN_UNPRESSED){
    Serial.println("[Hand Mode] FIST");
    moveHand_fist();
  }
  else if(btnAvailable[0] == BTN_UNPRESSED && btnAvailable[1] == BTN_PRESSED){
    Serial.println("[Hand Mode] COUNT");
    moveHand_count();
  }
  else if (btnAvailable[0] == BTN_PRESSED && btnAvailable[1] == BTN_PRESSED){
    Serial.println("[Hand Mode] FUCK_U");
    moveHand_count();
  }
  else if(btnAvailable[0] == BTN_UNPRESSED && btnAvailable[1] == BTN_UNPRESSED){
    Serial.println("[Hand Mode] UNPRESSED");
  }
	Serial.println("Motor Loop Begins");
  delay(1000);
  Serial.println("Moving into next servo");
  delay(1000);
  servo_angle_debugger(thumbMotor, 0);
  Serial.println("Moving into next servo");
  delay(1000);
  servo_angle_debugger(indexMotor, 1);
  Serial.println("Moving into next servo");
  delay(1000);
  servo_angle_debugger(middleMotor, 2);
  Serial.println("Moving into next servo");
  delay(1000);
  servo_angle_debugger(ringMotor, 3);
  Serial.println("Moving into next servo");
  delay(1000);
  servo_angle_debugger(littleMotor, 4);

  /*
  Serial.println("Motor Increasing Loop Begins");
  for(int i=0;i<5;i++){
    Serial.print(i);
    Serial.println(" motor begins.");
    moveMotor(motor_list[i], 180, 'i');
    delay(100);
  }
  Serial.println("Motor Increasing Loop Ends");
  
  Serial.println("Motor Decreasing Loop Begins");
  for(int i=0;i<5;i++){
    Serial.print(i);
    Serial.println(" motor begins.");
    moveMotor(motor_list[i], 0, 'd');
    delay(100);
  }
  Serial.println("Motor Decreasing Loop Ends");
  */
  /*
  Serial.println("Motor Increasing Loop Begins");
  for (pos = 0; pos < 180; pos += 1){
      thumbMotor.write(pos);
      indexMotor.write(pos);
      middleMotor.write(pos);
      ringMotor.write(pos);
      littleMotor.write(pos);
      delay(15);
  }
  Serial.println("Motor Increasing Loop Ends");
  
  Serial.println("Motor Decreasing Loop Begins");
  for (pos = 180; pos >= 1; pos -= 1){
      thumbMotor.write(pos);
      indexMotor.write(pos);
      middleMotor.write(pos);
      ringMotor.write(pos);
      littleMotor.write(pos);
      delay(15);
  }
  Serial.println("Motor Decreasing Loop Ends");
  */
	//Serial.println("Motor Loop Ends");
}

void moveMotor(Servo motor,int pos,char mode){
  /*
   moveMotor function is a function to move Servo motor at position given as parameter.
   motor : type<Servo>, a servo which you want to control.
   pos : type<int>, target position which you want to move your servo into.
   mode : type<char>, mode which you want to control your motor. 'i' for increase, 'd' for decrease.
  */
  switch(mode){
    case 'i':
      for(int degree=0;degree<pos;degree++){
        motor.write(degree);
        delay(15);
      }
      break;
    case 'd':
      for(int degree=180;degree>=pos;degree--){
        motor.write(degree);
        delay(15);
      }
      break;
  }
}

void moveHand_fist(){
  for(int i=0;i<5;i++){
    
  }
}

void moveHand_count(){
  for(int i=0;i<5;i++){
    
  }
}

void servo_angle_debugger(Servo motor, int motor_num){
  for(int deg = 0; deg <180; deg+=3){
    Serial.print("Current ");
    Serial.print(motor_num);
    Serial.print(" servo degree : ");
    Serial.println(deg);

    motor.write(deg);
    delay(20);
    Serial.println("Do you want to quit debugging? Y/N : ");
    delay(1000);
    char cmd = Serial.read();
    if(cmd == 'y'){
      Serial.print("Servor Motor [");
      Serial.print(motor_num);
      Serial.print("] debugging ended. Final result : ");
      Serial.println(deg);
      return;
    }
    else if(cmd == 'n'){
      continue;
    }
    delay(1000);
  }
  Serial.print("Servor Motor [");
  Serial.print(motor_num);
  Serial.print("] debugging ended. Final result : ");
  Serial.println(180); 
}
