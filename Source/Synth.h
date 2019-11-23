/*
  ==============================================================================

    This file handles the SynthAudioSource class.

  ==============================================================================
*/

#pragma once

#include "SineWave.h"
#include "SquareWave.h"
#include "TriangleWave.h"
#include "Noise.h"

#define OSC_SINE 0
#define OSC_SQUARE 1
#define OSC_TRIANGLE 2
#define OSC_SAW_ANA 3
#define OSC_SAW_DIG 4
#define OSC_NOISE 5 

//==============================================================================
class SynthAudioSource   : public AudioSource
{
public:
    SynthAudioSource (MidiKeyboardState& keyState)
        : keyboardState (keyState)
    {
        for (auto i = 0; i < 4; ++i) {
            synth.addVoice (new SineWaveVoice());
        }

        synth.addSound (new SineWaveSound());
    }

	void setOscillatorType(char OSCType) {
		int m = 0; //garbage placeholder
		synth.clearVoices();
		synth.clearSounds();
	
		if (OSCType == OSC_SINE)
		{
			for (auto i = 0; i < 4; ++i) {
				synth.addVoice(new SineWaveVoice());
			}
			synth.addSound(new SineWaveSound());
		}
		else if (OSCType == OSC_SQUARE)
		{
			synth.clearSounds();
			for (auto i = 0; i < 4; ++i) {
				synth.addVoice(new SquareWaveVoice());
			}
			synth.addSound(new SquareWaveSound());
		}
		else if (OSCType == OSC_TRIANGLE)
		{
			synth.clearSounds();
			for (auto i = 0; i < 4; ++i) {
				synth.addVoice(new TriangleWaveVoice());
			}
			synth.addSound(new TriangleWaveSound());
		}
		else if (OSCType == OSC_SAW_ANA)
		{
			m = 0;
			for (auto i = 0; i < 4; ++i) {
				synth.addVoice(new SineWaveVoice());
			}
		}
		else if (OSCType == OSC_SAW_DIG)
		{
			m = 0;
			for (auto i = 0; i < 4; ++i) {
				synth.addVoice(new SineWaveVoice());
			}
		}
		else if (OSCType == OSC_NOISE)
		{
			for (auto i = 0; i < 4; ++i) {
				synth.addVoice(new NoiseVoice());
			}
			synth.addSound(new NoiseSound());
		}
	}

    void setUsingSineWaveSound()
    {
        synth.clearSounds();
    }

    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        synth.setCurrentPlaybackSampleRate (sampleRate);
        midiCollector.reset (sampleRate);
    }

    void releaseResources() override {}

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        bufferToFill.clearActiveBufferRegion();

        MidiBuffer incomingMidi;
        midiCollector.removeNextBlockOfMessages (incomingMidi, bufferToFill.numSamples);

        keyboardState.processNextMidiBuffer (incomingMidi, bufferToFill.startSample,
                                             bufferToFill.numSamples, true);

        synth.renderNextBlock (*bufferToFill.buffer, incomingMidi,
                               bufferToFill.startSample, bufferToFill.numSamples);
    }

    MidiMessageCollector* getMidiCollector()
    {
        return &midiCollector;
    }

private:
    MidiKeyboardState& keyboardState;
    Synthesiser synth;
    MidiMessageCollector midiCollector;
};
