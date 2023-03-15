#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

// MAC ADDRESSES
// Device 1: 10:97:BD:3F:E0:44
// Device 2: 24:4C:AB:DA:14:CC

// REPLACE WITH THE MAC Address of your receiver 
uint8_t broadcastAddress[] = {0x24, 0x4C, 0xAB, 0xDA, 0x14, 0xCC};

String success;

typedef struct msg {
  char cmd;
  // Add more stuff if Needed
  // int, float, bool etc.
} msg;

msg input;


// Callback when data is sent
void data_sent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == 0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}

// Callback when data is received
void data_receive(const uint8_t * mac, const uint8_t *incomingData, int len) {
  Serial.print("Bytes received from: ");
  Serial.println((char*)mac);
}
 
void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(data_sent);
  
  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;     
  // Attempt to add a peer  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(data_receive);
}

unsigned char in = ' ';
void loop() {
  // Send information through Serial to receiver ESP32 board
  if(Serial.available()) {
    in = Serial.read();
    input.cmd = in; 
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &input, sizeof(input));
    delay(100);
  }
}