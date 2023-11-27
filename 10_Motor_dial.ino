#include <AccelStepper.h>

// ULN2003 Motor Driver Pins
#define IN1 5 //D1 
#define IN2 4 //D2
#define IN3 0 //D3
#define IN4 2 //D4

// Rotary Encoder Inputs
#define inputCLK 14  //D5
#define inputDT 12   //D6

// initialize the stepper library
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

int currentStateCLK;
int previousStateCLK;
int rotateAngle = 180;

void setup() {
  // Set encoder pins as inputs
  pinMode(inputCLK, INPUT);
  pinMode(inputDT, INPUT);
  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);

  // set the speed and acceleration
  stepper.setMaxSpeed(15000); // if motor does not move, lower the values
  stepper.setAcceleration(10000);
}

void loop() {
  // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);

  // If the previous and the current state of the inputCLK are different then a pulse has occured
  if (currentStateCLK != previousStateCLK) {
    // If the inputDT state is different than the inputCLK state then
    // the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK) {
      stepper.move(rotateAngle);
    } else {
      stepper.move(-rotateAngle);
    }
  }
  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;

  // move the stepper motor (one step at a time)
  stepper.run();
}
