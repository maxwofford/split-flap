/* pseudocode keep track of where a drum is and rotate based on sensor value */

int homePosition;
int currPosition = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  findHome();
}

void loop() {
  if (Serial.available() > 0) {
    char ch = Serial.read();
    goTo(ch);
  }
}

void findHome() {
  while(isSensor(false)) {
    moveDrum();
  }
  // stopDrum();
  Serial.write("I found my home!")
  homePosition = getDrum();
}

void goTo(char character) {
  Serial.write("Moving to character '", character, "'...");
  String flaps = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
  flaps.indexOf(character);
}

bool isSensor(bool val) {
  // this is a stubbed method
  return (currPosition == 0) == val;
}

void moveDrum() {
  // this is a stubbed method
  currPosition = (currPosition + 1) % 2038
}

int getDrum() {
  // this is a stubbed method
  return currPosition
}