// synth_prototype1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

#include "olcNoiseMaker.h"

// Converts frequency (Hz) to angular velocity
double w(double dHertz)
{
	return dHertz * 2.0 * PI;
}

// General purpose oscillator
#define OSC_SINE 0
#define OSC_SQUARE 1
#define OSC_TRIANGLE 2
#define OSC_SAW_ANA 3
#define OSC_SAW_DIG 4
#define OSC_NOISE 5

double osc(double dHertz, double dTime, int nType, double dLFOHertz = 0.0, double dLFOAmplitude = 0.0)
{
	double dFreq = w(dHertz) * dTime + dLFOAmplitude * dHertz * sin(w(dLFOHertz) * dTime);

	switch (nType)
	{

	case OSC_SINE: //Sine Wave
		return sin(dFreq);
	case OSC_SQUARE: //Square Wave
		return 0.3 * sin(dFreq) > 0.0 ? 1.0 : -1.0;
	case OSC_TRIANGLE: //Triangle Wave
		return asin(sin(dFreq) * (2.0 / PI));
	case OSC_SAW_ANA: // Saw Wave (analogue / warm / slow)
	{
		double dOutput = 0.0;

		for (double n = 1.0; n < 100.0; n++)
			dOutput += (sin(n * dFreq)) / n;

		return dOutput * (2.0 / PI);
	}
	case OSC_SAW_DIG: // Saw Wave (optimized / harsh / fast)
		return (2.0 / PI) * (dHertz * PI * fmod(dTime, 1.0 / dHertz) - (PI / 2.0));
	case OSC_NOISE: // Pseudo Random Noise
		return 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;

	default:
		return 0.0;
	}
}

struct sEnvelopeADSR
{
	double dAttackTime;
	double dDecayTime;
	double dReleaseTime;

	double dSustainAmplitude;
	double dStartAmplitude;

	double dTriggerOnTime;
	double dTriggerOffTime;

	bool bNoteOn;

	sEnvelopeADSR()
	{
		dAttackTime = 0.01;
		dDecayTime = 1.0;
		dStartAmplitude = 1.0;
		dSustainAmplitude = 0.0;
		dReleaseTime = 1.0;
		dTriggerOnTime = 0.0;
		dTriggerOffTime = 0.0;
		bNoteOn = false;
	}

	double GetAmplitude(double dTime)
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

	void NoteOn(double dTimeOn)
	{
		dTriggerOnTime = dTimeOn;
		bNoteOn = true;
	}

	void NoteOff(double dTimeOff)
	{
		dTriggerOffTime = dTimeOff;
		bNoteOn = false;
	}
};

// Global synthesizer variables
atomic<double> dFrequencyOutput = 0.0;
sEnvelopeADSR envelope;
double dOctaveBaseFrequency = 220.0; //A2
double d12thRootof2 = pow(2.0, 1.0 / 12.0);

struct instrument
{
	double dVolume;
	sEnvelopeADSR env;
	virtual double sound(double dTime, double dFrequency) = 0;
};

struct bell : public instrument
{
	bell()
	{
		env.dAttackTime = 0.01;
		env.dDecayTime = 1.0;
		env.dStartAmplitude = 1.0;
		env.dSustainAmplitude = 0.0;
		env.dReleaseTime = 5.0;
	}

	double sound(double dTime, double dFrequency)
	{
		double dOutput = env.GetAmplitude(dTime) *
			(
				+ 0.7 * osc(dFrequencyOutput, dTime, OSC_SINE, 5.0, 0.001)
				+ 0.5 * osc(dFrequencyOutput * 2, dTime, OSC_SINE, 5.0, 0.001)
				+ 0.3 * osc(dFrequencyOutput * 3 + 20, dTime, OSC_SINE, 5.0, 0.001)
				+ 0.2 * osc(dFrequencyOutput * 4, dTime, OSC_SINE, 5.0, 0.001)
				+ 0.1 * osc(dFrequencyOutput * 5 + 10, dTime, OSC_SINE, 5.0, 0.001)
			);

		return dOutput;
	}
};

struct lead : public instrument
{
	lead()
	{
		env.dAttackTime = 0.01;
		env.dDecayTime = 1.0;
		env.dStartAmplitude = 1.0;
		env.dSustainAmplitude = 0.0;
		env.dReleaseTime = 5.0;
	}

	double sound(double dTime, double dFrequency)
	{
		double dOutput = env.GetAmplitude(dTime) *
			(
				+ 0.5 * osc(dFrequencyOutput, dTime, OSC_SINE, 5.0, 0.001)
				+ 0.5 * osc(dFrequencyOutput / 2, dTime, OSC_SQUARE, 5.0, 0.001)
				+ 0.5 * osc(dFrequencyOutput / 2, dTime, OSC_TRIANGLE, 5.0, 0.0)
				);

		return dOutput;
	}
};

instrument *voice = nullptr;

double MakeNoise(double dTime)
{
	double dOutput = voice->sound(dTime, dFrequencyOutput);
	return dOutput * 0.4; // Master Volume
}

int main()
{
		wcout << "Synth Prototype 1" << endl;

		// Get all sound hardware
		vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

		// Display findings
		for (auto d : devices) wcout << "Found Output Device:" << d << endl;

		// Create sound machine!!
		olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);

		//
		//voice = new bell();
		voice = new lead();

		// Link noise function with sound machine
		sound.SetUserFunction(MakeNoise);

		// Sit in loop, capturing keyboard state changes and modify
		// synthesizer output accordingly
		int nCurrentKey = -1;
		bool bKeyPressed = false;
		while (1)
		{
			bKeyPressed = false;
			for (int k = 0; k < 16; k++)
			{
				if (GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe\xbf"[k])) & 0x8000)
				{
					if (nCurrentKey != k)
					{
						dFrequencyOutput = dOctaveBaseFrequency * pow(d12thRootof2, k);
						//envelope.NoteOn(sound.GetTime());
						voice->env.NoteOn(sound.GetTime());
						wcout << "\rNote On : " << sound.GetTime() << "s " << dFrequencyOutput << "Hz";
						nCurrentKey = k;
					}

					bKeyPressed = true;
				}
			}

			if (!bKeyPressed)
			{
				if (nCurrentKey != -1)
				{
					wcout << "\rNote Off: " << sound.GetTime() << "s                        ";
					//envelope.NoteOff(sound.GetTime());
					voice->env.NoteOff(sound.GetTime());
					nCurrentKey = -1;
				}
			}
		}
	return 0;
}
