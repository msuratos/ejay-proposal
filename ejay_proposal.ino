/*
 * ejay_proposal.ino
 * ///////////////////////////////////////////
 * using CheapStepper Arduino library v.0.2.0
 * created by Tyler Henry, 7/2016
 * ///////////////////////////////////////////
 * 
 * the purpose of this sketch is to fulfill the
 * requirements for Ejay's proposal project.
 * 
 * //////////////////////////////////////////////////////
 */

#include <CheapStepper.h>

const int ROTATIONS_FOR_POLE = 2;
const int ROTATIONS_FOR_BOX = 1;

// arduino pin <--> pins on ULN2003 board: (IN1, IN2, IN3, IN4)
CheapStepper stepperPole (4, 5, 6, 7);
CheapStepper stepperBox (8, 9, 10, 11);
int btnA = 2;
int btnB = 3;

int stepCounterUpPole = 0;
int stepCounterDownPole = 0;
bool isFullyUp = false;
bool isFullyDown = true;

void setup() {  
//  // let's just set up a serial connection and test print to the console  
  Serial.begin(9600);
  Serial.println("Waiting for input....");
  pinMode(btnA, INPUT);
  pinMode(btnB, INPUT);
  stepperPole.setRpm(20);
  stepperBox.setRpm(10);
}

void loop() {
  /*
   * Detect if button A has been pressed.
   * This means the contraption is going up.
   */
  if (digitalRead(btnA) == HIGH){
    Serial.println("Button A Pressed!");
    
    if (!isFullyUp && isFullyDown){
      for (int i = 0; i < ROTATIONS_FOR_POLE; i++) {
        stepperPole.moveDegrees(true, 360);
      }

      Serial.println("Finished Extending Pole Stepper");
      delay(1000);

      for (int i = 0; i < ROTATIONS_FOR_BOX; i++) {
        stepperBox.moveDegrees(false, 360);
      }

      Serial.println("Finished Extending Box Stepper");
      isFullyUp = true;
      isFullyDown = false;
    }
  }

  /*
   * Detect if button B has been pressed.
   * This means the contraption is going down.
   */
  if (digitalRead(btnB) == HIGH){   
    Serial.println("Button B Pressed!");     
    
    if (isFullyUp && !isFullyDown){
      for (int i = 0; i < ROTATIONS_FOR_BOX; i++) {
        stepperBox.moveDegrees(true, 360);
      }

      Serial.println("Finished Extending Box Stepper");
      delay(1000);

      for (int i = 0; i < ROTATIONS_FOR_POLE; i++) {
        stepperPole.moveDegrees(false, 360);
      }

      Serial.println("Finished Extending Pole Stepper");
      isFullyUp = false;
      isFullyDown = true;
    }
  }
}
