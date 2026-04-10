/*
    ATtiny85 3-LED chase sequence for bicycle indicator: 0, 1, 2, blank, repeat.
    Released to public domain by David Horton, creator of this code.
    See also: https://github.com/DavesCodeMusings/ATtiny85-LED-chase

    To use:
    1. Set direction of chase sequence with logic level on input.
    2. Apply power to boot ATtiny and begin chase sequence.
    3. Power off to cancel chase sequence.
*/

// Physical pins are for ATtiny85 8-pin DIP
#define LED0 0        // physical pin 5
#define LED1 1        // physical pin 6
#define LED2 2        // physical pin 7
#define DIRECTION 3   // physical pin 2
#define DELAY_mS 500


void setup() {
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(DIRECTION, INPUT_PULLUP);  // up/down control, physical pin 2, defaults to upward count
}

// Use direct port manipulation to ensure all LED changes happen at the same time.
// This allows a single current limiting resistor common to all three LEDs.
void loop() {
  if (digitalRead(DIRECTION) == HIGH) {  // counts upward 0, 1, 2, blank
    PORTB = PORTB & 0b11111000;  // Turn off 0, 1, 2
    PORTB = PORTB | 0b00000001;  // Turn on only 0
    delay(DELAY_mS);
    PORTB = PORTB & 0b11111000;  // Turn off 0, 1, 2
    PORTB = PORTB | 0b00000010;  // Turn on only 1
    delay(DELAY_mS);
    PORTB = PORTB & 0b11111000;  // Turn off 0, 1, 2
    PORTB = PORTB | 0b00000100;  // Turn on only 2
    delay(DELAY_mS);
    PORTB = PORTB & 0b11111000;  // Turn off 0, 1, 2
    delay(DELAY_mS);
  }
  else {  // counts downward 2, 1, 0, blank
    PORTB = PORTB & 0b11111000;  // Turn off 0, 1, 2
    PORTB = PORTB | 0b00000100;  // Turn on only 2
    delay(DELAY_mS);
    PORTB = PORTB & 0b11111000;  // Turn off 0, 1, 2
    PORTB = PORTB | 0b00000010;  // Turn on only 1
    delay(DELAY_mS);
    PORTB = PORTB & 0b11111000;  // Turn off 0, 1, 2
    PORTB = PORTB | 0b00000001;  // Turn on only 0
    delay(DELAY_mS);
    PORTB = PORTB & 0b11111000;  // Turn off 0, 1, 2
    delay(DELAY_mS);
  }
}
