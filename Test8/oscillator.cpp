#include "oscillator.h"

oscillator::oscillator()
{
	this->type = 0;
	this->amplitude = 1.0;
	this->phaseShift = 0.0;
	this->period = 2 * PI;
	this->frequency = 0.0;
}

void oscillator::setType(char type)
{
	this->type = type;
}

void oscillator::setAmplitude(double amplitude)
{
	this->amplitude = amplitude;
}

void oscillator::setPhaseShift(double phaseShift)
{
	this->phaseShift = phaseShift;
}

void oscillator::setPeriod(double period)
{
	this->period = period;
}

void oscillator::setFrequency(double frequency)
{
	this->frequency = frequency;
}

char oscillator::getType()
{
	return type;
}

double oscillator::getAmplitude()
{
	return amplitude;
}

double oscillator::getPhaseShift()
{
	return phaseShift;
}

double oscillator::getPeriod()
{
	return period;
}

double oscillator::getFrequency()
{
	return frequency;
}

double oscillator::evaluateFunction(double dTime)
{
	double dFreq = frequency * 2 * PI;

	switch (type)
	{

	case OSC_SINE: //Sine Wave
		return amplitude*sin(dFreq*dTime);
	case OSC_SQUARE: //Square Wave
		return amplitude*sin(dFreq * dTime) > 0.0 ? 1.0 : -1.0;
	case OSC_TRIANGLE: //Triangle Wave
		return amplitude*asin(sin(dFreq * dTime) * (2.0 / PI));
	case OSC_SAW_ANA: // Saw Wave (analogue / warm / slow)
	{
		double dOutput = 0.0;

		for (double n = 1.0; n < 100.0; n++)
			dOutput += (sin(n * dFreq)) / n;

		return amplitude*dOutput * (2.0 / PI);
	}
	case OSC_SAW_DIG: // Saw Wave (optimized / harsh / fast)
		return amplitude*((2.0 / PI) * (dFreq * PI * fmod(dTime, 1.0 / frequency) - (PI / 2.0)));
	case OSC_NOISE: // Pseudo Random Noise
		return amplitude*(2.0 * ((double)rand() / (double)RAND_MAX) - 1.0);

	default:
		return 0.0;
	}
}
