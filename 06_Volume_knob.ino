#include <HID-Project.h>

// Rotary Encoder Inputs
#define inputCLK 5
#define inputDT 4
#define inputSW 3

int currentStateCLK;
int previousStateCLK;
bool halfStep;

void setup() {
  // Set encoder pins as inputs
  pinMode(inputCLK, INPUT);
  pinMode(inputDT, INPUT);
  pinMode(inputSW, INPUT_PULLUP);

  // Setup Serial Monitor
  Serial.begin(9600);
  Consumer.begin();
  Keyboard.begin();
  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);
  halfStep = false;
}

void loop() {
  // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);

  // If the previous and the current state of the inputCLK are different then a pulse has occured
  if (currentStateCLK != previousStateCLK) {
    // If the inputDT state is different than the inputCLK state then
    // the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK) {
      if (halfStep)
        halfStep = false;
      else {
        halfStep = true;
        Consumer.write(MEDIA_VOLUME_DOWN);
      }
    } else {
      if (halfStep)
        halfStep = false;
      else {
        halfStep = true;
        Consumer.write(MEDIA_VOLUME_UP);
      }
    }
  }
  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;

  if (!digitalRead(inputSW)) {
    Consumer.write(MEDIA_VOLUME_MUTE);
    delay(500);
  }
}