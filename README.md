# Motor Library for HG7881CP Motor Driver

## Overview
This library provides an interface for controlling a motor using the HG7881CP motor driver. It allows setting the motor direction and speed via PWM, with an optional inversion setting.

## Features
- Set motor direction (forward or backward)
- Adjust motor speed using a normalized value (0.0 to 1.0)
- Supports inversion for motors with reversed wiring

## Installation
Copy `Motor.h` and `Motor.cpp` into your Arduino project directory.

## Usage

### Include the Library
```cpp
#include <Motor.h>
```

### Initialize the Motor
```cpp
// Define motor control pins
#define MOTOR_A_DIR 8     // Direction pin for Motor A
#define MOTOR_A_SPEED 9   // PWM speed control pin for Motor A
#define MOTOR_B_DIR 4     // Direction pin for Motor B
#define MOTOR_B_SPEED 5   // PWM speed control pin for Motor B


// Create a Motor instance
// Parameters: (dirPin, speedPin, invertDirection, printDebug, label)
// Motors may need inverting direction depending on orientation
Motor motorA(MOTOR_A_DIR, MOTOR_A_SPEED, true, true, 'A');
Motor motorB(MOTOR_B_DIR, MOTOR_B_SPEED, false, true, 'B');
```

### Set Direction
```cpp
motorA.setDirection(Motor::FORWARD); // Set forward direction
motorA.setDirection(Motor::BACKWARD); // Set backward direction
```

### Set Speed
```cpp
motorA.setSpeed(0.5); // Set speed to 50%
motorA.setSpeed(1.0); // Set speed to maximum
motorA.setSpeed(0.0); // Stop the motor
```

### Set Direction and Speed
```cpp
motorA.run(0.5);  // Set speed to 50% forward
motorA.run(1.0);  // Set speed to maximum forward
motorA.run(0.0);  // Stop the motor
motorA.run(-0.5); // Set speed to 50% backwards
motorA.run(1.0);  // Set speed to maximum backwards
```

## Example Code
```cpp
/**
 * H-bridge module dual L9110S/HG7881CP with PID control
 * Motor control tests using gradual speed increase
 * Includes MPU6050 accelerometer (not used in this sketch)
 */

#include <Motor.h> // Include custom Motor control library
#include "config.h"

// Define motor control pins
#define MOTOR_A_DIR 8     // Direction pin for Motor A
#define MOTOR_A_SPEED 9   // PWM speed control pin for Motor A
#define MOTOR_B_DIR 4     // Direction pin for Motor B
#define MOTOR_B_SPEED 5   // PWM speed control pin for Motor B

#define MAX_SPEED 100     // Maximum speed value (as percentage)
#define DELAY 100         // Delay between speed changes (in milliseconds)

// Instantiate motor objects
// Parameters: (dirPin, speedPin, invertDirection, printDebug, label)
// Motor A may need inverting direction depending on orientation
Motor motorA(MOTOR_A_DIR, MOTOR_A_SPEED, true, true, 'A');
// Motor B may need inverting direction depending on orientation
Motor motorB(MOTOR_B_DIR, MOTOR_B_SPEED, false, true, 'B');

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(ROBOT_BAUD_RATE);
  Serial.println("\n\n\n=================================");
  Serial.println("Motor test starting.");
}

void loop() {
  // Move both motors forward gradually
  Serial.println("\n\n\n=================================");
  Serial.println("FORWARD");
  for (int i = 0; i < MAX_SPEED; i++) {
    motorA.run(i / 100.0);  // Set Motor A speed as a float (0.0 to 1.0)
    motorB.run(i / 100.0);  // Set Motor B speed as a float (0.0 to 1.0)
    delay(DELAY);           // Wait before increasing speed
  }

  // Move both motors in reverse gradually
  Serial.println("\n\n\n=================================");
  Serial.println("REVERSE");
  for (int i = 0; i < MAX_SPEED; i++) {
    motorA.run(-i / 100.0); // Set Motor A reverse speed (-1.0 to 0.0)
    motorB.run(-i / 100.0); // Set Motor B reverse speed (-1.0 to 0.0)
    delay(DELAY);           // Wait before increasing reverse speed
  }
}

```

## License
This library is open-source and free to use under the MIT License.

## Author
Created by Paul Bucci, March 19, 2025.

