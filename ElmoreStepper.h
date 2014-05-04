

// ensure this library description is only included once
#ifndef ElmoreStepper_h
#define ElmoreStepper_h


class Command 
{
	public:
		Command();
		Command(int pin1, int val1, int pin2, int val2, int pin3, int val3, int pin4, int val4);
		void Set();
		
	private:
		int Pin1;
		int Pin2;
		int Pin3;
		int Pin4;
		
		int Val1;
		int Val2;
		int Val3;
		int Val4;
};

class CommandList
{
	public:
		CommandList();
		CommandList(int pin1, int pin2, int pin3, int pin4);
		void StepForward();
		void StepBack();
		
	private:
		Command commands [8];
		int index;
		void IncIndex();
		void DecIndex();
		
};

// library interface description
class ElmoreStepper {
  public:
	// constructors:
	ElmoreStepper(int number_of_steps, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4);

	// speed setter method:
	void setSpeed(long whatSpeed);

	// mover method:
	void step(int number_of_steps);

	int version(void);

  private:
	// lists the command codes for the stepper
	CommandList commander;
	
	// delay between steps, in ms, based on speed
	unsigned long step_delay;    
	
	// total number of steps this motor can take
	int number_of_steps;
	
	// time stamp in ms of when the last step was taken
	long last_step_time;      
};

#endif

