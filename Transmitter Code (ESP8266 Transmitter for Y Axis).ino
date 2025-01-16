#include <ESP8266WiFi.h>
#include <espnow.h>

// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x30, 0x83, 0x98, 0x80, 0x05, 0xBD};  // Broadcast address

// Structure to send joystick data
typedef struct struct_message {
  int joyX;  // X-axis value (dummy value for this transmitter)
  int joyY;  // Y-axis value
  int senderID;  // ID to identify the transmitter (2 for this transmitter)
} struct_message;

// Create a struct_message called myData
struct_message myData;

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  // Set device as Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register for Send CB
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  
  // Register peer (Receiver)
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  // Read joystick Y value
  int yValue = analogRead(A0);

  // Map the analog value to 1 or 0 based on thresholds
  if (yValue > 600) {
    myData.joyY = 1;
  } else if (yValue < 400) {
    myData.joyY = 0;
  } else {
    myData.joyY = -1;  // No turning in the middle range
  }

  // Set joyX to a dummy value for this transmitter (since only Y is used here)
  myData.joyX = 0;

  // Set sender ID to 2 for this transmitter
  myData.senderID = 2;

  // Send joystick data via ESP-NOW
  esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

  Serial.print("Sending Joy Y: ");
  Serial.println(myData.joyY);

  delay(10);  // Just a small delay to allow the receiver to process, can be removed entirely if not needed
}
