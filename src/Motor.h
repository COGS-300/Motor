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
       bool reversed; ///< Flag to determine if direction should be reversed
       bool debug;    ///< Flag to print debug info.
       char label;
   
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
        * @param reversed If true, inverts the direction value to reverse motor control behavior (forward is backward and backward is forward).
        * @param debug If true, prints all debug info.
        * @param label A character label for the motor.
        */
       Motor(int dir_pin, int speed_pin, bool reversed, bool debug, char label);
       
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
       void run(float speed);
 };
 
 #endif // Motor_h
 