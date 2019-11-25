#include<Servo.h>

Servo thumbMotor, indexMotor, middleMotor, ringMotor, littleMotor;
int thumbPin=7, indexPin=8, middlePin=9, ringPin=10, littlePin=11;
Servo motor;
Servo motor_list[5] = {thumbMotor, indexMotor, middleMotor, ringMotor, littleMotor};
int motor_pin_list[5]={thumbPin, indexPin, middlePin, ringPin, littlePin};

void setup() {
  //motor.attach(3);
  
  // Initializing 5 motors
  for(int i=0;i<5;i++){
    motor_list[i].attach(motor_pin_list[i]);
    motor_list[i].write(0);
    delay(15);
  }
  Serial.begin(9600);
}

void loop() {
  Serial.println("Trying to initialize Servo Motors...");
  //motor.write(0);
  
  // Initializing 5 motors
  for(int i=0;i<5;i++){
    motor_list[i].attach(motor_pin_list[i]);
    motor_list[i].write(0);
    delay(15);
  }
  
}
