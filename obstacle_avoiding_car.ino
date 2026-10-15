 /*
  Obstacle-avoiding 4WD car (Arduino Uno / Nano)
  - 1x L298N driving 4 BO motors (left pair on OUT1/OUT2, right pair on OUT3/OUT4)
  - HC-SR04 ultrasonic sensor mounted on an SG90 servo
*/
#include <Servo.h>

// ---------- Pin map ----------
#define ENA 5    // PWM speed, left motors
#define ENB 6    // PWM speed, right motors
#define IN1 7    // left motors
#define IN2 8
#define IN3 2    // right motors
#define IN4 4
#define SERVO_PIN 9
#define TRIG 10
#define ECHO 11

// ---------- Settings ----------
const int  SPEED          = 170;   // 0-255 (lower if motors too fast)
const int  TURN_SPEED     = 180; 
const int  STOP_DIST_CM   = 20;    // obstacle threshold
const int  SERVO_CENTER   = 90;
const int  SERVO_LEFT     = 160;
const int  SERVO_RIGHT    = 20;
const int  TURN_TIME_MS   = 450;   // tune: time for ~90 degree turn
const int  BACK_TIME_MS   = 350;

Servo scanServo;

// ---------- Motor helpers --------- 
void setSpeed(int l, int r) {
  analogWrite(ENA, l);
  analogWrite(ENB, r);
}

void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  setSpeed(SPEED, SPEED);
}

void backward() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  setSpeed(SPEED, SPEED);
}

void turnLeft() {   // spin in place: left backward, right forward
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  setSpeed(TURN_SPEED, TURN_SPEED);
}

void turnRight() {  // left forward, right backward
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  setSpeed(TURN_SPEED, TURN_SPEED);
}

void stopCar() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  setSpeed(0, 0);
}

// ---------- Ultrasonic ----------
long readDistanceOnce() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long dur = pulseIn(ECHO, HIGH, 30000UL);   // 30 ms timeout (~5 m)
  if (dur == 0) return 400;                  // no echo = far away
  return dur * 0.034 / 2;
}

// median of 3 readings to reject noise
long getDistance() {
  long a = readDistanceOnce(); delay(10);
  long b = readDistanceOnce(); delay(10);
  long c = readDistanceOnce();
  if (a > b) { long t = a; a = b; b = t; }
  if (b > c) { long t = b; b = c; c = t; }
  if (a > b) { long t = a; a = b; b = t; }
  return b;
}

long lookAt(int angle) {
  scanServo.write(angle);
  delay(450);              // let servo settle
  long d = getDistance();
  return d;
}

// ---------- Setup / Loop ----------
void setup() {
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(TRIG, OUTPUT); pinMode(ECHO, INPUT);

  scanServo.attach(SERVO_PIN);
  scanServo.write(SERVO_CENTER);
  stopCar();
  delay(1500);             // time to place the car down
}

void loop() {
  long front = getDistance();

  if (front > STOP_DIST_CM) {
    forward();
  } else {
    stopCar();
    delay(150);

    backward();
    delay(BACK_TIME_MS);
    stopCar();

    long left  = lookAt(SERVO_LEFT);
    long right = lookAt(SERVO_RIGHT);
    scanServo.write(SERVO_CENTER);
    delay(300);

    if (left < STOP_DIST_CM && right < STOP_DIST_CM) {
      // dead end: turn around (~180 deg)
      turnRight();
      delay(TURN_TIME_MS * 2);
    } else if (left > right) {
      turnLeft();
      delay(TURN_TIME_MS);
    } else {
      turnRight();
      delay(TURN_TIME_MS);
    }
    stopCar();
    delay(100);
  }
  delay(40);
}
