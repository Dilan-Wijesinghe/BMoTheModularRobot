// Include the required Wire library for I2C
#include <Wire.h>
#include <Servo.h>

Servo servo; // servo controller (multiple can exist)

int pin = 20; // PWM pin for servo control

void setup() {
  Wire.setSDA(0); // Set i2c communication to pins 0 and 1
  Wire.setSCL(1); 
  Wire.begin(0x38); // set address of peripheral as 0x38
  Wire.onReceive(receiveEvent);
  servo.attach(pin); // start servo control
  Serial.begin(115200); // start serial monitor
  servo.write(90); // move servo to 90 degrees
  Serial.println("0x42 Booting Up!");
}

void loop() {
}

char c = ' ';
void receiveEvent(int howMany) {
  while (Wire.available())  // loop through all but the last0
    c = Wire.read();  // receive byte as a character
    Serial.println((String)"Command Sent is: " + c);
  if (c == 'd') {
    servo.write(0);
  }

  if (c == 's') {
    servo.write(90);
  }

  if (c == 'a') {
    servo.write(180);
  }
}
