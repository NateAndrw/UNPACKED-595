// PROJECT  :UNPACKED 595 GCD Calculator
// PURPOSE  :UNPACKED 595 Shirt Register Project
// COURSE   :ISC3U-E
// AUTHOR   :N.ANDREW
// DATE     :2025 05 24
// MCU      :328P (Standalone)
// STATUS   :Working
// REFERENCE:http://darcy.rsgc.on.ca/ACES/TEI3M/Tasks.html#DFlipFlop

uint8_t dataPin = 3;   // Data Input
uint8_t clockPin = 2;  // Clock Signal

int bluePin = 12;   // First Number Representation
int greenPin = 11;  // Second Number Representation
int redPin = 10;    // Greatest Common Denominator Representation

uint8_t number1 = 190;  // First Number Value
uint8_t number2 = 20;   // Second Number Value

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  digitalWrite(clockPin, LOW);

  Serial.begin(9600);
  delay(500);  // Buffer

  // Display First Number on LEDs
  Serial.print("Displaying number1: ");
  Serial.println(number1);
  printBinary(number1);
  setColor(1);  // Blue
  displayBinary(number1);
  delay(5000);

  // Display Second Number on LEDs
  Serial.print("Displaying number2: ");
  Serial.println(number2);
  printBinary(number2);
  setColor(2);  // Green
  displayBinary(number2);
  delay(5000);

  // Display Greatest Common Denominator on LEDs
  uint8_t result = gcd(number1, number2);
  Serial.print("GCD result: ");
  Serial.println(result);
  printBinary(result);
  setColor(3);  // Red
  displayBinary(result);
}

void loop() {
}
// Greatest Common Denominator Using Recursion
uint8_t gcd(uint8_t a, uint8_t b) {
  uint8_t r = a % b;
  if (r == 0) return b;
  return gcd(b, r);
}
// Display Binary Value
void displayBinary(uint8_t value) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, LOW);
    delayMicroseconds(20);
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(20);
  }

  delay(50);  // Buffer

  // Send 8-Bit Binanary Value
  for (int i = 7; i >= 0; i--) {
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, (value >> i) & 1);
    delayMicroseconds(50);
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(50);
  }

  digitalWrite(clockPin, LOW);  // No Extra Flashes
}

void printBinary(uint8_t value) {
  char buffer[9];
  for (int i = 7; i >= 0; i--) {
    buffer[7 - i] = ((value >> i) & 1) ? '1' : '0';
  }
  buffer[8] = '\0';
  Serial.println(buffer);
}

void setColor(uint8_t mode) {
  // Set Multicolour LED
  digitalWrite(bluePin, (mode == 1) ? HIGH : LOW);
  digitalWrite(greenPin, (mode == 2) ? HIGH : LOW);
  digitalWrite(redPin, (mode == 3) ? HIGH : LOW);
}
