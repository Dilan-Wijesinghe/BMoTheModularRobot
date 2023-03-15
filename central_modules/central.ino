// Include the required Wire library for I2C<br>
#include <Wire.h>
#include "Keyboard.h"

void setup() {
  // Start the I2C Bus as Master
  Serial.begin(115200);
  Wire.setSDA(0);
  Wire.setSCL(1);
  Wire.begin();
  // Keyboard.begin();
}

char inChar = ' ';
void loop() {
  if (Serial.available()) {
    inChar = Serial.read();
    // Keyboard.write(inChar);
  }
  // Write a value over to i2c peripheral
  Serial.println("Sending Servo Command!");
  Wire.beginTransmission(0x30);  // transmit to device 0x30
  Wire.write(inChar);
  Wire.endTransmission();  // stop transmitting

  Wire.beginTransmission(0x34);
  Wire.write(inChar);
  Wire.endTransmission();

  Wire.beginTransmission(0x38);
  Wire.write(inChar);
  Wire.endTransmission();

  Wire.beginTransmission(0x42);
  Wire.write(inChar);
  Wire.endTransmission();

  delay(500);
}
