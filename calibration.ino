// Include the AccelStepper Library
#include <AccelStepper.h>

// Define step constant
#define MotorInterfaceType 4

// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper myStepper(MotorInterfaceType, 8, 10, 9, 11);

const int flapCount = 44;
const int stepperSteps = 2048; // specific to my model of 28BYJ-48
const long stepsPerFlap = stepperSteps / flapCount;

const int hallPin = 12; // initializing a pin for the sensor output

// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(hallPin, INPUT);

  Serial.begin(9600);

  myStepper.setMaxSpeed(1000.0);
  myStepper.setAcceleration(50.0);
  myStepper.setSpeed(200);
  myStepper.setCurrentPosition(0);

  calibrate();
}

void calibrate()
{
  bool initialState = hallState();
  moveUntil(!initialState);
  if (initialState == HIGH)
  {
    myStepper.setCurrentPosition(stepperSteps / 2);
  }
  else
  {
    myStepper.setCurrentPosition(0);
  }
  Serial.println(myStepper.currentPosition());
}

bool hallState()
{
  bool val = digitalRead(hallPin);
  digitalWrite(LED_BUILTIN, val);
  return val;
}

void moveUntil(bool state)
{
  while (hallState() != state)
  {
    myStepper.setSpeed(200);
    myStepper.move(100);
    myStepper.run();
  }
  myStepper.setSpeed(0);
}

void moveToStep(int step)
{
  myStepper.setSpeed(200);
  myStepper.moveTo(step * stepsPerFlap);
  myStepper.run();
}

// the loop function runs over and over again forever
void loop()
{
  if (Serial.available() > 0)
  {
    char value = Serial.read();
    if (value != '0' && value != '1')
    {
      return;
    }
    bool on = value == '0';
    moveUntil(on);
  }
}
