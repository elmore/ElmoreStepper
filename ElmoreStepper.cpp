
#include "Arduino.h"
#include "ElmoreStepper.h"

Command::Command() {}

Command::Command(int pin1, int val1, int pin2, int val2, int pin3, int val3, int pin4, int val4)
{
	this->Pin1 = pin1;
	this->Pin2 = pin2;
	this->Pin3 = pin3;
	this->Pin4 = pin4;
	
	this->Val1 = val1;
	this->Val2 = val2;
	this->Val3 = val3;
	this->Val4 = val4;
}

void Command::Set()
{
	digitalWrite(this->Pin1, this->Val1);
	digitalWrite(this->Pin2, this->Val2);
	digitalWrite(this->Pin3, this->Val3);
	digitalWrite(this->Pin4, this->Val4);
}


CommandList::CommandList() {}

CommandList::CommandList(int pin1, int pin2, int pin3, int pin4)
{
	this->index = 0;

	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);
	pinMode(pin3, OUTPUT);
	pinMode(pin4, OUTPUT);
	
	commands[0] = Command(pin1, HIGH, pin2, LOW, pin3, LOW, pin4, LOW);
	commands[1] = Command(pin1, HIGH, pin2, HIGH, pin3, LOW, pin4, LOW);
	commands[2] = Command(pin1, LOW, pin2, HIGH, pin3, LOW, pin4, LOW);
	commands[3] = Command(pin1, LOW, pin2, HIGH, pin3, HIGH, pin4, LOW);
	commands[4] = Command(pin1, LOW, pin2, LOW, pin3, HIGH, pin4, LOW);
	commands[5] = Command(pin1, LOW, pin2, LOW, pin3, HIGH, pin4, HIGH);
	commands[6] = Command(pin1, LOW, pin2, LOW, pin3, LOW, pin4, HIGH);
	commands[7] = Command(pin1, HIGH, pin2, LOW, pin3, LOW, pin4, HIGH);
}

void CommandList::IncIndex()
{
	if(this->index == 7)
	{
		this->index = 0;
	}
	else 
	{
		this->index++;
	}
}
void CommandList::DecIndex()
{
	if(this->index == 0)
	{
		this->index = 7;
	}
	else 
	{
		this->index--;
	}
}
void CommandList::StepForward()
{
	IncIndex();

	this->commands[this->index].Set();
}

void CommandList::StepBack()
{
	DecIndex();

	this->commands[this->index].Set();
}






/*
 *   constructor for four-pin version
 *   Sets which wires should control the motor.
 */

ElmoreStepper::ElmoreStepper(int number_of_steps, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4)
{	
	// array of commands
	this->commander = CommandList(motor_pin_1, motor_pin_2, motor_pin_3, motor_pin_4);
	
	// time stamp in ms of the last step taken
	this->last_step_time = 0;    
	
	// total number of steps for this motor
	this->number_of_steps = number_of_steps;    
	
	// set as a default
	this->setSpeed(100);
}

/*
  Sets the speed in revs per minute
*/
void ElmoreStepper::setSpeed(long whatSpeed)
{
  this->step_delay = 60L * 1000L / this->number_of_steps / whatSpeed;
}


void ElmoreStepper::step(int steps_to_move)
{  
	if(steps_to_move == 0) { return; }

	int steps_left = abs(steps_to_move);  // how many steps to take

	// determine direction based on whether steps_to_mode is + or -:
	int direction = steps_to_move > 0 ? 1 : 0;
    
	// decrement the number of steps, moving one step each time:
	while(steps_left > 0) {
	
		// move only if the appropriate delay has passed:
		if (millis() - this->last_step_time >= this->step_delay) {
		
			// get the timeStamp of when you stepped:
			this->last_step_time = millis();
			
			// increment or decrement the step number,
			// depending on direction:
			if (direction == 1) 
			{
				this->commander.StepForward();
			} 
			else 
			{ 
				this->commander.StepBack();
			}
			
			// decrement the steps left:
			steps_left--;
		}
	}
}

/*
  version() returns the version of the library:
*/
int ElmoreStepper::version(void)
{
  return 1;
}
