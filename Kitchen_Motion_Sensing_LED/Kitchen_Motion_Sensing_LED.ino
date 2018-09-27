/**
This project was started to fix the issue in my apartment, in which underneath the kitchen cabinets
was to dark to cook properly.

The PIR has a range of about 15m and is very sensitive, at about 110 degree radius.
You might have to place tape around the edge to narrow the sensing view.
It has an interal clock to prevent quick succession of value switching, I have tested it around
1.3 seconds.

Scope Creep:
  - Add a light sensor, so when you enter the kitchen in the dark the lEDs will not turn on
    as bright, blinding you.
  - A button/switch that will switch between constantly on or motion detecting
  - Wireless capability, so you can place strips throughout the kitchen and only have one sensor
  
Materials: (What I used)
  - 3 MOSFETS (IRLB8721)
  - Adafruit Trinket m0
  - PIR
  - NeoPixel RGB LED strip
  - 12V at 5A power wall adapter
  - Power Regulator

@AUTHOR: James Deromedi
@DATE: 4/2/2017

*/
const int PIRINPUT = 1;
const int STRIPONE = 2;
const int STRIPTWO = 4;
const int REDLEDS = 3;            //Seperate to be used in different MOSFET
const int FADESPEEDOFF = 12;      //Higher = slower
const int FADESPEEDON = 20;       //Higher = slower; Different to counteract LEDs min brightness
    
int redValue = 200;               //Max value of red LED brightness, makes strip more 'cool'
bool LEDState = false;            //Flag to know when the LEDs are on or off
bool interupt;   //Used in Interupt

void setup() {
  pinMode(STRIPONE, OUTPUT);
  pinMode(STRIPTWO, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIRINPUT), ISR_MOTION, CHANGE);
  interupt = true;
}//END setup

void loop() {
  //Motion detected; flag = true and LEDS off
  if (interupt && !LEDState) {
    LEDState = !LEDState; //LEDS on
    turnOnLED();
  }
  //No motion detected; flag = false and LEDS on
  if (!interupt && LEDState) {
    LEDState = !LEDState; //LEDS off
    turnOffLED();
  }
}//END main

//--------------------------------------------------------------------------------
/**
 * Interupt service routine for the PIR
 * Switches the interupt flag
 * @Param: None
 * @Return: None
 */
void ISR_MOTION() {
  interupt = !interupt;
}

//--------------------------------------------------------------------------------
/**
 * Controls the LED strips in a PWM fashion to turn on the LEDS. The delay value is slower
 * to counteract the natural min brightness of the LEDs. Otherwise it looks like they turn on
 * much faster than turn off
 * @Param: None
 * @Return: None
 */
void turnOnLED() {
  for (int turnOn = 0; turnOn < 256; turnOn++) {
    //Limits the red value to give the LEDs a more 'cool' color
    if (turnOn < redValue) {
      analogWrite(REDLEDS, turnOn);
    }
    analogWrite(STRIPONE, turnOn);
    analogWrite(STRIPTWO, turnOn);
    delay(FADESPEEDON);
  }

}//END turnOnLED

//--------------------------------------------------------------------------------
/**
 * Controls the LED strips in a PWM fashion to turn off the LEDS
 * @Param: None
 * @Return: None
 */
void turnOffLED() {
  for (int turnOff = 255; turnOff >= 0; --turnOff) {
    //Limits the red value to give the LEDs a more 'cool' color
    if (turnOff < redValue) {
      analogWrite(REDLEDS, turnOff);
    }
    analogWrite(STRIPONE, turnOff);
    analogWrite(STRIPTWO, turnOff);
    delay(FADESPEEDOFF);
  }
  
}//END turnOffLED

