#define BLYNK_TEMPLATE_ID "TMPL3bZfE45JH"
#define BLYNK_TEMPLATE_NAME "Water level"
#define BLYNK_AUTH_TOKEN "YOUR_NEW_BLYNK_AUTH_TOKEN

#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BlynkSimpleEsp32.h>

// Wi-Fi credentials
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// Ultrasonic sensor pins
#define TRIG_PIN 5
#define ECHO_PIN 18

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1
);

BlynkTimer timer;

bool oledReady = false;
bool highAlertSent = false;

float distance = 0.0;
int percentage = 0;

// Bottle calibration
// Bottle height = 14.7 cm
// Sensor must face downward from above the bottle.
const float EMPTY_DISTANCE_CM = 14.7;
const float FULL_DISTANCE_CM = 2.5;

// Connection retry timing
unsigned long lastWiFiAttempt = 0;
unsigned long lastBlynkAttempt = 0;

const unsigned long WIFI_RETRY_MS = 10000;
const unsigned long BLYNK_RETRY_MS = 5000;

// Function declarations
void measureWaterLevel();
void updateDisplay();
void maintainConnections();

void setup() {
  Serial.begin(115200);

  // Ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  // OLED
  Wire.begin(21, 22);

  oledReady = display.begin(
    SSD1306_SWITCHCAPVCC,
    OLED_ADDRESS
  );

  if (oledReady) {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Water Level Monitor");
    display.println("Starting...");
    display.display();
  } else {
    Serial.println("OLED initialization failed!");
  }

  // Start Wi-Fi without blocking sensor startup
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  lastWiFiAttempt = millis();

  // Configure Blynk
  Blynk.config(BLYNK_AUTH_TOKEN);

  // Measure every 2 seconds
  timer.setInterval(2000L, measureWaterLevel);

  Serial.println("Water monitoring started");
}

void loop() {
  maintainConnections();

  if (WiFi.status() == WL_CONNECTED) {
    Blynk.run();
  }

  timer.run();
}

void maintainConnections() {
  unsigned long now = millis();

  // Retry Wi-Fi if disconnected
  if (WiFi.status() != WL_CONNECTED &&
      now - lastWiFiAttempt >= WIFI_RETRY_MS) {

    Serial.println("Retrying Wi-Fi...");
    WiFi.disconnect();
    WiFi.begin(ssid, pass);
    lastWiFiAttempt = now;
  }

  // Retry Blynk connection if disconnected
  if (WiFi.status() == WL_CONNECTED &&
      !Blynk.connected() &&
      now - lastBlynkAttempt >= BLYNK_RETRY_MS) {

    Serial.println("Connecting to Blynk...");
    bool connected = Blynk.connect(1000);

    if (connected) {
      Serial.println("Blynk connected!");
    } else {
      Serial.println("Blynk connection failed; retrying.");
    }

    lastBlynkAttempt = millis();
  }
}

void measureWaterLevel() {
  // Send ultrasonic trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo; timeout after 30 ms
  unsigned long duration = pulseIn(
    ECHO_PIN, HIGH, 30000
  );

  if (duration == 0) {
    Serial.println("Sensor timeout - check sensor/wiring");
    return;
  }

  float measuredDistance = duration * 0.0343 / 2.0;

  // Ignore readings outside a reasonable range
  if (measuredDistance < 2.0 ||
      measuredDistance > 400.0) {
    Serial.println("Invalid distance reading");
    return;
  }

  distance = measuredDistance;

  // Convert distance to water percentage.
  // Smaller distance means more water.
  float level =
    (EMPTY_DISTANCE_CM - distance) /
    (EMPTY_DISTANCE_CM - FULL_DISTANCE_CM) * 100.0;

  percentage = constrain((int)(level + 0.5), 0, 100);

  Serial.print("Distance: ");
  Serial.print(distance, 1);
  Serial.print(" cm | Water Level: ");
  Serial.print(percentage);
  Serial.println("%");

  updateDisplay();

  // Send readings to Blynk
  if (Blynk.connected()) {
    Blynk.virtualWrite(V0, percentage);
    Blynk.virtualWrite(V1, distance);

    // Send a single alert when level reaches 80%
    if (percentage >= 80 && !highAlertSent) {
      Blynk.logEvent(
        "water_high",
        "Water level reached 80% or higher. Overflow risk!"
      );

      highAlertSent = true;
      Serial.println("High water level alert sent");
    }

    // Allow another alert after level falls below 75%
    if (percentage < 75) {
      highAlertSent = false;
    }
  }
}

void updateDisplay() {
  if (!oledReady) {
    return;
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("WATER LEVEL MONITOR");

  display.setTextSize(2);
  display.setCursor(0, 17);
  display.print(percentage);
  display.println("%");

  display.setTextSize(1);
  display.setCursor(0, 43);
  display.print("Distance: ");
  display.print(distance, 1);
  display.println(" cm");

  display.setCursor(0, 55);
  if (WiFi.status() == WL_CONNECTED &&
      Blynk.connected()) {
    display.println("Blynk: Online");
  } else {
    display.println("Blynk: Connecting...");
  }

  display.display();
}