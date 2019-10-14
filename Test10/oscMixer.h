#pragma once
class oscMixer
{
private:
	double OSC1Volume;
	double OSC2Volume;

	double OSC1inputSignal;
	double OSC2inputSignal;

	double mixerResult;
public:
	oscMixer();

	void setOSC1Volume(double volume);
	void setOSC2Volume(double volume);
	void setOSC1inputSignal(double OSC1inputSignal);
	void setOSC2inputSignal(double OSC2inputSignal);

	double returnMixerResult();
};

