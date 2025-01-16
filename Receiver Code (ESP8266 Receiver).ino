#include <ESP8266WiFi.h>
#include <espnow.h>

// Structure to receive joystick data
typedef struct struct_message {
  int joyX;  // X-axis value
  int joyY;  // Y-axis value
  int senderID;  // ID to identify the transmitter
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Motor control pins (update as per your wiring)
const int motor1Pin1 = D1;  // Motor 1 IN1
const int motor1Pin2 = D2;  // Motor 1 IN2
const int motor2Pin1 = D5;  // Motor 2 IN1
const int motor2Pin2 = D6;  // Motor 2 IN2

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));  // Copy incoming data to myData

  Serial.print("Received Sender ID: ");
  Serial.println(myData.senderID);

  // Handle X-axis data (from sender 1)
  if (myData.senderID == 1) {
    Serial.print("Joy X: ");
    Serial.println(myData.joyX);

    // If X is in range [400, 600], no movement
    if (myData.joyX == 1) {
      moveForward();
    } else if (myData.joyX == 0) {
      moveBackward();
    } else {
      stopMotors();  // No movement if X is in the middle range
    }
  }

  // Handle Y-axis data (from sender 2)
  if (myData.senderID == 2) {
    Serial.print("Joy Y: ");
    Serial.println(myData.joyY);

    // If Y is in range [400, 600], no turning
    if (myData.joyY == 1) {
      turnRight();
    } else if (myData.joyY == 0) {
      turnLeft();
    } else {
      stopMotors();  // No turning if Y is in the middle range
    }
  }
}

// Function to move the car forward
void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Function to move the car backward
void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

// Function to turn the car left
void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Function to turn the car right
void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Set device as Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Print MAC address for debugging
  Serial.print("Receiver MAC: ");
  Serial.println(WiFi.macAddress());

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Set the role as slave (receiver)
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);

  // Register callback to receive data
  esp_now_register_recv_cb(OnDataRecv);

  // Set motor control pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
}

void loop() {
  // No need to do anything in loop, as everything is handled in the callback
}
