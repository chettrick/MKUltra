#pragma once
#include "oscillator.h"
#include "envelope.h"

class instrument
{
public:
	//Timing
	double sysTime;

	//Oscillators
	oscillator OSC1;
	oscillator OSC2;
	bool OSC1_on = true;
	bool OSC2_on = true;

	//Envelope
	envelope ENV;
	//Frequency Modulation and LFO
	oscillator LFO;
	//Notes
	char MIDInoteNum;
	double frequency;

	//Make sound

//methods
	//Default constructor
	instrument();

	//Constructors with arguments

	//Setters
	void setNote(char MIDInoteNum);
	void setOSC1_on(bool on_or_off);
	void setOSC2_on(bool on_or_off);

	//Getters


	//Other
	double noteNumberToFrequency(int noteNumber);
	double outputSound(double dTime);

};

