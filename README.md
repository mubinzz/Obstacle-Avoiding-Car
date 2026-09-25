# Obstacle-Avoiding-Car
# 🚗 ESP32 4-Wheel Obstacle Avoiding Robot

A simple autonomous **4-wheel obstacle-avoiding robot** built using an **ESP32**, **HC-SR04 ultrasonic sensor**, and **L298N motor driver**.

The robot continuously measures the distance in front of it. When an obstacle is detected within a predefined distance, it stops, moves backward, turns right, and continues moving forward.

---

## 📌 Project Overview

This project demonstrates the basic concept of **autonomous mobile robotics** using distance sensing and motor control.

### Main Features

* 🤖 Autonomous movement
* 📡 Ultrasonic obstacle detection
* 🚗 4-wheel drive
* ⚡ ESP32-based control
* 🔧 L298N dual H-bridge motor driver
* 🔄 Automatic obstacle avoidance
* 📊 Real-time distance monitoring through Serial Monitor

---

## 🧰 Components Required

| Component                 |    Quantity |
| ------------------------- | ----------: |
| ESP32 Development Board   |           1 |
| HC-SR04 Ultrasonic Sensor |           1 |
| L298N Motor Driver        |           1 |
| DC Gear Motors            |           4 |
| Robot Car Chassis         |           1 |
| Wheels                    |           4 |
| Battery                   |           1 |
| Jumper Wires              | As required |

---

## 🔌 Pin Configuration

### L298N → ESP32

| L298N Pin | ESP32 GPIO | Function              |
| --------- | ---------: | --------------------- |
| ENA       |    GPIO 25 | Left motor speed      |
| IN1       |    GPIO 26 | Left motor direction  |
| IN2       |    GPIO 27 | Left motor direction  |
| IN3       |    GPIO 14 | Right motor direction |
| IN4       |    GPIO 12 | Right motor direction |
| ENB       |    GPIO 13 | Right motor speed     |

### HC-SR04 → ESP32

| HC-SR04 |   ESP32 | Function |
| ------- | ------: | -------- |
| VCC     |      5V | Power    |
| GND     |     GND | Ground   |
| TRIG    |  GPIO 5 | Trigger  |
| ECHO    | GPIO 18 | Echo     |

### Motor Connections

The two motors on the left side are connected together:

```text
Left Motor 1 ─┐
              ├── L298N OUT1 / OUT2
Left Motor 2 ─┘
```

The two motors on the right side are connected together:

```text
Right Motor 1 ─┐
               ├── L298N OUT3 / OUT4
Right Motor 2 ─┘
```

---

## ⚠️ Important: HC-SR04 and ESP32

The HC-SR04 **ECHO pin can output 5V**, while ESP32 GPIO pins operate at **3.3V logic**.

Therefore, do **not** connect the HC-SR04 ECHO directly to the ESP32.

Use a voltage divider:

```text
HC-SR04 ECHO
     |
    1kΩ
     |
     +──────────> ESP32 GPIO 18
     |
    2kΩ
     |
    GND
```

This reduces the approximately 5V signal to a safer level for the ESP32.

---

## 🔋 Power Connections

A typical arrangement is:

```text
             Battery
                |
        ┌───────┴───────┐
        ↓               ↓
     L298N            Buck Converter
        ↓               ↓
     Motors           ESP32
```

**Important:**

* The motor power should come from a suitable battery.
* Do not power four motors directly from the ESP32.
* Connect **ESP32 GND and L298N GND together**.
* Make sure the battery voltage is appropriate for your motors and L298N.

---

## 🧠 How It Works

The ultrasonic sensor measures the distance between the robot and an obstacle.

The basic logic is:

```text
START
  |
  ↓
Measure distance
  |
  ↓
Is obstacle within 20 cm?
  |
  ├── NO ──→ Move Forward
  |
  └── YES
       |
       ↓
      STOP
       |
       ↓
   Move Backward
       |
       ↓
    Turn Right
       |
       ↓
   Move Forward
       |
       └────────→ Repeat
```

---

## ⚙️ Obstacle Detection

The default obstacle detection distance is:

```cpp
int obstacleDistance = 20;
```

This means the robot considers an object within approximately **20 cm** to be an obstacle.

You can change it:

```cpp
int obstacleDistance = 30;
```

for a 30 cm detection threshold.

---

## 🚀 Motor Speed

Motor speed is controlled using:

```cpp
int motorSpeed = 180;
```

The ESP32 uses PWM to control the L298N enable pins.

The range is:

```text
0   → Motor stopped
255 → Maximum PWM
```

For example:

```cpp
int motorSpeed = 120;
```

will give a lower speed.

---

## 📂 Project Structure

```text
ESP32-Obstacle-Avoiding-Robot/
│
├── obstacle_avoiding_robot.ino
│
└── README.md
```

---

## 💻 Software Requirements

* Arduino IDE
* ESP32 board package for Arduino IDE

### Required Libraries

No external library is required for the basic version.

The code uses built-in Arduino functions such as:

```cpp
digitalWrite()
analogWrite()
pulseIn()
delay()
delayMicroseconds()
```

---

## ▶️ How to Run

### 1. Install ESP32 Board Support

Install the ESP32 board package in Arduino IDE.

### 2. Open the Code

Open:

```text
obstacle_avoiding_robot.ino
```

### 3. Select Your Board

For example:

```text
ESP32 Dev Module
```

### 4. Select the Correct COM Port

Connect the ESP32 to your computer through USB and select the appropriate port.

### 5. Upload

Upload the program to the ESP32.

### 6. Open Serial Monitor

Set the baud rate to:

```text
115200
```

You should see something similar to:

```text
Obstacle Avoiding Robot Started
Distance: 45 cm
Distance: 43 cm
Distance: 38 cm
Distance: 18 cm
Distance: 15 cm
```

When the distance becomes ≤ 20 cm, the robot will avoid the obstacle.

---

## 🛠️ Troubleshooting

### Robot moves backward instead of forward

One or more motors may be connected with reversed polarity.

Swap the two wires of the affected motor.

---

### One side moves in the wrong direction

Check the motor polarity on that side.

The left and right motor groups must rotate so that the robot moves forward together.

---

### Ultrasonic sensor always shows `-1`

Check:

* ECHO connection
* TRIG connection
* GND connection
* Sensor power
* Voltage-divider wiring

---

### Robot continuously turns

Check the ultrasonic sensor readings in the Serial Monitor.

If the distance is always very small, check whether the sensor is pointing toward the chassis, wires, or another nearby object.

---

### Motors don't move

Check:

* L298N motor power
* Battery voltage
* ENA/ENB connections
* Common GND
* Motor connections
* L298N jumper configuration

---

## 🔮 Future Improvements

This project can be upgraded significantly.

### 1. Three Ultrasonic Sensors

Add:

```text
        FRONT
          ↓
       [HC-SR04]
          |
   ┌──────┴──────┐
   ↓             ↓
 LEFT          RIGHT
[HC-SR04]    [HC-SR04]
```

The robot can compare left, front, and right distances and choose a clearer path.

### 2. Servo-Mounted Ultrasonic Sensor

Mount the ultrasonic sensor on a servo:

```text
          Sensor
            |
            ↓
       ┌─────────┐
       │  SERVO  │
       └─────────┘
        ↙   ↓   ↘
      Left Front Right
```

The robot can scan its surroundings before deciding where to turn.

### 3. PWM Speed Control

Different speeds can be used for:

* Forward movement
* Turning
* Reverse movement

### 4. Encoder-Based Control

Wheel encoders can be added for more accurate:

* Distance measurement
* Turning
* Speed control
* Odometry

### 5. PID Control

PID control can be implemented to improve motor synchronization and straight-line movement.

### 6. Advanced Autonomous Navigation

The ESP32 can eventually be combined with:

* LiDAR
* IMU
* Wheel encoders
* Camera
* ROS 2

to develop a more advanced autonomous mobile robot.

---

## 🎯 Learning Objectives

Through this project, you can learn:

* ESP32 GPIO programming
* Ultrasonic distance measurement
* PWM motor control
* H-bridge motor control
* Autonomous decision making
* Basic robotics algorithms
* Sensor-based navigation
* Embedded systems programming

---

## 📜 License

This project is intended for educational and personal robotics development.

Feel free to modify and improve the code for your own projects.

---

## 👨‍💻 Author

**Muhammod Mubin**

Mechatronics Engineering Student
KUET

Interested in:

* 🤖 Robotics
* ⚙️ Mechatronics
* 🧠 Autonomous Systems
* 🚗 Mobile Robotics
* 🔧 Embedded Systems
* 🛰️ Robot Navigation
