/*
 TB6612FNG.h - Library for the Toshiba TB6612FNG motor driver.
 Created by TheDIYGuy999 June 2016
 Released into the public domain.
 */

#include "Arduino.h"
#include "TB6612FNG.h"

// Member definition (code) ========================================================================

// NOTE: The first pin must always be PWM capable, the second only, if the last parameter is set to "true"
// SYNTAX: IN1, IN2, min. input value, max. input value, neutral position width
// invert rotation direction, true = both pins are PWM capable
TB6612FNG::TB6612FNG(int pin1, int pin2, int pwmPin, int minInput, int maxInput, int neutralWidth, boolean invert) { // Constructor
    _pin1 = pin1;
    _pin2 = pin2;
    _pwmPin = pwmPin;
    _minInput = minInput;
    _maxInput = maxInput;
    _minNeutral = (_maxInput + _minInput) / 2 - (neutralWidth / 2);
    _maxNeutral = (_maxInput + _minInput) / 2 + (neutralWidth / 2);
    _controlValueRamp = (_minNeutral + _maxNeutral) / 2;
    _invert = invert;
    _state = 0;
    _previousMillis = 0;
    pinMode(_pin1, OUTPUT);
    pinMode(_pin2, OUTPUT);
    pinMode(_pwmPin, OUTPUT);
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2, LOW);
    digitalWrite(_pwmPin, HIGH);
}

// Drive function ************************************************************

// SYNTAX: Input value, max PWM, ramptime in ms per 1 PWM increment
// true = brake active, false = brake in neutral position inactive
boolean TB6612FNG::drive(int controlValue, int maxPWM, int rampTime, boolean neutralBrake) {
    _controlValue = controlValue;
    _maxPWM = maxPWM;
    _rampTime = rampTime;
    _neutralBrake = neutralBrake;
    
    if (_invert) {
        _controlValue = map (_controlValue, _minInput, _maxInput, _maxInput, _minInput); // invert driving direction
    }
    
    // Fader (allows to ramp the motor speed slowly up & down) --------------------
    if (_rampTime >= 1) {
        unsigned long _currentMillis = millis();
        if (_currentMillis - _previousMillis >= _rampTime) {
            // Increase
            if (_controlValue > _controlValueRamp && _controlValueRamp < _maxInput) {
                _controlValueRamp++;
            }
            // Decrease
            if (_controlValue < _controlValueRamp && _controlValueRamp > _minInput) {
                _controlValueRamp--;
            }
            _previousMillis = _currentMillis;
        }
    }
    else {
        _controlValueRamp = _controlValue;
    }
    
    // H bridge controller -------------------
    if (_controlValueRamp >= _maxNeutral) { // Forward
        digitalWrite(_pin1, HIGH);
        digitalWrite(_pin2, LOW);
        analogWrite(_pwmPin, map(_controlValueRamp, _maxNeutral, _maxInput, 0, _maxPWM));
        return true;
    }
    else if (_controlValueRamp <= _minNeutral) { // Reverse
        digitalWrite(_pin1, LOW);
        digitalWrite(_pin2, HIGH);
        analogWrite(_pwmPin, map(_controlValueRamp, _minNeutral, _minInput, 0, _maxPWM));
        return true;
    }
    else { // Neutral
        if (_neutralBrake) {
            digitalWrite(_pin1, HIGH); // Brake in neutral position active
            digitalWrite(_pin2, HIGH);
        }
        else {
            digitalWrite(_pin1, LOW); // Brake in neutral position inactive
            digitalWrite(_pin2, LOW);
            digitalWrite(_pwmPin, HIGH);
        }
        return false;
    }
}

