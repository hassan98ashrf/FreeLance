#include <NewPing.h>

const int TRIGGER_PIN = 6;  
const int ECHO_PIN = 7;     
const int IN1 = 2;          
const int IN2 = 3;          
const int MOTOR_PIN = 9;    
#define MAX_DISTANCE 200  

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  Serial.begin(9600);
  
  // تحديد اتجاه الحركة الافتراضي للأمام
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void accelerate() {
  for (int pwm = 0; pwm <= 255; pwm += 5) { // Linear PWM ramp
    analogWrite(MOTOR_PIN, pwm);
    delay(50); // Controls acceleration rate
  }
}

void decelerate() {
  for (int pwm = 245; pwm > 0; pwm -= 5) { // Linear PWM ramp[cite: 5]
    analogWrite(MOTOR_PIN, pwm);
    delay(50); // Controls acceleration rate[cite: 5]
  }
}

void brake() {
  digitalWrite(IN1, HIGH); // Short braking[cite: 5]
  digitalWrite(IN2, HIGH);
}

void loop() {
  int distance = sonar.ping_cm(); // Get filtered distance[cite: 5]
  
  if (distance == 0) { // Sensor failure check[cite: 5]
    brake();[cite: 5]
    return;[cite: 5]
  }
  
  if (distance > 170) accelerate();[cite: 5]
  else if (distance > 120) decelerate();[cite: 5]
  else brake();[cite: 5]

  delay(100); // Loop delay for stability[cite: 5]
}