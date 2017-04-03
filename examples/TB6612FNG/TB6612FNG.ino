// This example was cuccessfully tested on an Sparkfun Pro Micro in 8MHz version
// It also works on a Pro Mini, but only, if you don't change the PWM frequency

// Version 1.2

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

// define motor pin numbers
#define motor1_in1 2
#define motor1_in2 4
#define motor1_pwm 5

#define motor2_in1 7
#define motor2_in2 8
#define motor2_pwm 6

// Create motor objects
TB6612FNG Motor1; // Motor 1
TB6612FNG Motor2; // Motor 2

//
// =======================================================================================================
// LIGHTS
// =======================================================================================================
//

void lights() {
  if (Motor1.brakeActive()) { // if braking detected from TB6612FNG motor driver
    //digitalWrite(BRAKELIGHTS, HIGH);
  }
  else {
    //digitalWrite(BRAKELIGHTS, LOW);
  }
}

//
// =======================================================================================================
// MAIN ARDUINO SETUP (1x during startup)
// =======================================================================================================
//
void setup() {

  // Motor pin setup
  // SYNTAX: IN1, IN2, PWM, min. input value, max. input value, neutral position width
  // invert rotation direction true or false
  Motor1.begin(motor1_in1, motor1_in2, motor1_pwm, 0, 1023, 60, false); // Motor 1
  Motor2.begin(motor2_in1, motor2_in2, motor2_pwm, 0, 1023, 60, false); // Motor 2

  // Optional: Motor PWM frequency (Requires the PWMFrequency.h library)
  /*setPWMPrescaler(motor1_pwm, 1); // 123Hz = 256,  492Hz = 64, 3936Hz = 8, 31488Hz = 1
    setPWMPrescaler(motor2_pwm, 1);*/
}

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
  // SYNTAX: Input value, min PWM, max PWM, ramptime in ms per 1 PWM increment
  // false = brake in neutral position inactive
  if (Motor1.drive(speed1, 0, 255, 7, false) ) { // Motor 1
    // returns true, if motor is running, so we can do other stuff here!
  }
  Motor2.drive(speed2, 0, 255, 1, false); // Motor 2
}

//
// =======================================================================================================
// MAIN LOOP
// =======================================================================================================
//

void loop() {
  // Drive the main motor
  driveMotor();

  //Light control
  lights();
}
