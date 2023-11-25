#include <Adafruit_NeoPixel.h>
#include "pitches.h"

// change this to make the song slower or faster
int tempo = 200;

// change this to whichever pin you want to use
int buzzer = 14;  // ESP8266 D5

// Which pin on the Arduino is connected to the NeoPixels?
#define LED_PIN 4 //D2

Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

uint32_t rgbcolor = 0;
uint32_t hsvValue = 0;

void setup() {

  pixels.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(10);  // 1-255

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;  // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);
    if (hsvValue < 65536) {
      hsvValue = hsvValue + 8192;
    } else {
      hsvValue = 0;
    }

    rgbcolor = pixels.ColorHSV(hsvValue);
    pixels.fill(rgbcolor);
    pixels.show();

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    pixels.clear();
    pixels.fill(0);
    pixels.show();

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}

void loop() {
  // no need to repeat the melody.
}