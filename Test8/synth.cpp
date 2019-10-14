#include <iostream>
#include "olcNoiseMaker.h"
#include "oscillator.h"

oscillator OSC1;

double MakeNoise1(double dTime)
{
	return OSC1.evaluateFunction(dTime);
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

	// Link noise function with sound machine
	sound.SetUserFunction(MakeNoise1);

	double dOctaveBaseFrequency = 110.0; //A2
	double d12thRootof2 = pow(2.0, 1.0 / 12.0);

	OSC1.setType(OSC_SQUARE);

	while (1)
	{
		// Add a keyboard
		bool bKeyPressed = false;
		for (int k = 0; k < 15; k++)
		{
			if (GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe"[k])) & 0x8000)
			{
				OSC1.setFrequency(dOctaveBaseFrequency * pow(d12thRootof2, k));
				bKeyPressed = true;
			}
		}

		if (!bKeyPressed)
		{
			OSC1.setFrequency(0.0);
		}

	}
	return 0;
}