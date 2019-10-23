#include <iostream>
#include <conio.h>
#include "olcNoiseMaker.h"
#include "oscillator.h"
// XXX #include "oscMixer.h"
#include "envelope.h"
#include "instrument.h"

instrument SYNTH1;
double sysTime;

double MakeNoise1(double dTime)
{
	sysTime = dTime;
	return SYNTH1.outputSound(dTime);
}

void printMIDIDevices()
{
	UINT numMidiInDev;
	UINT udeviceID = 0;
	MIDIINCAPS pmic;

	vector<wstring> midiDevices;
	numMidiInDev = midiInGetNumDevs();
	printf("Number of MIDI-INPUT Devices: %d\n", numMidiInDev);

	for (int i = 0; i < numMidiInDev; i++) {
		if (midiInGetDevCaps(udeviceID, &pmic, sizeof(pmic))) {
			// XXX midiDevices.push_back(pmic.szPname);
			string temp(pmic.szPname);
			wstring temp2(temp.begin(), temp.end());
			midiDevices.push_back(temp2);
		}

			wcout << "Found Midi Input: " << pmic.szPname << endl;
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
		printf("%x\n", dwParam1 << 8 * 7);
		//92 ON
		if (dwParam1 << 8 * 7 == 0x92000000) { //Only for MIDI channel 3
			char note_number = dwParam1 << 2 * 8 >> 3 * 8; // Using bit shifts to get only bytes I want 2*8 means 2 bytes
			double frequency = SYNTH1.noteNumberToFrequency(note_number);
			printf("Note on:\t %08x %d %f\n", dwParam1, note_number, frequency);
			//Call function here with note number to produce sound//
			SYNTH1.setNote(note_number);
			SYNTH1.ENV.NoteOn(sysTime);
			SYNTH1.outputSound(sysTime);
		}
		//82 OFF
		if (dwParam1 << 8 * 7 == 0x82000000) { //Only for MIDI channel 3
			char note_number = dwParam1 << 2 * 8 >> 3 * 8; // Using bit shifts to get only bytes I want 2*8 means 2 bytes
			printf("Note off:\t %08x %d %f\n", dwParam1, note_number, SYNTH1.noteNumberToFrequency(note_number));
			//Call envelope function here to release sound
			SYNTH1.ENV.NoteOff(sysTime);
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

	//Set up the oscillators
	SYNTH1.OSC1.setType(OSC_SINE);
	SYNTH1.OSC2.setType(OSC_SQUARE);
	SYNTH1.OSC2.setFrequencyMultiple(2.0);
	SYNTH1.setOSC1_on(true);
	SYNTH1.setOSC2_on(true);

	//Set up the MIDI input
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
