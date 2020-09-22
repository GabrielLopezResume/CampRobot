//motor shield library
#include <AFMotor.h> 

//assign left and right motor to M1-M4
//have to assign globally to allow functions to use the motors
AF_DCMotor R_motor(3); 
AF_DCMotor L_motor(4); 
  
//declare functions
void forward();
void backward();
bool ultra();
bool ir();

/* for the ultrasonic sensor, connect the trig and echo pins to whichever digital pins you chose.
I chose 9 and 10. Then connect VCC to 5V and GND to ground. */  
int trig = 9;
int echo = 10;

//for the ir sensor chose any digital pins to connect to, i chose 6
//then connect the sensors power and ground 
int irsensor=6;

//direction variable: true is forward and false is backward
bool dir = true;

//runs on startup of Arduino
void setup() {
  
  // set the serial monitor at 9600 
  Serial.begin(9600); 
  
  //set speed
  int speed=200;
  L_motor.setSpeed(speed); 
  R_motor.setSpeed(speed); 
  //start with the motors off 
  L_motor.run(RELEASE); 
  R_motor.run(RELEASE); 
  
  //set ir sensor 
  pinMode(irsensor,INPUT);
  forward();
}

//runs while arduino is powered
void loop() {
  //checks ultrasonic sensor when going forward, and flips the direction when 
  //something is detected
  
  //check ir sensor when going backwardsand flips the direction when 
  //something is detected
  
  if(dir){
    if(ultra()){
      backward();
      dir=false;
    }
  }else{
    if(ir()){
      forward();
      dir=true;
    }
  }
}

void forward(){
  L_motor.run(FORWARD); 
  R_motor.run(FORWARD);
}

void backward(){
  L_motor.run(BACKWARD); 
  R_motor.run(BACKWARD);
}

//returns true if there is a object with in 15 cm and vise versa
bool ultra(){
   // set trig to low
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    // read from the trig pin for 10 microseconds
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    // read echo and  return the sound wave travel time in microseconds
    long duration = pulseIn(echo, HIGH);
    // distance formula for sound waves in centimeters
    int distance= duration*0.034/2;
    // if there is a object within 15 centimeters return true and vise versa 
    if(distance<15){
      return true;
    }else{
      return false;
    }
    //turn off echo pin
    digitalWrite(echo, LOW);
}

//returns true if ir sensor is triggered and vise versa
bool ir(){
  return digitalRead(irsensor);
}