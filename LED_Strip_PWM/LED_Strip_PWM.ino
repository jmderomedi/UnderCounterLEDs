// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!

#define STRIPTWO 3
#define STRIPONE 2

#define FADESPEED 4     // make this higher to slow down

void setup() {
  pinMode(STRIPONE, OUTPUT);
  pinMode(STRIPTWO, OUTPUT);
}


void loop() {
  int turnOn, turnOff;

  //On motion sensor activation
  //Strip 1 turning on
  for (turnOn = 0; turnOn < 256; turnOn++) {
    analogWrite(STRIPONE, turnOn);
    analogWrite(STRIPTWO, turnOn);
    delay(FADESPEED);
  }

  // fade from yellow to green
  for (turnOff = 255; turnOff > 0; turnOff--) {
    analogWrite(STRIPONE, turnOff);
    analogWrite(STRIPTWO, turnOff);
    delay(FADESPEED);
  }


}
