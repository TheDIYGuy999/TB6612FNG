// This example was cuccessfully tested on an Sparkfun Pro Micro in 8MHz version
// It also works on a Pro Mini, but only, if you don't change the PWM frequency

//
// =======================================================================================================
// INCLUDE LIRBARIES
// =======================================================================================================
//
#include <TB6612FNG.h> // https://github.com/TheDIYGuy999/TB6612FNG

// Optional for motor PWM frequency adjustment:
//#include <PWMFrequency.h> // https://github.com/kiwisincebirth/Arduino/tree/master/libraries/PWMFrequency

//
// =======================================================================================================
// CREATE MOTOR OBJECTS
// =======================================================================================================
//

// Initialize TB6612FNG H-Bridge
#define motor1_in1 2 // define motor pin numbers
#define motor1_in2 4
#define motor1_pwm 5

#define motor2_in1 7
#define motor2_in2 8
#define motor2_pwm 6

// SYNTAX: IN1, IN2, PWM, min. input value, max. input value, neutral position width
// invert rotation direction true or false
TB6612FNG Motor1(motor1_in1, motor1_in2, motor1_pwm, 0, 1023, 60, false); // Motor 1
TB6612FNG Motor2(motor2_in1, motor2_in2, motor2_pwm, 0, 1023, 60, false); // Motor 2

//
// =======================================================================================================
// DRIVE MOTOR
// =======================================================================================================
//

void driveMotor() {

  int speed1 = 512;
  int speed2 = 512;
  
  // Read Potentiometer
  speed1 = analogRead(A0); // 0 - 1023
  speed2 = analogRead(A1); // 0 - 1023

  // ***************** Note! The ramptime is intended to protect the gearbox! *******************
  // SYNTAX: Input value, max PWM, ramptime in ms per 1 PWM increment
  // false = brake in neutral position inactive
  Motor1.drive(speed1, 255, 7, false); // Motor 1
  Motor2.drive(speed2, 255, 1, false); // Motor 2
}

//
// =======================================================================================================
// MAIN ARDUINO SETUP (1x during startup)
// =======================================================================================================
//
void setup() {
  // Optional: Motor PWM frequency (Requires the PWMFrequency.h library)
/*setPWMPrescaler(motor1_pwm, 1); // 123Hz = 256,  492Hz = 64, 3936Hz = 8, 31488Hz = 1
  setPWMPrescaler(motor2_pwm, 1);*/
}

//
// =======================================================================================================
// MAIN LOOP
// =======================================================================================================
//

void loop() {
  // Drive the main motor
  driveMotor();
}
