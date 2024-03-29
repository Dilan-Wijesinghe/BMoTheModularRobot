# BMo
Winter Project for my MS in Robotics Winter Quarter!

[![Video Demonstration](https://user-images.githubusercontent.com/32602477/225807597-5707af96-a6a8-4298-8ed3-bf45b2ab135e.jpg)](https://www.youtube.com/watch?v=KZacVYFTs9U)


![All Modules](https://user-images.githubusercontent.com/32602477/225952373-cf8b64a5-5b4b-4249-a0e5-da4ecbfbf8a4.jpg)


### Project Description
BMo is a modular robot consisting of three distinct modules, the brain (BMo), motor (MMo), and hinge (HMo) modules. By connecting these modules in a different configurations, BMo can transform into several different robots. BMo was inspired by the modular robotics kits I had as a child, and was a challenge to myself to do a very intensive hardware project with almost zero experience.

This repository contains the code accompanying BMo.
It also includes the final CAD files I used to create each module.

![BMo in a 'Crab' Configuration](https://user-images.githubusercontent.com/32602477/225952341-b935cd67-b0e1-4c41-ae29-e9a540979084.jpg)

### Hardware
Below is the boards used, and the magnetic connector that made everything possible
* [Adafruit Feather RP2040](https://www.adafruit.com/product/4884)
* [Adafruit Feather ESP32](https://www.adafruit.com/product/3591)
* [Magnetic Pogo Pin](https://www.adafruit.com/product/5413)

### Uploading Code
To upload code onto the RP2040 boards, hold down the BOOTSEL button while inserting a USB-C from your PC.
This should pop open a drive called 'RPI-RP2' onto your PC. From here you can use the Arduino IDE to upload the 
code. 

Note the pins used during setup(), as these pins determine where communication is sent. 
SCL and SDA are used for i2c communication, while pins 26 or 20 are used for servo control.

### Central.io (Brain)
This file contains code necessary for running the central or 'brain' of BMo. It sends i2c messages received 
from the Serial port in order to communicate with the rest of the modules. 
Once the code is loaded, use `screen` or the serial port in the Arduino IDE to send messages.

### Sender.io (Wireless Serial)
This file contains half of the code for the central 'brain' and allows wireless communication through the
ESP32 NOW peer-to-peer protocol. This half uses the serial port to send commands wirelessly to a receiver
board located inside BMo. To connect the sender to the receiver, you need to have both of their MAC
addresses, which can be found by using `WiFi.macAddress()`

### Receiver.io (Wirless Brain)
The file contains the other half of the central 'brain'. It takes the commands from the sender and 
sends them to any of the connected peripherals along its i2c bus. 

### Peripheral.io (Motor Module)
This file contains code necessary for running the peripheral or main 'motor' module, MMo. It receives
i2c messages from the brain and moves according to the given command. By default, `i` moves the servo inside
the module clockwise, while `k` moves it counter-clockwise. Pressing `j` will stop the motor.

To remap, modify the if statements to your desired mapping.

### HMo.io (Hinge Module)
This file contains code necessary for running the peripheral module, HMo. In the same way MMo receives and interprets messages, so
does HMo. Currently, the `e`, `w`, and `q` are mapped to one 0, 90, and 180 degrees. 
