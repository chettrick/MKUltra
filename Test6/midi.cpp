#include <SDKDDKVer.h>
#include <Windows.h>
#include <cmath>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <atomic>
#include <vector>
#include "olcNoiseMaker.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

atomic<double> dFrequencyOutput = 0.0;

using namespace std;

double MakeNoise(double dTime)
{
	double dOutput = 0.3 * sin(dFrequencyOutput * 2 * 3.14159 * dTime) + sin(dFrequencyOutput * 2 * 2 * 3.14159 * dTime);;

	if (dOutput > 0.0)
		return 0.3;
	else
		return -0.3;
}

double noteNumberToFrequency(int noteNumber) {
	double exponent = ((double)noteNumber - 69) / 12;
	double freq = pow(2, exponent) * 440.0;
	return freq;
}

void printMIDIDevices()
{
	UINT numMidiInDev;
	UINT udeviceID = 0;
	MIDIINCAPS pmic;
	UINT cbmic = 0;

	numMidiInDev = midiInGetNumDevs();

	printf("Number of MIDI-INPUT Devices: %d\n", numMidiInDev);

	for (int i = 0; i < numMidiInDev; i++) {
		midiInGetDevCaps(udeviceID, &pmic, cbmic);
		printf("Device name: %s\n", pmic.szPname);
	}
}

void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	constexpr unsigned char mask0{ 0b1111'0000 }; // represents bit 0
	switch (wMsg) {
	case MIM_OPEN:
		//printf("wMsg=MIM_OPEN\n");
		break;
	case MIM_CLOSE:
		//printf("wMsg=MIM_CLOSE\n");
		break;
	case MIM_DATA:
		//printf("wMsg=MIM_DATA, dwInstance=%08x, dwParam1=%08x, dwParam2=%08x\n", dwInstance, dwParam1, dwParam2);
		printf("%x\n", dwParam1<<8*7);
		//92 ON
		if (dwParam1 << 8 * 7 == 0x92000000) { //Only for MIDI channel 3
			char note_number = dwParam1 << 2 * 8 >> 3 * 8; // Using bit shifts to get only bytes I want 2*8 means 2 bytes
			double frequency = noteNumberToFrequency(note_number);
			printf("Note on:\t %08x %d %f\n", dwParam1, note_number, frequency);
			//Call function here with note number to produce sound//
			dFrequencyOutput = frequency;
		}
		//82 OFF
		if (dwParam1 << 8 * 7 == 0x82000000) { //Only for MIDI channel 3
			char note_number = dwParam1 << 2 * 8 >> 3 * 8; // Using bit shifts to get only bytes I want 2*8 means 2 bytes
			printf("Note off:\t %08x %d %f\n", dwParam1, note_number, noteNumberToFrequency(note_number));
			//Call function here with note number to release sound
			dFrequencyOutput = 0.0;
		}
		break;
	case MIM_LONGDATA:
		//printf("wMsg=MIM_LONGDATA\n");
		break;
	case MIM_ERROR:
		//printf("wMsg=MIM_ERROR\n");
		break;
	case MIM_LONGERROR:
		//printf("wMsg=MIM_LONGERROR\n");
		break;
	case MIM_MOREDATA:
		//printf("wMsg=MIM_MOREDATA\n");
		break;
	default:
		//printf("wMsg = unknown\n");
		break;
	}
	return;
}

int main()
{
	// Get all sound hardware
	vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

	// Display findings
	for (auto d : devices) wcout << "Found Output Device:" << d << endl;

	// Create sound machine!!
	olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);

	// Link noise function with sound machine
	sound.SetUserFunction(MakeNoise);

	HMIDIIN phmi = NULL;
	UINT uDeviceID = 0;
	DWORD_PTR dwCallback;
	MMRESULT midiIn;

	printMIDIDevices();

	midiIn = midiInOpen(&phmi, uDeviceID, (DWORD)(void*)MidiInProc, 0, CALLBACK_FUNCTION);

	midiInStart(phmi);
	
	while (true) {
		if (!_kbhit()) {
			Sleep(100);
			continue;
		}
		int c = _getch();
		if (c == VK_ESCAPE) break;
		if (c == 'q') break;
	}
	
	midiInStop(phmi);
	midiInClose(phmi);
	phmi = NULL;

	return 0;
}
