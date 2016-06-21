/*
  TB6612FNG.h - Library for the Toshiba TB6612FNG motor driver.
  Created by TheDIYGuy999 June 2016
  Released into the public domain.
*/

#ifndef TB6612FNG_h
#define TB6612FNG_h

#include "Arduino.h"

// Class definition (header) ========================================================================
class TB6612FNG {
  public:
    TB6612FNG(int pin1, int pin2, int pwmPin, int minInput, int maxInput, int neutralWidth, boolean invert);
    void drive(int controlValue, int maxPWM, int rampTime, boolean neutralBrake);

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
    unsigned long _currentMillis;
    byte _state = 0;
};

#endif
