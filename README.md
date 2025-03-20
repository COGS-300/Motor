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
#include "Motor.h"
```

### Initialize the Motor
```cpp
// Define motor control pins
#define DIR_PIN 5
#define SPEED_PIN 6

// Create a Motor instance
Motor myMotor(DIR_PIN, SPEED_PIN, false); // Set false if motor direction does not need to be inverted
```

### Set Direction
```cpp
myMotor.setDirection(Motor::FORWARD); // Set forward direction
myMotor.setDirection(Motor::BACKWARD); // Set backward direction
```

### Set Speed
```cpp
myMotor.setSpeed(0.5); // Set speed to 50%
myMotor.setSpeed(1.0); // Set speed to maximum
myMotor.setSpeed(0.0); // Stop the motor
```

## Example Code
```cpp
#include <Arduino.h>
#include "Motor.h"

#define DIR_PIN 5
#define SPEED_PIN 6

Motor motor(DIR_PIN, SPEED_PIN, false);

void setup() {
    Serial.begin(9600);
    motor.setDirection(Motor::FORWARD);
}

void loop() {
    for (float speed = 0.0; speed <= 1.0; speed += 0.1) {
        motor.setSpeed(speed);
        delay(500);
    }
    for (float speed = 1.0; speed >= 0.0; speed -= 0.1) {
        motor.setSpeed(speed);
        delay(500);
    }
}
```

## License
This library is open-source and free to use under the MIT License.

## Author
Created by Paul Bucci, March 19, 2025.

