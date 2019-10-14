#include "envelope.h"

envelope::envelope()
{
	attackTime = 0.2;
	decayTime = 0.03;
	startAmplitude = 0.5;
	sustainAmplitude = 0.5;
	releaseTime = 0.20;
	triggerOnTime = 0.0;
	triggerOffTime = 0.0;
	noteOn = false;
}

void envelope::setAttackTime(double attackTime)
{
	this->attackTime = attackTime;
}

void envelope::setDecayTime(double decayTime)
{
	this->decayTime = decayTime;
}

void envelope::setReleaseTime(double releaseTime)
{
	this->releaseTime = releaseTime;
}

void envelope::setSustainAmplitude(double sustainAmplitude)
{
	this->sustainAmplitude = sustainAmplitude;
}

void envelope::setStartAmplitude(double startAmplitude)
{
	this->startAmplitude = startAmplitude;
}

void envelope::setTriggerOnTime(double triggerOnTime)
{
	this->triggerOnTime = triggerOnTime;
}

void envelope::setTriggerOffTime(double triggerOffTime)
{
	this->triggerOffTime = triggerOffTime;
}

void envelope::setNoteOn(bool noteOn)
{
	this->noteOn = noteOn;
}

double envelope::getAttackTime()
{
	return attackTime;
}

double envelope::getDecayTime()
{
	return decayTime;
}

double envelope::getReleaseTime()
{
	return releaseTime;
}

double envelope::getSustainAmplitude()
{
	return sustainAmplitude;
}

double envelope::getStartAmplitude()
{
	return startAmplitude;
}

double envelope::getTriggerOnTime()
{
	return triggerOnTime;
}

double envelope::getTriggerOffTime()
{
	return triggerOffTime;
}

bool envelope::getNoteOn()
{
	return noteOn;
}

double envelope::getAmplitude(double time)
{
	double amplitude = 0.0;
	double releaseAmplitude = 0.0;

	if (triggerOnTime > triggerOffTime)
	{
		double lifeTime = time - triggerOnTime;

		// Attack
		if (lifeTime <= attackTime)
			amplitude = (lifeTime / attackTime) * startAmplitude;

		// Decay
		if (lifeTime > attackTime&& lifeTime <= (attackTime + decayTime))
			amplitude = ((lifeTime - attackTime) / decayTime) * (sustainAmplitude - startAmplitude) + startAmplitude;

		// Sustain
		if (lifeTime > attackTime + decayTime)
		{
			amplitude = sustainAmplitude;
		}
	}
	else
	{
		double lifeTime = time - triggerOnTime;

		if (lifeTime <= attackTime)
			releaseAmplitude = (lifeTime / attackTime) * startAmplitude;
		if (lifeTime > attackTime && lifeTime <= (attackTime + decayTime));
			releaseAmplitude = ((lifeTime - attackTime) / decayTime) * (sustainAmplitude - startAmplitude) + startAmplitude;
		if (lifeTime > (attackTime + decayTime))
			releaseAmplitude = sustainAmplitude;

		// Release
		amplitude = ((time - triggerOffTime) / releaseTime) * (0.0 - releaseAmplitude) + releaseAmplitude;
	}

	if (amplitude <= 0.000)
	{
		amplitude = 0.0;
	}

	return amplitude;
}

void envelope::NoteOn(double timeOn)
{
	triggerOnTime = timeOn;
	noteOn = true;
}

void envelope::NoteOff(double timeOff)
{
	triggerOffTime = timeOff;
	noteOn = false;
}
