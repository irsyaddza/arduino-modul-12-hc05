#include <SoftwareSerial.h>

// Bluetooth module connection
SoftwareSerial bluetooth(11, 10); // RX, TX

// LED pins
const int numLeds = 8;
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
  // Set baudrate yang umum digunakan HC-05
  Serial.begin(115200);
  bluetooth.begin(115200);
  
  // Initialize LED pins
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  // Test komunikasi serial
  Serial.println("Starting communication test...");
  testCommunication();
}

void loop() {
  if (bluetooth.available() > 0) {
    // Baca satu karakter dari Bluetooth
    char command = bluetooth.read(); // Membaca data dalam bentuk karakter

    // Tampilkan data untuk debugging
    Serial.print("Command received: ");
    Serial.println(command);

    // Eksekusi berdasarkan perintah
    if (command == 'A') {           // Command A: Nyalakan dan matikan LED pertama
      toggleSingleLed();
    } else if (command == 'B') {    // Command B: Nyalakan dan matikan semua LED
      toggleAllLeds();
    } else if (command == 'C') {    // Command C: Jalankan efek running LED
      runningLeds();
    } else {
      Serial.println("Unknown command");
    }
  }
}

void testCommunication() {
  Serial.println("Testing serial communication...");
  Serial.println("If you see this in Serial Monitor, Arduino Serial is working.");
  
  // Send test message through Bluetooth
  bluetooth.println("BT TEST");
  Serial.println("Bluetooth test message sent. Check your Android device.");
  
  // Test each LED
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);
  }
}

void toggleSingleLed() {
  // Nyalakan LED pertama
  digitalWrite(ledPins[0], HIGH);
  delay(500); // Tunggu 500ms
  // Matikan LED pertama
  digitalWrite(ledPins[0], LOW);
  Serial.println("Toggled single LED.");
}

void toggleAllLeds() {
  // Nyalakan semua LED
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(500); // Tunggu 500ms
  
  // Matikan semua LED
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  Serial.println("Toggled all LEDs.");
}

void runningLeds() {
  // Menyalakan LED satu per satu
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(200); // Tunggu 200ms
    digitalWrite(ledPins[i], LOW);
  }
  Serial.println("Running LEDs sequence complete.");
}