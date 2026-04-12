/*
  Blink LED using watchdog interrupt instead of delay() to maximize power saving.
  This is a proof of concept sketch for sleep and watchdog timer wakeups as delays.
  See also: https://www.instructables.com/AVR-Watchdog-as-timed-interrupt/
*/

#include <avr/sleep.h>

// Physical pins are for ATtiny85 8-pin DIP
#define LED0 0         // physical pin 5


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
}

void loop() {
  digitalWrite(LED0, HIGH);
  wdtSleep();  // Instead of a traditional delay(500), we are now powering down for the same amount of time.
  digitalWrite(LED0, LOW);
  wdtSleep();
}
