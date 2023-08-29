#include <NewPing.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "Enter Your firebase host link" // Firebase host
#define FIREBASE_AUTH "Enter your firebase authentication code" // Firebase Auth code
#define WIFI_SSID "enter your ssid" // Enter your WiFi Name
#define WIFI_PASSWORD "enter your password" // Enter your WiFi password

#define TRIGGER_PIN_1 D1 // Trigger pin for the first sensor
#define ECHO_PIN_1 D2    // Echo pin for the first sensor
#define TRIGGER_PIN_2 D3 // Trigger pin for the second sensor
#define ECHO_PIN_2 D4    // Echo pin for the second sensor
#define TRIGGER_PIN_3 D5 // Trigger pin for the third sensor
#define ECHO_PIN_3 D6    // Echo pin for the third sensor
#define TRIGGER_PIN_4 D7 // Trigger pin for the fourth sensor
#define ECHO_PIN_4 D8    // Echo pin for the fourth sensor
#define MAX_DISTANCE 5   // Maximum distance in centimeters (adjust according to your needs)

NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE); // First sensor
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE); // Second sensor
NewPing sonar3(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE); // Third sensor
NewPing sonar4(TRIGGER_PIN_4, ECHO_PIN_4, MAX_DISTANCE); // Fourth sensor

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.println("Connected.");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  delay(3000); // Adjust the delay to change the measurement frequency

  unsigned int distance1 = sonar1.ping_cm();
  unsigned int distance2 = sonar2.ping_cm();
  unsigned int distance3 = sonar3.ping_cm();
  unsigned int distance4 = sonar4.ping_cm();

  // Update slot statuses for Parking 1
  if (distance1 == 0) {
    Serial.println("Slot 1 - Available");
    Firebase.setString("Parkings/Parking 1/Slot1", "Available");
  } else {
    Serial.println("Slot 1 - Unavailable");
    Firebase.setString("Parkings/Parking 1/Slot1", "Unavailable");
  }

  if (distance2 == 0) {
    Serial.println("Slot 2 - Available");
    Firebase.setString("Parkings/Parking 1/Slot2", "Available");
  } else {
    Serial.println("Slot 2 - Unavailable");
    Firebase.setString("Parkings/Parking 1/Slot2", "Unavailable");
  }

  // Update slot statuses for Parking 2
  if (distance3 == 0) {
    Serial.println("Slot 3 - Available");
    Firebase.setString("Parkings/Parking 2/Slot1", "Available");
  } else {
    Serial.println("Slot 3 - Unavailable");
    Firebase.setString("Parkings/Parking 2/Slot1", "Unavailable");
  }

  if (distance4 == 0) {
    Serial.println("Slot 4 - Available");
    Firebase.setString("Parkings/Parking 2/Slot2", "Available");
  } else {
    Serial.println("Slot 4 - Unavailable");
    Firebase.setString("Parkings/Parking 2/Slot2", "Unavailable");
  }
}
