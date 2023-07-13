#include <Servo.h>

Servo servo9;
Servo servo10;
int servoPin9 = 9;
int servoPin10 = 10;

int pos9 = 60;              // Initial position of the servo
int targetPos9 = 90;        // Target position of the servo
int easingAmount9 = 5;      // Easing amount (smaller values = smoother movement)
unsigned long easingDelay9 = 50;  // Delay between each incremental movement
unsigned long previousTime9 = 0;

int pos10 = 60;              // Initial position of the servo
int targetPos10 = 90;        // Target position of the servo
int easingAmount10 = 8;      // Easing amount (smaller values = smoother movement)
unsigned long easingDelay10 = 70;  // Delay between each incremental movement
unsigned long previousTime10 = 0;

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

const int motor1Pin = 4;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 5;    // H-bridge leg 2 (pin 7, 2A)
const int enablePin = 3;    // H-bridge enable pin
int potPin = A0;
int motorSpeed = 0;


void setup() {
  servo9.attach(servoPin9);  // Attaches the servo to the specified pin
  servo10.attach(servoPin10);  // Attaches the servo to the specified pin

  // set all the other pins you're using as outputs:
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);


  // set enablePin high so that motor can turn on:
  digitalWrite(enablePin, HIGH);

  servo9.write(90);
  servo10.write(90);

  digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
  digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high
  analogWrite(enablePin, 200);

delay(3000);

}

void loop() {

  if (pos9 == targetPos9) {
    // Generate a new random target position
    targetPos9 = random(70, 130);
  }

  // Calculate the next position using easing
  if (pos9 < targetPos9) {
    pos9 = min(pos9 + easingAmount9, targetPos9);
  } else {
    pos9 = max(pos9 - easingAmount9, targetPos9);
  }


  // Check if the specified delay has passed
  unsigned long currentTime = millis();
  if (currentTime - previousTime9 >= easingDelay9) {
    previousTime9 = currentTime;
  } else {
    // Wait for the remaining time
    delay(easingDelay9 - (currentTime - previousTime9));
  }


  if (pos10 == targetPos10) {
    // Generate a new random target position
    targetPos10 = random(70, 100);
  }

  // Calculate the next position using easing
  if (pos10 < targetPos10) {
    pos10 = min(pos10 + easingAmount10, targetPos10);
  } else {
    pos10 = max(pos10 - easingAmount10, targetPos10);
  }



  // Check if the specified delay has passed
  //unsigned long currentTime = millis();
  if (currentTime - previousTime10 >= easingDelay10) {
    previousTime10 = currentTime;
  } else {
    // Wait for the remaining time
    delay(easingDelay10 - (currentTime - previousTime10));
  }

  // Move the servo to the next position
  servo9.write(pos9);

  // Move the servo to the next position
  servo10.write(pos10);

  digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
  digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high
  int val = analogRead(potPin);
  motorSpeed = map(val, 0, 1023, 0, 255);
  analogWrite(enablePin, motorSpeed);


}
