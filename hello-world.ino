// Include the AccelStepper Library
#include <AccelStepper.h>

// Define step constant
#define MotorInterfaceType 4

// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper myStepper(MotorInterfaceType, 8, 10, 9, 11);

const int flapCount = 44;
const int stepperSteps = 2048; // specific to my model of 28BYJ-48
const long stepsPerFlap = 1.0 * stepperSteps / flapCount;

const int hallPin = 12; // initializing a pin for the sensor output

const int offset = 4; // this is specific to my flaps

// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(hallPin, INPUT);

  Serial.begin(9600);

  myStepper.setMaxSpeed(1000);
  myStepper.setAcceleration(200.0);
  myStepper.setSpeed(100);
  myStepper.setCurrentPosition(0);

  calibrate();
  displayLetter('0');
}

void calibrate()
{
  bool initialState = hallState();
  moveUntil(!initialState);

  int offsetSteps = offset * stepsPerFlap;
  if (initialState == HIGH)
  {
    myStepper.setCurrentPosition((stepperSteps / 2) + offsetSteps);
  }
  else
  {
    myStepper.setCurrentPosition(0 + offsetSteps);
  }
  // Serial.println(myStepper.currentPosition());
}

bool hallState()
{
  bool val = digitalRead(hallPin);
  digitalWrite(LED_BUILTIN, val);
  return val;
}

// void moveUntilFlap() {
//   if (goalPosition == -1)  { return; }
//   int distance = myStepper.currentPosition() - goalPosition;
//   while (distance < 100 && distance > -100) {
//     myStepper.setSpeed(200);
//     myStepper.move(stepsPerFlap);
//     myStepper.run();
//   }
//   myStepper.setSpeed(0);
//   goalPosition = -1;
// }

void moveUntil(bool state)
{
  while (hallState() != state)
  {
    myStepper.setSpeed(500);
    myStepper.move(100);
    myStepper.run();
  }
  myStepper.setSpeed(0);
}

// void moveToStep(int step)
// {
//   int goal = step * stepsPerFlap;
//   goal += stepperSteps;
//   goalPosition = goal;
// }

// int charToStep(char ch)
// {
//   String flaps = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
//   return flaps.indexOf(flaps);
// }

// int stepToPosition(int step) {
//   return (step * stepsPerFlap);
// }

void blockingRunSpeedToPosition(long position)
{
  // if (myStepper.currentPosition() > position) {
  //   position += stepperSteps;
  // }
  if (position < myStepper.currentPosition()) {
    position += stepperSteps;
    Serial.println("going back, increasing number...");
  } else {
    Serial.println("good number!...");
  }
  Serial.println("starting move to...");
  Serial.println(position - myStepper.currentPosition());
  myStepper.moveTo(position);

  myStepper.setSpeed(500);
  while (myStepper.distanceToGo() != 0) {
    myStepper.runSpeedToPosition();
  }
  if (myStepper.currentPosition() > stepperSteps) {
    myStepper.setCurrentPosition(myStepper.currentPosition() % stepperSteps);
  }
}

void displayLetter(char ch) {
  Serial.println("printing letter...");
  Serial.println(ch);
  String input = String(ch);
  input.toUpperCase();
  const String flaps = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
  int flapIndex = flaps.indexOf(input);
  int goalPosition = flapIndex * stepsPerFlap;
  blockingRunSpeedToPosition(goalPosition);
}

// the loop function runs over and over again forever
void loop()
{
  // blockingRunSpeedToPosition(500);
  // Serial.println(myStepper.currentPosition());
  // delay(1000);
  // blockingRunSpeedToPosition(1000);
  // Serial.println(myStepper.currentPosition());
  // delay(1000);
  // blockingRunSpeedToPosition(100);
  // delay(1000);
  // blockingRunSpeedToPosition(0);
  // delay(1000);
  // String msg = "hello world";
  // for (int i = 0; i < msg.length(); i++) {
  //   displayLetter(msg[i]);
  //   delay(1000);
  // }

  if (Serial.available() > 0)
  {
    char ch = Serial.read();
    if (ch == '\n') { return; }
    Serial.println(ch);
    String input = String(ch);
    input.toUpperCase();
    const String flaps = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    int flapIndex = flaps.indexOf(input);
    int goalPosition = flapIndex * stepsPerFlap;
    Serial.println("indexof");
    Serial.println(flaps.indexOf(input));
    Serial.println("stepsPerFlap");
    Serial.println(stepsPerFlap);
    Serial.println("goalPosition");
    Serial.println(goalPosition);
    Serial.println("distancetogo");
    Serial.println(myStepper.distanceToGo());
    blockingRunSpeedToPosition(goalPosition);
  }
}
