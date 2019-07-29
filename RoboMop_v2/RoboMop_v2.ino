#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(4,5);
Servo myServo;

int r_motor_n = 7; //PWM control Right Motor +
int r_motor_p = 8; //PWM control Right Motor -
int r_motor_c = 6;
int l_motor_p = 9; //PWM control Left Motor -
int l_motor_n = 10; //PWM control Left Motor +
int l_motor_c = 11;
int pump = 13;
int mop = 12;
int serv = 3;
int speedy = 255;
int incomingByte = 'F'; // for incoming serial data
const int trigPin = 3; //trigger pin ultrasonic
const int echoPin = 2; //echopin ultrasonic
long duration;
int distance;


void setup()
{
Bluetooth.begin(9600);
pinMode(r_motor_n, OUTPUT); //Set control pins to be outputs
pinMode(r_motor_p, OUTPUT);
pinMode(r_motor_c, OUTPUT);
pinMode(l_motor_p, OUTPUT);
pinMode(l_motor_n, OUTPUT);
pinMode(l_motor_c, OUTPUT);
pinMode(pump, OUTPUT);
pinMode(mop, OUTPUT);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
digitalWrite(r_motor_n, LOW); //set both motors off for start-up
digitalWrite(r_motor_p, LOW);
digitalWrite(l_motor_p, LOW);
digitalWrite(l_motor_n, LOW);
digitalWrite(pump, LOW);
digitalWrite(mop, LOW);
Serial.begin(9600);
}


void loop()
{

if (Bluetooth.available() > 0) 
{
incomingByte = Bluetooth.read();
}

DistanceCheck();

switch(incomingByte)
{

case 'S': // control to stop the robot
digitalWrite(r_motor_n, LOW); 
digitalWrite(r_motor_p, LOW);
digitalWrite(l_motor_p, LOW);
digitalWrite(l_motor_n, LOW);
Serial.println("Stop");
incomingByte='*';
break;

case 'R': //control for right
digitalWrite(r_motor_n, LOW); 
digitalWrite(r_motor_p, LOW);
digitalWrite(r_motor_c, HIGH);
digitalWrite(l_motor_p, HIGH);
digitalWrite(l_motor_n, LOW);
digitalWrite(l_motor_c, HIGH);
Serial.println("right");
incomingByte='*';
break;


case 'L': //control for left
digitalWrite(r_motor_n, LOW); 
digitalWrite(r_motor_p, HIGH);
digitalWrite(r_motor_c, HIGH);
digitalWrite(l_motor_p, LOW);
digitalWrite(l_motor_n, LOW);
digitalWrite(l_motor_c, LOW);
Serial.println("left");
incomingByte='*';
break;


case 'F': //control for forward
digitalWrite(r_motor_n, LOW); 
digitalWrite(r_motor_p, HIGH);
digitalWrite(r_motor_c, HIGH);
digitalWrite(l_motor_p, HIGH);
digitalWrite(l_motor_n, LOW);
digitalWrite(l_motor_c, HIGH);
Serial.println("forward");
incomingByte='*';
break;


case 'B': //control for backward
digitalWrite(r_motor_n, HIGH); 
digitalWrite(r_motor_p, LOW);
digitalWrite(r_motor_c, HIGH);
digitalWrite(l_motor_p, LOW);
digitalWrite(l_motor_n, HIGH);
digitalWrite(l_motor_c, HIGH);
incomingByte='*';
break;


case 'P': // pump on
digitalWrite(pump, LOW);
Serial.println("pump on");
incomingByte='*';
break;

case 'p': // pump off
digitalWrite(pump, HIGH); 
Serial.println("pump off");
incomingByte='*';
break;

case 'M':
digitalWrite(mop, LOW); // mopper on
Serial.println("mopper on");
incomingByte='*';
break;

case 'm':
digitalWrite(mop, HIGH); // mopper off
Serial.println("mopper off");
incomingByte='*';
break;

delay(5000);
}
}

void DistanceCheck(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2 ); // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  (trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2; //distance in cm

  if (distance <= 25){
    //stop
    digitalWrite(r_motor_n, LOW); 
    digitalWrite(r_motor_p, LOW);
    digitalWrite(l_motor_p, LOW);
    digitalWrite(l_motor_n, LOW);
    delay(500);
    //reverse
    digitalWrite(r_motor_n, HIGH); 
    digitalWrite(r_motor_p, LOW);
    digitalWrite(r_motor_c, HIGH);
    digitalWrite(l_motor_p, LOW);
    digitalWrite(l_motor_n, HIGH);
    digitalWrite(l_motor_c, HIGH);
    delay(3000);
    //left
    digitalWrite(r_motor_n, LOW); 
    digitalWrite(r_motor_p, HIGH);
    digitalWrite(r_motor_c, HIGH);
    digitalWrite(l_motor_p, LOW);
    digitalWrite(l_motor_n, LOW);
    digitalWrite(l_motor_c, LOW);
    delay(5000);
  //incomingByte = 'L';  
  }
  
}
