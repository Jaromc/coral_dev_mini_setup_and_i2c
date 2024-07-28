#include <Wire.h> 

int LED = 13;
char x = 0;
void setup() {
  // Define the LED pin as Output
  pinMode (LED, OUTPUT);
  Serial.begin(9600);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int bytes) {
  x = Wire.read();
  Serial.println(x, HEX);
}

void loop() {

  if (x == '0') {
    Serial.print("0");
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
  }

  if (x == '3') {
    Serial.println("3");
    digitalWrite(LED, HIGH);
    delay(400);
    digitalWrite(LED, LOW);
    delay(400);
  }
}