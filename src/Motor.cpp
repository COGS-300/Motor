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
  * @param reversed If true, reverses the direction value to reverse motor control behavior (default: false).
  * @param debug If true, prints all debug info.
  * @param label Character label for the motor.
  */
 Motor::Motor(
  int dir_pin, 
  int speed_pin, 
  bool reversed, 
  bool debug, 
  char label) : 
      dirPin(dir_pin),
      speedPin(speed_pin),
      reversed(reversed),
      debug(debug),
      label(label)
 {
    if (debug) {
      char buffer[150];
      sprintf(buffer, "Setting motor %c to pin %d for direction and pin %d for speed.", label, dirPin, speedPin);
      Serial.println(buffer);
    }
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
 int Motor::setSpeed(float speed)
 {
     int pwmSpeed = int(trunc(speed * MAX_SPEED));
     analogWrite(speedPin, pwmSpeed);
     return pwmSpeed;
 }
 
 /**
 * @brief Runs the motor at the specified speed and direction.
 * 
 * This function sets both the direction and speed of the motor based on the 
 * sign and magnitude of the input value. A positive speed runs the motor 
 * forward, a negative speed runs it backward, and zero stops the motor.
 * 
 * @param speed A float between -1.0 and 1.0 representing the desired speed and direction.
 *              Positive values run the motor forward, negative values backward.
 */
 void Motor::run(float speed) {
  int dir = FORWARD;
  if (speed < 0) {
    dir = !dir;
  }
  if (reversed) {
    dir = !dir;
  }

  // Put everything into the right range
  speed = abs(constrain(speed, -1.0, 1.0));

  if (dir == FORWARD) {
    setDirection(FORWARD);
    setSpeed(1.0 - speed);
  } else {
    setDirection(BACKWARD);
    setSpeed(speed);
  }
    
    // Debugging
    if (debug) {
      char buffer[150];
      char floatStr[10];
      dtostrf(speed, 5, 2, floatStr);
      sprintf(buffer, "Set speed to %s and direction %d for motor %c.", floatStr, dir, label);
      Serial.println(buffer);
    }
}