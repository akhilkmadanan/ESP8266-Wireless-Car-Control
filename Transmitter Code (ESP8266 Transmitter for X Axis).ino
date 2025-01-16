#include <ESP8266WiFi.h>
#include <espnow.h>

// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x30, 0x83, 0x98, 0x80, 0x05, 0xBD};  // Broadcast address

// Structure to send joystick data
typedef struct struct_message {
  int joyX;  // X-axis value
  int joyY;  // Y-axis value (dummy value for this transmitter)
  int senderID;  // ID to identify the transmitter (1 for this transmitter)
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
  // Read joystick X value
  int xValue = analogRead(A0);

  // Map the analog value to 1 or 0 based on thresholds
  if (xValue > 600) {
    myData.joyX = 1;
  } else if (xValue < 400) {
    myData.joyX = 0;
  } else {
    myData.joyX = -1;  // No movement in the middle range
  }

  // Set joyY to a dummy value for this transmitter (since only X is used here)
  myData.joyY = 0;

  // Set sender ID to 1 for this transmitter
  myData.senderID = 1;

  // Send joystick data via ESP-NOW
  esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

  Serial.print("Sending Joy X: ");
  Serial.println(myData.joyX);

  delay(10);  // Just a small delay to allow the receiver to process, can be removed entirely if not needed
}
