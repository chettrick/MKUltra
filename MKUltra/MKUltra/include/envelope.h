#pragma once
class envelope
{
private:
	double attackTime;
	double decayTime;
	double releaseTime;

	double sustainAmplitude;
	double startAmplitude;

	double triggerOnTime;
	double triggerOffTime;

	bool noteOn;

public:
	envelope();

	//Setters
	void setAttackTime(double attackTime);
	void setDecayTime(double decayTime);
	void setReleaseTime(double releaseTime);
	void setSustainAmplitude(double sustainAmplitude);
	void setStartAmplitude(double startAmplitude);
	void setTriggerOnTime(double triggerOnTime);
	void setTriggerOffTime(double triggerOffTime);
	void setNoteOn(bool noteOn);

	//Getters
	double getAttackTime();
	double getDecayTime();
	double getReleaseTime();
	double getSustainAmplitude();
	double getStartAmplitude();
	double getTriggerOnTime();
	double getTriggerOffTime();
	bool getNoteOn();

	double getAmplitude(double time);
	void NoteOn(double timeOn);
	void NoteOff(double timeOff);
};

