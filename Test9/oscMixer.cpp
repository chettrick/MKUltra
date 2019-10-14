#include "oscMixer.h"

oscMixer::oscMixer()
{
	OSC1Volume = 0.8;
	OSC1Volume = 0.8;
	OSC1inputSignal = 0.0;
	OSC2inputSignal = 0.0;
	mixerResult = returnMixerResult();
}

void oscMixer::setOSC1Volume(double volume)
{
	OSC1Volume = volume;
}

void oscMixer::setOSC2Volume(double volume)
{
	OSC2Volume = volume;
}

void oscMixer::setOSC1inputSignal(double OSC1inputSignal)
{
	this->OSC1inputSignal = OSC1inputSignal;
}

void oscMixer::setOSC2inputSignal(double OSC2inputSignal)
{
	this->OSC2inputSignal = OSC2inputSignal;
}

double oscMixer::returnMixerResult()
{
	//This is not exactly what I want..I dont think...
	return 0.5 * OSC1Volume * OSC1inputSignal + 0.5 * OSC2Volume * OSC2inputSignal;;
}
