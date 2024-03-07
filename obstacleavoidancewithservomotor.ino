#include <Servo.h> // Servo motor library
#include <NewPing.h> // Ultrasonic sensor function library

const int LeftForward = 3;   // L298N control pins
const int LeftBackward = 2;
const int RightForward = 4;
const int RightBackward = 5;

#define trig_pin 10 // Sensor pins - analog input 1
#define echo_pin 11 // Analog input 2
#define maximum_distance 200

boolean goesForward = false;
int distance = 0; // Initialize distance to 0

NewPing sonar(trig_pin, echo_pin, maximum_distance); // Sensor function
Servo servo_motor; // Servo name

void setup() {
  Serial.begin(9600);
  pinMode(RightForward, OUTPUT);
  pinMode(LeftForward, OUTPUT);
  pinMode(LeftBackward, OUTPUT);
  pinMode(RightBackward, OUTPUT);
  servo_motor.attach(9); // Servo pin
  servo_motor.write(115);
  delay(2000);
  distance = readPing(); // Update distance after initialization
}

void loop() {
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  Serial.print("Ping: ");
  Serial.print(distance); // Print the current distance
  Serial.println("cm");

  if (distance <= 20) {
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);
    
    if (distanceRight >= distanceLeft) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }
  } else {
    moveForward();
  }

  distance = readPing(); // Update the distance in each iteration
}

int lookRight() {
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft() {
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  digitalWrite(RightForward, LOW);
  digitalWrite(LeftForward, LOW);
  digitalWrite(RightBackward, LOW);
  digitalWrite(LeftBackward, LOW);
}

void moveForward() {
  if (!goesForward) {
    goesForward = true;
    digitalWrite(LeftForward, HIGH);
    digitalWrite(RightForward, HIGH);
    digitalWrite(LeftBackward, LOW);
    digitalWrite(RightBackward, LOW);
  }
}

void moveBackward() {
  goesForward = false;
  digitalWrite(LeftBackward, HIGH);
  digitalWrite(RightBackward, HIGH);
  digitalWrite(LeftForward, LOW);
  digitalWrite(RightForward, LOW);
}

void turnRight() {
  digitalWrite(LeftForward, HIGH);
  digitalWrite(RightBackward, HIGH);
  digitalWrite(LeftBackward, LOW);
  digitalWrite(RightForward, LOW);
  delay(500);
  digitalWrite(LeftForward, HIGH);
  digitalWrite(RightForward, HIGH);
  digitalWrite(LeftBackward, LOW);
  digitalWrite(RightBackward, LOW);
}

void turnLeft() {
  digitalWrite(LeftBackward, HIGH);
  digitalWrite(RightForward, HIGH);
  digitalWrite(LeftForward, LOW);
  digitalWrite(RightBackward, LOW);
  delay(500);
  digitalWrite(LeftForward, HIGH);
  digitalWrite(RightForward, HIGH);
  digitalWrite(LeftBackward, LOW);
  digitalWrite(RightBackward, LOW);
}
