// Include the required Wire library for I2C
#include <Wire.h>
#include <Servo.h>

Servo servo1;
int pos = 0;
void setup() {
  Serial.begin(115200);
  // Set the i2c SDA and SCL ports
  Wire.setSDA(0);
  Wire.setSCL(1);
  Wire.begin(0x30); // 0x30, 0x34, 0x46, 0x50
  Wire.onReceive(receiveEvent);
}

// Buffer to write into
static char buff[100];
void loop() {
}


// }
char c = 'j';
void receiveEvent(int howMany) {
  // Serial.print(c);       // print the character
  while (Wire.available())  // loop through all but the last0
  
    c = Wire.read();  // receive byte as a character
    // Serial.print(c);       // print the character
    Serial.println((String)"Command Sent is: " + c);
    if (c == 'i') {
      servo1.attach(26);
      servo1.write(180);
    }

    if (c == 'k') {
      servo1.attach(26);
      servo1.write(0);
    }

    if (c == 'j') {
      servo1.detach();
    }
  }
  // Serial.println(c);
}