// synth_prototype1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

#include "olcNoiseMaker.h"

atomic<double> dFrequencyOutput = 0.0;

double MakeNoise(double dTime)
{
	double dOutput = 0.3 * sin(dFrequencyOutput * 2 * 3.14159 * dTime) + sin(dFrequencyOutput * 2 * 2 * 3.14159 * dTime);;
	
	if (dOutput > 0.0)
		return 0.3;
	else
		return -0.3;
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
		sound.SetUserFunction(MakeNoise);

		double dOctaveBaseFrequency = 110.0; //A2
		double d12thRootof2 = pow(2.0, 1.0 / 12.0);

		while (1)
		{
			// Add a keyboard
			bool bKeyPressed = false;
			for (int k = 0; k < 15; k++)
			{
				if (GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe"[k])) & 0x8000)
				{
					dFrequencyOutput = dOctaveBaseFrequency * pow(d12thRootof2, k);
					bKeyPressed = true;
				}
			}

			if (!bKeyPressed)
			{
				dFrequencyOutput = 0.0;
			}

		}
	return 0;
}
