# ATtiny85-LED-chase
This repository holds the code (and in the future, schematics) for an ATtiny85-based 3-LED chase sequence.

The goal is to create a simple turn indicator for mounting on the rear rack of a bicycle.
The design must be able to run from batteries. Low part count is a desirable, but secondary consideration.

ATtiny85 was chosen because of its popularity as an alternative to the popular Arduino Uno.

## Preparing the ATtiny85 and the Arduino IDE
You must set up an off the shelf Arduino as a system programmer. DigiKey has a good tutorial on this.

https://www.digikey.com/en/maker/tutorials/2022/how-to-flash-the-arduino-bootloader-to-an-attiny85-ic

There is also an Instructables tutorial that covers sketch uploading, however it uses a different
bootloader than the DigiKey tutorial. My understanding is the David A. Mellis bootloader is preferred as
David is one of the original Arduino developers. (I learned this from the internet, so it could be wrong.)

## About the sketch (code)
The three GPIOs for lighting the LEDs are PB0, PB1, and PB2. These are physical pins 5, 6, and 7 on an
ATtiny85 8-pin DIP. The input to control up/down direction is PB3 (physical pin 2.) The idea behind this
layout is to keep the LEDs physically close on the circuit board.
