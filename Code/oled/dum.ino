/*
  SMART INCENTIVIZED DUSTBIN - OLED VERSION (ESP32)
  Author: Viraj Patil (Team Project)
  Features:
  - RFID-based student recognition
  - OLED UI with animations
  - Ultrasonic level sensing
  - Reward system (+1 to +20 credits)
  - Eco quote display
  - Dynamic bin fill % and LED indicators
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <MFRC522.h>

// OLED CONFIG ===============================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C  // Change to 0x3D if your OLED uses that address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// RFID CONFIG ===============================
#define SS_PIN 5
#define RST_PIN 17
MFRC522 rfid(SS_PIN, RST_PIN);

// ULTRASONIC CONFIG =========================
#define TRIG_PIN 12
#define ECHO_PIN 14

// LED CONFIG ================================
#define GREEN_LED 2
#define RED_LED 4

// STUDENT DATABASE ==========================
struct Student {
  String name;
  uint32_t uidDec;
  int credits;
};

Student students[] = {
  {"Viraj", 332408889, 0},
  {"Gargi", 2744089070, 0},
  {"Tanvi", 1389083307, 0}
};

int numStudents = sizeof(students) / sizeof(students[0]);

// ECO QUOTES ================================
String quotes[] = {
  "Clean campus, cool campus!",
  "Be the change you wish to see.",
  "Every throw counts.",
  "Keep it green, keep it clean.",
  "Smart minds, smart planet."
};

// FUNCTION DECLARATIONS =====================
float getDistance();
void showText(String text, int delayMs = 1500);
void showBinStatus(float fillPercent);
void scrollText(String text, int speedDelay);
void loadingDots(String baseMsg);
void rewardAnimation(int points);
void showQuote();

// ===========================================
// SETUP
// ===========================================
void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  SPI.begin();
  rfid.PCD_Init();

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("OLED init failed!"));
    for (;;);
  }

  display.clearDisplay();
  showText("SMART DUSTBIN", 1500);
  scrollText("Initializing system...", 40);
  showText("Tap RFID card to start", 2000);
}

// ===========================================
// MAIN LOOP
// ===========================================
void loop() {
  float distance = getDistance();
  float fillPercent = constrain(map(distance, 5, 25, 100, 0), 0, 100);

  if (fillPercent > 90) {
    digitalWrite(RED_LED, HIGH);
    showText("Bin Full! Please empty.", 2000);
    return;
  } else digitalWrite(RED_LED, LOW);

  // RFID check
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    showBinStatus(fillPercent);
    delay(1000);
    return;
  }

  // Get UID
  uint32_t uidDec = 0;
  for (byte i = 0; i < rfid.uid.size; i++)
    uidDec = uidDec * 256 + rfid.uid.uidByte[i];

  Serial.print("UID detected: "); Serial.println(uidDec);

  bool found = false;
  for (int i = 0; i < numStudents; i++) {
    if (students[i].uidDec == uidDec) {
      found = true;
      digitalWrite(GREEN_LED, HIGH);
      showText("Hello, " + students[i].name + "!");
      showText("Credits: " + String(students[i].credits), 1500);
      scrollText("Please insert trash...", 30);

      float before = getDistance();
      delay(3000);
      float after = getDistance();

      if (before - after > 3) {
        int points = random(1, 21);
        students[i].credits += points;
        rewardAnimation(points);
        loadingDots("Updating leaderboard");
        showText("Points updated!", 1500);
        showQuote();
      } else {
        showText("No trash detected.", 1500);
      }

      digitalWrite(GREEN_LED, LOW);
      break;
    }
  }

  if (!found) {
    showText("Unknown card detected.", 1500);
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// ===========================================
// FUNCTION DEFINITIONS
// ===========================================

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 25000);
  float distance = (duration * 0.0343) / 2;
  return distance;
}

void showText(String text, int delayMs) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(4, 28);
  display.println(text);
  display.display();
  delay(delayMs);
}

void scrollText(String text, int speedDelay) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  for (int x = 128; x > -text.length() * 6; x--) {
    display.clearDisplay();
    display.setCursor(x, 28);
    display.println(text);
    display.display();
    delay(speedDelay);
  }
}

void loadingDots(String baseMsg) {
  for (int cycle = 0; cycle < 2; cycle++) {
    for (int i = 0; i < 4; i++) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(10, 30);
      String dots = "";
      for (int j = 0; j < i; j++) dots += ".";
      display.println(baseMsg + dots);
      display.display();
      delay(300);
    }
  }
}

void rewardAnimation(int points) {
  for (int i = 0; i < 2; i++) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(25, 20);
    display.print("+");
    display.println(points);
    display.display();
    delay(500);
  }
}

void showBinStatus(float fillPercent) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.print("Bin Fill: ");
  display.print((int)fillPercent);
  display.println("%");
  int bars = fillPercent / 10;
  display.setCursor(0, 35);
  for (int i = 0; i < bars; i++) display.print("|");
  display.display();
}

void showQuote() {
  int q = random(0, 5);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(4, 28);
  display.println(quotes[q]);
  display.display();
  delay(2000);
}
