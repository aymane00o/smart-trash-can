#include <AFMotor.h>
#include <Servo.h>
#define trigPin 6      //Trig 
#define echoPin 7      //Echo 
int mindist = 5;
// constants won't change
const int TRIG_PIN  = 6;  // Arduino pin connected to Ultrasonic Sensor's "TRIG" pin
const int ECHO_PIN  = 7;  // Arduino pin connected to Ultrasonic Sensor's "ECHO" pin
const int SERVO_PIN = 9; // Arduino pin connected to Servo Motor's pin (PWM ~)
const int DISTANCE_THRESHOLD = 50; // cm
AF_DCMotor m1(1);//define motor 1 as m1
AF_DCMotor m4(4);//define motor 4 as m4
Servo servo; // create servo object to control a servo
float duration_us, distance_cm;//will change
/*
 get pereentage value  "0" to "100%"  and  conversts it to "0" to "255" which is motor speed used by Arduino
 */
int speed(int b)
{
  return map(b, 0, 100, 0, 255);
}

void setup() {
  Serial.begin(9600); // SERIAL DE TEST // set up Serial library at 9600 bps
  Serial.println("Robojax Motor test!");

  // initial state of motor turn on motor
  m1.setSpeed(0);//motor 1 is turned off to turn on change 0, to 255 
  m4.setSpeed(0); //motor 4 is turned off 
  ///////////////////////////////////////////////////////////////
   pinMode(trigPin, OUTPUT);  //We define Trig as an output
  pinMode(echoPin, INPUT);   //We define Trig as an input
 ///////////////////////////////////////////////////////////////
  Serial.begin (9600);       // initialize serial port
  pinMode(TRIG_PIN, OUTPUT); // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);  // set arduino pin to input mode
  servo.attach(SERVO_PIN);   // attaches the servo on pin 9 to the servo object
  servo.write(0);
}

void loop() {
  uint8_t i;
  
  Serial.println("Motor 1 FORWARD 100% speed");
  m1.run(FORWARD);
  m1.setSpeed(speed(50));
  Serial.println("m4 FORWARD 100%");
  m4.run(FORWARD);
  m4.setSpeed(speed(50));  
  delay(3000);
  // arret des moteurs//
  
  m1.run(RELEASE);
  Serial.println("M1 RELEASE");
  m4.run(RELEASE);
  Serial.println("m4 RELEASE");  
  delay(3000); 

  //marche arriere/

  Serial.println("M1 BACKWARD 80%");
  m1.run(BACKWARD );
  m1.setSpeed(speed(80));
  Serial.println("m4 BACKWARD 60%");
  m4.run(BACKWARD );
  m4.setSpeed(speed(60));
  delay(3000);
  m1.run(RELEASE);
  Serial.println("M1 RELEASE");
  m4.run(RELEASE);
  Serial.println("m4 RELEASE");  
  delay(3000);   
  Serial.println("=============");
  //////////////////////////////////////////////
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration_us = pulseIn(ECHO_PIN, HIGH);
  distance_cm = 0.1 * duration_us;
  if(distance_cm < DISTANCE_THRESHOLD)
    servo.write(106); // rotate servo motor to 106 degree
  else
    servo.write(0);  // rotate servo motor to 0 degree
    Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(1000);
}
