#include <Adafruit_NeoPixel.h>
#include <HCSR04.h>

#define PIN 6  // Which pin on the Arduino is connected to the NeoPixels?

#define NUMPIXELS 60  // How many NeoPixels are attached to the Arduino?

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

UltraSonicDistanceSensor distanceSensor(3, 4);  // Initialize sensor that uses digital pins 3 and 4.
int current_Last_LED = 0;

void setup() {
  pixels.begin();
  pixels.setBrightness(20);
}

void loop() {
  pixels.clear();  // Set all pixel colors to 'off'
  current_Last_LED = distanceSensor.measureDistanceCm() * 0.5;

  for (int i = 0; i < current_Last_LED; i++)  //For each pixel in strip...
  {
    pixels.setPixelColor(i, 150, 0, 255);  //Purple - Change color
  }

  pixels.show();  // Send the updated pixel colors to the hardware.
}