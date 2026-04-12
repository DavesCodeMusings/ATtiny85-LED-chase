/*
    ATtiny85 3-LED chase sequence for bicycle indicator: 0, 1, 2, blank, repeat.
    Released to public domain by David Horton, creator of this code.
    See also: https://github.com/DavesCodeMusings/ATtiny85-LED-chase/blob/main/blink_watchdog.ino

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


#include <avr/sleep.h>


ISR (WDT_vect) {       // Fires on watchdog timer interrupt.
  WDTCR |= bit(WDIE);  // Reenable watchdog interrupt each time. 
}

/*
    Configure watchdog timer interrupt and put device into deep sleep.
    This saves battery power compared to using traditional delay()
*/
void wdtSleep(void) {
  const byte prescale = bit(WDP2) | bit(WDP0); // This setting equates to a half-second delay.
  cli();                                       // Block interrupts while setting things up.
  MCUSR = 0;                                   // Clear MCU status register of any previous interrupts.
  WDTCR = bit(WDCE) | bit(WDE);                // Preparation to allow disabling watchdog timer.
  WDTCR = 0;                                   // Reset watchdog to known state (disabled.)
  WDTCR = bit(WDIE) | prescale;                // Enable watchdog interrupts, but not reset, and set prescaler.
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);         // Power down mode gives maximum battery saving potential.
  sleep_enable();
  sei();
  sleep_mode();                                // Go to sleep
  sleep_disable();                             // Program resumes here on wake-up (after interrupt routine fires.)
}

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
    PORTB = PORTB & 0b11111000;  // Turn off LEDs 0, 1, 2
    PORTB = PORTB | bit(LED0);   // Turn on only LED 0
    wdtSleep();
    PORTB = PORTB & 0b11111000;
    PORTB = PORTB | bit(LED1);
    wdtSleep();
    PORTB = PORTB & 0b11111000;
    PORTB = PORTB | bit(LED2);
    wdtSleep();
    PORTB = PORTB & 0b11111000;  // Everything off
    wdtSleep();
  }
  else {  // counts downward 2, 1, 0, blank
    PORTB = PORTB & 0b11111000;  // Turn off LEDs 0, 1, 2
    PORTB = PORTB | bit(LED2);   // Turn on only LED 2
    wdtSleep();
    PORTB = PORTB & 0b11111000;
    PORTB = PORTB | bit(LED1);
    wdtSleep();
    PORTB = PORTB & 0b11111000;
    PORTB = PORTB | bit(LED0);
    wdtSleep();
    PORTB = PORTB & 0b11111000;  // Everything off
    wdtSleep();
  }
}
