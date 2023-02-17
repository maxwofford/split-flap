/* Simple test of message passing. This sketch can be loaded onto multiple
 * devices, then daisy-chain them. If "1347" is passed via serial to the first device in the chain...
 - the first device will flash once
 - second device will flash three times
 - the third device will flash four times
 - the "7" is inconsequential and will be dropped
 *
 * It should also be noted this is a sequential example. This is intentional due
 * to power constraints of the project (driving multiple steppers at the same
 * time is too much, so we're moving one at a time)
 */

#include <SoftwareSerial.h>

#define pinOut 0
#define pinIn 1

SoftwareSerial pinSerial = SoftwareSerial(pinIn, pinOut);

void setup() {
  while (!Serial) { }
  Serial.begin(19200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(pinIn, INPUT);
  pinMode(pinOut, OUTPUT);
  pinSerial.begin(9600);
}

void blinkFor(long sec) {
  for (int i = 2; i < sec; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
}

void handleMessage(char first_character) {
  if (!first_character) return;

  if (first_character >= '0' && first_character <= '9') {
    long digit = first_character - '0';
    blinkFor(digit);
  }
}

void passMessage(String message) {
  if (message.length() == 0) return;
  // something here...
  pinSerial.write("hello");
}

void handleSerial(char first_character, String other_characters) {
  handleMessage(first_character);
  passMessage(other_characters);
}

void checkPinSerial() {
  if (pinSerial.available() == 0) return;

  char first_character = pinSerial.read();
  String other_characters = "";
  while (pinSerial.available() != 0) {
    other_characters += pinSerial.read();
  }

  handleSerial(first_character, other_characters);
}

void checkUsbSerial() {
  if (Serial.available() == 0) return;

  char first_character = Serial.read();
  String other_characters = "";
  while (Serial.available() != 0) {
    other_characters += Serial.read();
  }

  handleSerial(first_character, other_characters);
}

void loop() {
  checkUsbSerial();
  checkPinSerial();
}