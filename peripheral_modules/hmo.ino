// Include the required Wire library for I2C
#include <Wire.h>
#include <Servo.h>

Servo servo;  // servo controller (multiple can exist)

int pin = 20;  // PWM pin for servo control

void setup() {
  Serial.begin(115200);  // start serial monitor
  Wire.setSDA(0);        // Set i2c communication to pins 0 and 1
  Wire.setSCL(1);
  Wire.begin(0x42);  // set address of peripheral as 0x38
  Wire.onReceive(receiveEvent);
  servo.attach(pin);  // start servo control
  servo.write(90);    // move servo to 90 degrees
  Serial.println("0x42 Booting Up!");
  delay(2000);
  servo.detach();
}

char l = ' ';
void loop() {
  // Serial.println("I am alive");
  if (Serial.available()) {
    l = Serial.read();
    if (l == 'c') {
      servo.attach(pin);
      servo.write(0);
      delay(500);  // delay(2000);
    }

    if (l == 'x') {
      servo.attach(pin);
      servo.write(90);
      delay(500);  // delay(2000);
    }

    if (l == 'z') {
      servo.attach(pin);
      servo.write(180);
      delay(500);  // delay(2000);
    }
    if (l == 'v') {
      servo.detach();
    }
  }
  // servo.detach();
}

char c = ' ';
void receiveEvent(int howMany) {
  while (Wire.available()) {  // loop through all but the last0
    c = Wire.read();          // receive byte as a character
    Serial.println((String) "Command Sent is: " + c);
    if (c == 'e') {
      servo.attach(pin);
      servo.write(0);
      delay(500);
    }

    if (c == 'w') {
      servo.attach(pin);
      servo.write(90);
      delay(500);
    }

    if (c == 'q') {
      servo.attach(pin);
      servo.write(180);
      delay(500);
    }
    servo.detach();
  }
}
