#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

#define trigPin 2
#define echoPin 4
#define buzzerPin 16
#define buttonPin 17

SoftwareSerial sim800(16, 17);     // SIM800L
SoftwareSerial gpsSerial(9, 10);   // GPS
TinyGPSPlus gps;

unsigned long lastSensorCheck = 0;
unsigned long lastBeepTime = 0;
const int sensorInterval = 200;

int threshold = 50;
bool objectDetected = false;
bool smsSent = false;

bool buzzerState = LOW;
int buzzerDelay = 500;

void setup() {
  Serial.begin(115200);
  sim800.begin(9600);
  gpsSerial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(buzzerPin, LOW);
  delay(2000); // wait for modules
  Serial.println("System Initialized");
}

void loop() {
  unsigned long now = millis();

  // === Distance Measurement ===
  if (now - lastSensorCheck >= sensorInterval) {
    lastSensorCheck = now;
    long duration = getUltrasonicDuration();
    if (duration > 0) {
      float distance = duration * 0.034 / 2;
      Serial.print("Distance: ");
      Serial.println(distance);

      if (distance < threshold) {
        objectDetected = true;

        // Adjust buzzer rate based on distance
        if (distance < 10) buzzerDelay = 100;
        else if (distance < 20) buzzerDelay = 200;
        else if (distance < 35) buzzerDelay = 350;
        else buzzerDelay = 500;

      } else {
        objectDetected = false;
        digitalWrite(buzzerPin, LOW);
        buzzerState = LOW;
        smsSent = false;
      }
    }
  }

  // === Pulsed Buzzer ===
  if (objectDetected) {
    if (now - lastBeepTime >= buzzerDelay) {
      buzzerState = !buzzerState;
      digitalWrite(buzzerPin, buzzerState);
      lastBeepTime = now;
    }
  }

  // === Emergency Button Press ===
  if (digitalRead(buttonPin) == LOW && !smsSent) {
    Serial.println("Emergency Button Pressed!");
    String location = getGPSLocation();
    sendSMS("🚨 Emergency! Please help.\nLocation: " + location);
    smsSent = true;
  }

  // === GPS Feed ===
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }
}

// === Ultrasonic Distance ===
long getUltrasonicDuration() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH, 30000); // timeout 30ms
}

// === GPS Location ===
String getGPSLocation() {
  if (gps.location.isValid()) {
    String lat = String(gps.location.lat(), 6);
    String lon = String(gps.location.lng(), 6);
    return "https://maps.google.com/?q=" + lat + "," + lon;
  }
  return "No GPS Fix";
}

// === Send SMS ===
void sendSMS(String message) {
  sim800.println("AT+CMGF=1");
  delay(500);
  sim800.println("AT+CMGS=\"+917900908236\""); // ✅ Your target number
  delay(500);
  sim800.print(message);
  sim800.write(26); // CTRL+Z to send
  delay(3000);
  Serial.println("SMS Sent.");
}
