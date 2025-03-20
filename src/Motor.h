/**
 * Motor.h - Library for interfacing with HG7881CP motor driver
 * 
 * This library provides a simple interface to control a motor using the HG7881CP motor driver.
 * It allows setting the motor direction and speed using PWM.
 * 
 * Created by Paul Bucci, March 19, 2025
 */

 #ifndef Motor_h
 #define Motor_h
 
 #include <Arduino.h>
 
 /**
  * @class Motor
  * @brief A class to control a motor using the HG7881CP motor driver.
  */
 class Motor {
     private:
       int dirPin;    ///< Digital pin for motor direction control
       int speedPin;  ///< PWM pin for motor speed control
       bool inverted; ///< Flag to determine if speed values should be inverted
   
     public:
       /**
        * @brief Motor direction constants.
        */
       static constexpr bool FORWARD = HIGH;   ///< Constant for forward direction
       static constexpr bool BACKWARD = LOW;   ///< Constant for backward direction
       
       /**
        * @brief Motor speed range constants.
        */
       static constexpr int MAX_SPEED = 255;   ///< Maximum PWM speed value
       static constexpr float MIN_SPEED = 0.0; ///< Minimum normalized speed value
 
       /**
        * @brief Constructor to initialize the motor.
        * @param dir_pin The pin connected to the direction control input of the motor driver.
        * @param speed_pin The pin connected to the PWM input of the motor driver.
        * @param invert If true, inverts the speed value to reverse motor control behavior.
        */
       Motor(int dir_pin, int speed_pin, bool invert);
       
       /**
        * @brief Sets the motor direction.
        * @param direction Use Motor::FORWARD or Motor::BACKWARD.
        */
       void setDirection(bool direction);
       
       /**
        * @brief Sets the motor speed using a normalized value (0.0 to 1.0).
        * @param normalizedSpeed A float between 0.0 and 1.0 representing the motor speed.
        * @return The actual PWM value set (between 0 and 255).
        */
       int setSpeed(float normalizedSpeed);
 };
 
 #endif // Motor_h
 