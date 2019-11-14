/*
  ==============================================================================

    This file handles the SynthAudioSource class.

  ==============================================================================
*/

#pragma once

#include "SineWave.h"

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
