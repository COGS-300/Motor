/**
 * Motor.cpp - Implementation of the Motor class for HG7881CP motor driver
 * 
 * This file contains the implementation of the Motor class, which allows controlling a motor's speed
 * and direction using the HG7881CP motor driver.
 * 
 * Created by Paul Bucci, March 19, 2025
 */

 #include <Arduino.h>
 #include "Motor.h"
 
 /**
  * @brief Constructor to initialize the motor.
  * 
  * Sets up the direction and speed pins as output and stores the inversion flag.
  * 
  * @param dir_pin The pin connected to the direction control input of the motor driver.
  * @param speed_pin The pin connected to the PWM input of the motor driver.
  * @param invert If true, inverts the speed value to reverse motor control behavior (default: false).
  */
 Motor::Motor(int dir_pin, int speed_pin, bool invert) : dirPin(dir_pin), speedPin(speed_pin), inverted(invert)
 {
     pinMode(dirPin, OUTPUT);
     pinMode(speedPin, OUTPUT);
 }
 
 /**
  * @brief Sets the motor direction.
  * 
  * This function controls the direction of the motor by setting the direction pin HIGH (forward)
  * or LOW (backward).
  * 
  * @param direction Use Motor::FORWARD or Motor::BACKWARD to set the direction.
  */
 void Motor::setDirection(bool direction)
 {
     digitalWrite(dirPin, direction);
 }
 
 /**
  * @brief Sets the motor speed using a normalized value (0.0 to 1.0).
  * 
  * This function takes a floating-point value between 0.0 and 1.0, scales it to a 0-255 PWM range,
  * and writes it to the speed control pin. If the motor is inverted, the speed value is reversed.
  * 
  * @param normalizedSpeed A float between 0.0 and 1.0 representing the desired motor speed.
  * @return The actual PWM value set (between 0 and 255).
  */
 int Motor::setSpeed(float normalizedSpeed)
 {
     // Ensure speed is within the valid range
     if (normalizedSpeed <= MIN_SPEED)
     {
         normalizedSpeed = 0;
     }
     normalizedSpeed = constrain(normalizedSpeed, 0.0, 1.0);
 
     // Invert speed if necessary
     if (inverted)
     {
         normalizedSpeed = 1.0 - normalizedSpeed;
     }
 
     Serial.print("Normalized speed: ");
     Serial.println(normalizedSpeed);
 
     // Convert normalized speed to PWM range (0-255)
     int pwmSpeed = int(trunc(normalizedSpeed * MAX_SPEED));
     analogWrite(speedPin, pwmSpeed);
     return pwmSpeed;
 }
 