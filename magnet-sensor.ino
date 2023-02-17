/* This is an example of reading values from a magnet (hall-effect) sensor
*/

int sensorPin = 0;

int i = 1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  waitForSensor(true);
  blinkFor(i++);
  waitForSensor(false);
  blinkFor(i++);
}

void blinkFor(int count) {
  for (let x = 0; x < count; x++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
}

void waitForSensor(bool val) {
  while(digitalRead(sensorPin)==val) {};
}