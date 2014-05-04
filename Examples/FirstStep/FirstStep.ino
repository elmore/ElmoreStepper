
#include <ElmoreStepper.h>

//declare variables for the motor pins
const int motorPin1 = 53;	// Blue   - 28BYJ48 pin 1
const int motorPin2 = 51;	// Pink   - 28BYJ48 pin 2
const int motorPin3 = 49;	// Yellow - 28BYJ48 pin 3
const int motorPin4 = 47;	// Orange - 28BYJ48 pin 4
const int stepsPerRev = 64;


void setup() {

  ElmoreStepper myStepper(stepsPerRev, motorPin1, motorPin2, motorPin3, motorPin4);
  
  Serial.begin(9600);
}

void loop(){

	myStepper.step(1);
	
	delay(5);

}

