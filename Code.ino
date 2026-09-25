// ======================================================
// 4-Wheel Obstacle Avoiding Robot
// ESP32 + HC-SR04 + L298N
// ======================================================

// ---------- L298N Motor Driver ----------
#define ENA 25
#define IN1 26
#define IN2 27

#define ENB 13
#define IN3 14
#define IN4 12

// ---------- Ultrasonic Sensor ----------
#define TRIG_PIN 5
#define ECHO_PIN 18

// ---------- Motor Speed ----------
int motorSpeed = 180;   // 0 - 255

// ---------- Obstacle Distance ----------
int obstacleDistance = 20;   // cm


// ======================================================
// SETUP
// ======================================================

void setup() {

  Serial.begin(115200);

  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  stopRobot();

  Serial.println("Obstacle Avoiding Robot Started");
}


// ======================================================
// LOOP
// ======================================================

void loop() {

  long distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  // --------------------------------------------------
  // If obstacle is detected
  // --------------------------------------------------

  if (distance > 0 && distance <= obstacleDistance) {

    stopRobot();
    delay(200);

    // Move backward a little
    moveBackward();
    delay(350);

    stopRobot();
    delay(150);

    // Turn right
    turnRight();
    delay(500);

    stopRobot();
    delay(150);
  }

  // --------------------------------------------------
  // No obstacle
  // --------------------------------------------------

  else {

    moveForward();
  }

  delay(50);
}


// ======================================================
// ULTRASONIC DISTANCE
// ======================================================

long getDistance() {

  // Make sure TRIG is LOW
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send 10 us pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure echo time
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // If no echo
  if (duration == 0) {
    return -1;
  }

  // Convert time to distance
  long distance = duration * 0.0343 / 2;

  return distance;
}


// ======================================================
// MOVE FORWARD
// ======================================================

void moveForward() {

  // Left side
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right side
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}


// ======================================================
// MOVE BACKWARD
// ======================================================

void moveBackward() {

  // Left side
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Right side
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}


// ======================================================
// TURN RIGHT
// ======================================================

void turnRight() {

  // Left side forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right side backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}


// ======================================================
// TURN LEFT
// ======================================================

void turnLeft() {

  // Left side backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Right side forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}


// ======================================================
// STOP
// ======================================================

void stopRobot() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
