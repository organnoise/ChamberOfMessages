/*
 Debounce

 Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
 press), the output pin is toggled from LOW to HIGH or HIGH to LOW.  There's
 a minimum delay between toggles to debounce the circuit (i.e. to ignore
 noise).

 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached from pin 2 to +5V
 * 10K resistor attached from pin 2 to ground

 * Note: On most Arduino boards, there is already an LED on the board
 connected to pin 13, so you don't need any extra components for this example.


 created 21 November 2006
 by David A. Mellis
 modified 30 Aug 2011
 by Limor Fried
 modified 28 Dec 2012
 by Mike Walters

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Debounce
 */
#define NUM_BUTTONS 2
// constants won't change. They're used here to
// set pin numbers:
const int buttonPin[] = {3,5};   // the number of the pushbutton pin

// Variables will change:
int buttonState[NUM_BUTTONS];             // the current reading from the input pin
int lastButtonState[NUM_BUTTONS];   // the previous reading from the input pin
int reading[NUM_BUTTONS];

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime[NUM_BUTTONS];  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPin[i], INPUT);
    lastButtonState[i] = LOW;
    lastDebounceTime[i] = 0;
    reading[i] = 0;
  }
}

void loop(){
  updateButton();
  }

void updateButton() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    // read the state of the switch into a local variable:
    reading[i] = digitalRead(buttonPin[i]);

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH),  and you've waited
    // long enough since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading[i] != lastButtonState[i]) {
      // reset the debouncing timer
      lastDebounceTime[i] = millis();
    }

    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading[i] != buttonState[i]) {
        buttonState[i] = reading[i];

        serialPrint(i, buttonState[i]);
      }
    }
    // save the reading.  Next time through the loop,
    // it'll be the lastButtonState:
    lastButtonState[i] = reading[i];
  }
}

void serialPrint(int section,int data) {
  //Serial.print("[");
  Serial.print(section);
  Serial.print(" ");
  Serial.print(data);
  Serial.println();
  //Serial.println("]");
}
