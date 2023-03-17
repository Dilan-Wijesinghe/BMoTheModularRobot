#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

// MAC ADDRESSES
// Device 1: 10:97:BD:3F:E0:44
// Device 2: 24:4C:AB:DA:14:CC

// REPLACE WITH THE MAC Address of your receiver 
uint8_t broadcastAddress[] = {0x10, 0x97, 0xBD, 0xD3F, 0xE0, 0x44};

String success;

typedef struct msg {
  char cmd;
  // Add more stuff if Needed
  // int, float, bool etc.
} msg;

msg input; // Incoming Input from the Sender

// Callback when data is received
void data_receive(const uint8_t * mac, const uint8_t *data, int len) {
  memcpy(&input, data, sizeof(data));
  Serial.print("Sending Message: ");
  Serial.println(input.cmd);

  // Begin Transmission to Board
  // Mmo 1
  Wire.beginTransmission(0x30);  // transmit to device 0x30
  Wire.write(input.cmd);
  Wire.endTransmission();  // stop transmitting

  // Mmo 2
  Wire.beginTransmission(0x34); // 
  Wire.write(input.cmd);
  Wire.endTransmission();

  // Hmo 1
  Wire.beginTransmission(0x38);
  Wire.write(input.cmd);
  Wire.endTransmission();

  // Hmo 2
  Wire.beginTransmission(0x42);
  Wire.write(input.cmd);
  Wire.endTransmission();

  // Mmo 3
  Wire.beginTransmission(0x46);
  Wire.write(input.cmd);
  Wire.endTransmission();

  // Mmo 4
  Wire.beginTransmission(0x50);
  Wire.write(input.cmd);
  Wire.endTransmission();

  // Xmo # To add another i2c transmission
  // Wire.beginTransmission(HEX_ADDRESS);
  // Wire.write(input.cmd);
  // Wire.endTransmission();

  delay(100);
}
 
void setup() {
  Serial.begin(115200);
  // Wire.setSDA(22);
  // Wire.setSCL(20);
  Wire.begin();
  Wire.setPins(22, 23);
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // esp_now_register_send_cb(data_sent);
  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;       
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(data_receive);
}
 
void loop() {
}