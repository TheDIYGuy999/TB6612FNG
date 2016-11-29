/*
 TB6612FNG.h - Library for the Toshiba TB6612FNG motor driver.
 Created by TheDIYGuy999 June - November 2016
 Released into the public domain.
 
 This is Version 1.1
 
 The pin configuration was moved to the separate begin() function.
 Change your existing programs in accordance with the provided example
 */


#ifndef TB6612FNG_h
#define TB6612FNG_h

#include "Arduino.h"

// Class definition (header) ========================================================================
class TB6612FNG {
    public:
    TB6612FNG();
    void begin(int pin1, int pin2, int pwmPin, int minInput, int maxInput, int neutralWidth, boolean invert);
    boolean drive(int controlValue, int maxPWM, int rampTime, boolean neutralBrake);
    boolean brakeActive();
    
    private:
    int _pin1;
    int _pin2;
    int _pwmPin;
    int _minInput;
    int _maxInput;
    int _minNeutral;
    int _maxNeutral;
    int _controlValue;
    int _controlValueRamp;
    int _maxPWM;
    int _rampTime;
    boolean _neutralBrake;
    boolean _invert;
    unsigned long _previousMillis = 0;
    unsigned long _previousMillisBrake = 0;
    byte _state = 0;
    byte _forward;
    byte _reverse;
    byte _upwards;
    byte _downwards;
};

#endif
