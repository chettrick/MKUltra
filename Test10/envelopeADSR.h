class envelopeADSR
{
public:
	double dAttackTime;
	double dDecayTime;
	double dReleaseTime;

	double dSustainAmplitude;
	double dStartAmplitude;

	double dTriggerOnTime;
	double dTriggerOffTime;

	bool bNoteOn;

	envelopeADSR() //Default constructor
	{
		dAttackTime = 0.1;
		dDecayTime = 0.05;
		dStartAmplitude = 0.3;
		dSustainAmplitude = 0.3;
		dReleaseTime = 0.25;
		dTriggerOnTime = 0.0;
		dTriggerOffTime = 0.0;
		bNoteOn = false;
	}

	double GetAmplitude(double dTime);

	void NoteOn(double dTimeOn);

	void NoteOff(double dTimeOff);
};


