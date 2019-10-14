#include "envelopeADSR.h"

double envelopeADSR::GetAmplitude(double dTime)
{
	double dAmplitude = 0.0;
	double dLifeTime = dTime - dTriggerOnTime;

	if (bNoteOn)
	{
		// ADS

		// Attack
		if (dLifeTime <= dAttackTime)
			dAmplitude = (dLifeTime / dAttackTime) * dStartAmplitude;

		// Decay
		if (dLifeTime > dAttackTime&& dLifeTime <= (dAttackTime + dDecayTime))
			dAmplitude = ((dLifeTime - dAttackTime) / dDecayTime) * (dSustainAmplitude - dStartAmplitude) + dStartAmplitude;

		// Sustain
		if (dLifeTime > dAttackTime + dDecayTime)
		{
			dAmplitude = dSustainAmplitude;
		}
	}
	else
	{
		// Release
		dAmplitude = ((dTime - dTriggerOffTime) / dReleaseTime) * (0.0 - dSustainAmplitude) + dSustainAmplitude;
	}

	if (dAmplitude <= 0.0001)
	{
		dAmplitude = 0.0;
	}

	return dAmplitude;
}

void envelopeADSR::NoteOn(double dTimeOn)
{
	dTriggerOnTime = dTimeOn;
	bNoteOn = true;
}

void envelopeADSR::NoteOff(double dTimeOff)
{
	dTriggerOffTime = dTimeOff;
	bNoteOn = false;
}
