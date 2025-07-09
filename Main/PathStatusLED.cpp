#include <Arduino.h>
#include "PathStatusLED.h"
#define PIN_LED_GREEN 9
#define PIN_LED_RED 8
// the setup function runs once when you press reset or power the board
PathStatusLED :: PathStatusLED() {
  // initialize digital pin PIN_LED as an output.
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
}
// the loop function runs over and over again forever
void PathStatusLED :: activateStatusLED(bool pathClearStatus) {
  if (pathClearStatus == true) {
    digitalWrite(PIN_LED_RED, LOW);
    digitalWrite(PIN_LED_GREEN, HIGH);
  }
  else {
    digitalWrite(PIN_LED_GREEN, LOW);
    digitalWrite(PIN_LED_RED, HIGH);
  }
}