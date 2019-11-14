/*
  ==============================================================================

    This file handles the MainComponent class of the audio application.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "Synth.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent, private Timer
{
public:
    //==============================================================================
    MainComponent()
        : synthAudioSource(keyboardState),
        keyboardComponent(keyboardState, MidiKeyboardComponent::horizontalKeyboard)
    {
        addAndMakeVisible(midiInputListLabel);
        midiInputListLabel.setText("MIDI Input:", dontSendNotification);
        midiInputListLabel.attachToComponent(&midiInputList, true);

        auto midiInputs = MidiInput::getAvailableDevices();
        addAndMakeVisible(midiInputList);
        midiInputList.setTextWhenNoChoicesAvailable("No MIDI Inputs Enabled");

        StringArray midiInputNames;
        for (auto input : midiInputs) {
            midiInputNames.add(input.name);
        }

        midiInputList.addItemList(midiInputNames, 1);
        midiInputList.onChange = [this] { setMidiInput(midiInputList.getSelectedItemIndex()); };

        for (auto input : midiInputs) {
            if (deviceManager.isMidiInputDeviceEnabled(input.identifier)) {
                setMidiInput(midiInputs.indexOf(input));
                break;
            }
        }

        if (midiInputList.getSelectedId() == 0) {
            setMidiInput(0);
        }

        addAndMakeVisible(keyboardComponent);

        // Specify the number of input and output channels that we want to open
        setAudioChannels(0, 2);

        // Make sure you set the size of the component after
        // you add any child components.
        setSize(600, 190);

        // Grab the computer's keyboard focus after a short delay.
        startTimer(400);
    }

    ~MainComponent() override
    {
        // This shuts down the audio device and clears the audio source.
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {
        // This function will be called when the audio device is started, or when
        // its settings (i.e. sample rate, block size, etc) are changed.

        // You can use this function to initialise any resources you might need,
        // but be careful - it will be called on the audio thread, not the GUI thread.

        // For more details, see the help for AudioProcessor::prepareToPlay()
        synthAudioSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    }

    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override
    {
        // Your audio-processing code goes here!

        // For more details, see the help for AudioProcessor::getNextAudioBlock()
        synthAudioSource.getNextAudioBlock(bufferToFill);
    }

    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()
        synthAudioSource.releaseResources();
    }

    //==============================================================================
    void paint(Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

        // You can add your drawing code here!
    }

    void resized() override
    {
        // This is called when the MainComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        midiInputList.setBounds(200, 10, getWidth() - 210, 20);
        keyboardComponent.setBounds(10, 40, getWidth() - 20, getHeight() - 50);
    }

private:
    void timerCallback() override
    {
        keyboardComponent.grabKeyboardFocus();
        stopTimer();
    }

    void setMidiInput(int index)
    {
        auto list = MidiInput::getAvailableDevices();

        deviceManager.removeMidiInputDeviceCallback(list[lastInputIndex].identifier, synthAudioSource.getMidiCollector());

        auto newInput = list[index];

        if (!deviceManager.isMidiInputDeviceEnabled(newInput.identifier)) {
            deviceManager.setMidiInputDeviceEnabled(newInput.identifier, true);
        }

        deviceManager.addMidiInputDeviceCallback(newInput.identifier, synthAudioSource.getMidiCollector());
        midiInputList.setSelectedId(index + 1, dontSendNotification);

        lastInputIndex = index;
    }

    //==============================================================================
    // Your private member variables go here...
    SynthAudioSource synthAudioSource;
    MidiKeyboardState keyboardState;
    MidiKeyboardComponent keyboardComponent;

    ComboBox midiInputList;
    Label midiInputListLabel;
    int lastInputIndex = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
