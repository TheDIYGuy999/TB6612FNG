# Advanced Arduino H-Bridge control library

This is an Arduino library for the Toshiba TB6612FNG DC motor driver

## Features:
- Adjustable fader for smooth speed changes
- brake active or not in neutral mode
- selectable input signal range (e.g. 0 - 100, 0 - 1023, -255 - 255 etc.)
- selectable neutral position width. This allows you to optimize it for your joystick
- the motor rotation direction is reversible in software, so you don't have to switch your motor wires, if the direction is reversed
- The end-speed is adjustable during runtime. This allows you to simulate different gear ratios

## Usage

See [example](https://github.com/TheDIYGuy999/TB6612FNG/blob/master/examples/TB6612FNG/TB6612FNG.ino).


(c) 2016 TheDIYGuy999
