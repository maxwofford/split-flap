/*
Test program to ensure stepper motor works. This will turn on/off depending on
the signal from an attached switch.
*/

// Include the AccelStepper Library
#include <AccelStepper.h>

// Define step constant
#define MotorInterfaceType 4

// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper myStepper(MotorInterfaceType, 8, 10, 9, 11);

int pinOut = 0;
int pinIn = 1;

void setup() {
	myStepper.setMaxSpeed(1000.0);
	myStepper.setAcceleration(50.0);
	myStepper.setSpeed(200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pinOut, OUTPUT);
  pinMode(pinIn, INPUT);
}

void loop() {
  int clicked = digitalRead(pinIn);

  if (clicked) {
    myStepper.setSpeed(200);
    myStepper.moveTo(myStepper.currentPosition()+1000);
  } else {
    myStepper.setSpeed(0);
    myStepper.moveTo(myStepper.currentPosition());
  }

  myStepper.run();
  digitalWrite(LED_BUILTIN, clicked);
}