#include <cmath>
#include "instrument.h"

instrument::instrument()
{
	//Timing
	double sysTime = 0.0;
	char MIDInoteNum = 0;
	double frequency = 0.0;
	//Oscillators
	bool OSC1_on = true; //Multiply by this in output to turn an oscillator on or off
	bool OSC2_on = true;
}

double instrument::noteNumberToFrequency(int noteNumber) {
	double exponent = ((double)noteNumber - 69) / 12;
	double freq = pow(2, exponent) * 440.0;
	return freq;
}

void instrument::setNote(char MIDInoteNum)
{
	this->MIDInoteNum = MIDInoteNum;
	frequency = noteNumberToFrequency(MIDInoteNum);
	//For all oscillator sound sources set the frequency
	OSC1.setFrequency(frequency);
	OSC2.setFrequency(frequency);
}

void instrument::setOSC1_on(bool on_or_off)
{
	OSC1_on = on_or_off;
}

void instrument::setOSC2_on(bool on_or_off)
{
	OSC2_on = on_or_off;
}

double instrument::outputSound(double dTime)
{
	sysTime = dTime;
	return ENV.getAmplitude(dTime) * (OSC1_on*0.6*OSC1.evaluateFunction(dTime) + OSC2_on*0.4*OSC2.evaluateFunction(dTime));
}
