/**
 * H-bridge module dual L9110S/HG7881CP with PID control
 * Motor control tests using gradual speed increase
 * Includes MPU6050 accelerometer (not used in this sketch)
 */

#include <Motor.h> // Include custom Motor control library

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
  Serial.begin(9600);
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
