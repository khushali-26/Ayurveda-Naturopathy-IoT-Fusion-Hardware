#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 4
#define DHTTYPE DHT22
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET
);

DHT dht(DHTPIN, DHTTYPE);

Adafruit_MPU6050 mpu;

#define BUTTON_PIN 15

#define GREEN_LED 18
#define RED_LED 19
#define BUZZER_PIN 5

int currentPage = 0;
bool lastButtonState = HIGH;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed!");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(8,10);
  display.println("Ayurveda");

  display.setCursor(25,35);
  display.println("IoT");

  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20,15);
  display.println("Smart Wellness");

  display.setCursor(25,32);
  display.println("Monitoring");

  display.setCursor(35,50);
  display.println("System");

  display.display();
  delay(2000);

  display.display();

  delay(2000);

  dht.begin();

  if (!mpu.begin()) {
      Serial.println("MPU6050 not found!");
      while (1) {
        delay(10);
      }
  }

  Serial.println("MPU6050 Ready");

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  
  Serial.println("DHT22 Test Started");
}

void loop() {

  // Read button
  bool buttonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && buttonState == LOW) {
    currentPage++;

    if (currentPage > 3)
      currentPage = 0;

    delay(200);   // Debounce
  }

  lastButtonState = buttonState;

  // Read DHT
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) { 
    Serial.println("Failed to read DHT22!");
    return;
  }
  sensors_event_t a, g, temp;

  mpu.getEvent(&a, &g, &temp);

  float movement =
    abs(a.acceleration.x) +
    abs(a.acceleration.y);

  String dosha = "Balanced";

  if (temperature >= 30) {
    dosha = "PITTA";
  }
  else if (temperature <= 22) {
    dosha = "VATA";
  }
  else if (humidity >= 70) {
    dosha = "KAPHA";
  }

  // Wellness Score
  int wellnessScore = 100;

  if (temperature > 30)
    wellnessScore -= 20;

  if (humidity > 70)
    wellnessScore -= 10;

  if (movement > 2.5)
    wellnessScore -= 10;

  if (wellnessScore < 0)
    wellnessScore = 0;

  display.setCursor(75,50);

  if (dosha == "Balanced") {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER_PIN, LOW);

  }
  else {

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    digitalWrite(BUZZER_PIN, HIGH);
    delay(150);
    digitalWrite(BUZZER_PIN, LOW);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  Serial.println("----------------------------");

  Serial.print("Temperature : ");
  Serial.println(temperature);

  Serial.print("Humidity    : ");
  Serial.println(humidity);

  Serial.print("Movement    : ");
  Serial.println(movement);

  Serial.print("Dosha       : ");
  Serial.println(dosha);

  Serial.print("Score       : ");
  Serial.println(wellnessScore);

  Serial.println("----------------------------");

  switch(currentPage) {

    case 0:
      display.setCursor(0,0);
      display.println("SMART HEALTH");

      display.drawLine(0,10,128,10,SSD1306_WHITE);

      display.setCursor(0,20);
      display.print("Temp : ");
      display.print(temperature,1);
      display.print(" C");

      display.setCursor(0,35);
      display.print("Hum  : ");
      display.print(humidity,1);
      display.print(" %");

      display.setCursor(0,50);
      display.print("Score: ");
      display.print(wellnessScore);
      display.print("%");

      display.setCursor(80,50);

      if(dosha=="Balanced")
        display.print("GOOD");
      else
        display.print("ALERT");

      break;

    case 1: {
      display.setCursor(0,0);
      display.println("ACTIVITY");

      display.drawLine(0,10,128,10,SSD1306_WHITE);

      display.setCursor(0,18);

      if (movement > 2.5)
        display.println("Status: Moving");
      else
        display.println("Status: Normal");

      display.setCursor(0,34);
      display.print("X:");
      display.print(a.acceleration.x,1);

      display.setCursor(64,34);
      display.print("Y:");
      display.print(a.acceleration.y,1);

      display.setCursor(0,50);
      display.print("Z:");
      display.print(a.acceleration.z,1);

      break;
    }
    
    case 2: {

    display.setCursor(0,0);
    display.println("DOSHA ANALYSIS");

    display.drawLine(0,10,128,10,SSD1306_WHITE);

    display.setCursor(0,22);
    display.print("Current Dosha:");

    display.setCursor(0,38);
    display.setTextSize(2);
    display.println(dosha);

    display.setTextSize(1);

    break;
    }   
    case 3: {

      display.setCursor(0,0);
      display.println("RECOMMENDATION");

      display.drawLine(0,10,128,10,SSD1306_WHITE);

      if (dosha == "PITTA") {

        display.setCursor(0,20);
        display.println("Cool Water");

        display.setCursor(0,35);
        display.println("Avoid Spicy Food");

      }

      else if (dosha == "VATA") {

        display.setCursor(0,20);
        display.println("Warm Meals");

        display.setCursor(0,35);
        display.println("Proper Rest");

      }

      else if (dosha == "KAPHA") {

        display.setCursor(0,20);
        display.println("Exercise");

        display.setCursor(0,35);
        display.println("Eat Light Food");

      }

      else {

        display.setCursor(0,20);
        display.println("Balanced");

        display.setCursor(0,35);
        display.println("Keep Healthy");

      }

      break;
    }

  }
  display.display();

  delay(100);
}
