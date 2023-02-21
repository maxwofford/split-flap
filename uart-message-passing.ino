// These numbers from the pinout image of the Raspberry Pi Pico. They are linked to UART0, which is referred to as "Serial1"
// On a different board, they will be different numbers.
const int pinTx = 12;
const int pinRx = 13;
String message;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);      // set LED pin as output
  digitalWrite(LED_BUILTIN, LOW);    // switch off LED pin

  Serial.begin(9600);               // initialize serial communication at 9600 bits per second:
  Serial1.setRX(pinRx);
  Serial1.setTX(pinTx);
  Serial1.begin(9600);            // initialize UART with baud rate of 9600

  blinkFor(2);
}

void blinkFor(int count) {
  for (int i = 0; i < count; i++) {
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void sendSerial(char ch) {
  Serial1.write(ch);
  Serial.write(ch); // this serial instance is just for logging!
}

void handleSerial(char ch) {
  // new characters are added! let's remember them for later
  message += ch;
  if (ch != '|') {
    return;
  }
  Serial.write("got pipe, outputting...");
  // end of line, let's execute the message!
  int digit = message[0] - '0';
  blinkFor(digit);
  for (int i = 1; i < message.length(); i++) {
    sendSerial(message[i]);
  }
  message = "";
}

// the loop function runs over and over again forever
void loop() {
  if (Serial.available() > 0) {
    char ch = Serial.read();
    handleSerial(ch);
  }
  if (Serial1.available() > 0) {
    char ch = Serial1.read();
    handleSerial(ch);
  }
}
