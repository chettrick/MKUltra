#include <iostream>
#include "olcNoiseMaker.h"

using namespace std;

// General purpose oscillator
#define OSC_SINE 0
#define OSC_SQUARE 1
#define OSC_TRIANGLE 2
#define OSC_SAW_ANA 3
#define OSC_SAW_DIG 4
#define OSC_NOISE 5

class oscillator
{
private:
	char type;
	double amplitude;
	double phaseShift;
	double period;
	double frequency;

public:
	//Default Constructor
	oscillator();
	//Setters
	void setType(char type);
	void setAmplitude(double amplitude);
	void setPhaseShift(double phaseShift);
	void setPeriod(double period);
	void setFrequency(double frequency);
	//Getters
	char getType();
	double getAmplitude();
	double getPhaseShift();
	double getPeriod();
	double getFrequency();

	double evaluateFunction(double dTime);
};

