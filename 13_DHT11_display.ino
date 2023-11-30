#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define DHTPIN 13  // Digital pin connected to the DHT sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11  // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address and change
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float h, t;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  dht.begin();

  display.setTextColor(SSD1306_WHITE);
  display.cp437(true);  // Use full 256 char 'Code Page 437' font
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    display.clearDisplay();
    display.println("Error reading sensor");
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  updateDisplay();
}

void updateDisplay() {
  display.clearDisplay();

  display.setCursor(0, 0);  // Start at top-left corner
  display.setTextSize(1);  // Normal 1:1 pixel scale
  display.println("Weather Station v1.0");
  display.println("");

  display.setTextSize(2);
  display.print(" Hum: ");
  display.print((int)h);
  display.println("%");
  display.println("");
  display.print("Temp: ");
  display.print((int)t);
  display.print("'C");

  display.display();
  delay(2000);
}
