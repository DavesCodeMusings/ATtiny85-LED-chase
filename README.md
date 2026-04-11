# ATtiny85 LED Chase
This repository holds the code (and in the future, schematics and CAD files) for an ATtiny85-based
3-LED chase sequence.

The goal is to create a simple turn indicator for mounting on the rear rack of a bicycle.
The design must be able to run from batteries. Low part count is a desirable, but secondary consideration.

ATtiny85 was chosen because of its popularity as an alternative to the ubiquitous Arduino Uno.
Theoretically, this should also run on a cheaper ATtiny25 (with 2K flash) since the code is minimal.
The ATtiny line also has a variant that runs on power as low as 1.8V, making a single Lithium-ion, CR2032
coin cell, or pair of AA batteries feasible.

## For the love of God, man, why?
Are there off-the-shelf bicycle turn indicators available? Yes. Do any of them blink with a chase sequence
to indicate direction? Not that I've seen. When I'm riding at night, do I want to trust my safety to a
dinky little indicator that, even though it's shaped like a directional arrow, may not be easy to discern
for a vehicle behind me? No, I do not.

Plus, have you ever seen the turn indicators on a Ford Mustang? The three light chase is undeniably cool.

## Preparing the ATtiny85 and the Arduino IDE
The ATtiny cannot be programmed directly from USB with the Arduino IDE. You must set up an off-the-shelf
Arduino as a system programmer. _DigiKey_ has a good tutorial on this.

https://www.digikey.com/en/maker/tutorials/2022/how-to-flash-the-arduino-bootloader-to-an-attiny85-ic

There is also an _Instructables_ tutorial that covers sketch uploading, however it uses a different
bootloader than the _DigiKey_ tutorial. My understanding is the David A. Mellis bootloader is preferred as
David is one of the original Arduino developers. (I learned this from the internet, so it could be wrong.)

https://www.instructables.com/How-to-Program-and-Bootload-ATtiny85-With-USBasp/

## About the sketch (code)
The three GPIOs for lighting the LEDs are PB0, PB1, and PB2. These are physical pins 5, 6, and 7 on an
ATtiny85 8-pin DIP (all on the same side.) The input to control up/down direction is PB3 (physical pin 2,
on the other side.) The idea behind this layout is to keep the LEDs physically close on the circuit board
and allow easy visual separation of inputs and outputs.

Rather than using `digitalWrite()` to control the LED outputs, the PORT B register is accessed directly.
This allows LED states to be changed all at once. And since we can ensure only one LED is ever lit at
any time, a single current-limiting resistor can be used on the common side of all three LEDs.

## Implementation as a turn indicator
This is still forthcoming, but my current thought is to use two ATtinys, one wired as a left indicator
and one wired as a right indicator. A single handlebar mounted control will be used to apply power to
the appropriate device, activating the directional chase sequence.

One advantage of dual ATtinys is the ability to activate both simultaneously as a sort of nighttime
attention getter or a braking indicator. Running both ATtinys would result in a chase sequence moving
from the center outward on both sides.

## What's missing?
Obviously, there needs to be a way to power the device(s) and a control to turn on the indicator in
the proper direction. This hardware is forthcoming.

## Why not a 555 timer?
Somebody's going to ask, so...

An ATtiny25 costs (US)$1.50 on DigiKey. A 555 costs 51 cents. But it requires a resistor and capacitor
for timing, not to mention an up/down counter for the chase sequence. More parts, bigger board. The
ATtiny does all this in a single 8-pin package. Even with a dual ATtiny setup, the part count, board
size, and soldering time is more favorable.
