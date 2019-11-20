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

        // Specify the number of input and output channels that we want to open
        setAudioChannels(0, 2);

        // Set up all graphical components.
        addAndMakeVisible (keyboardComponent);

        oscillator1Button.setButtonText ("Oscillator 1");
        addAndMakeVisible (oscillator1Button);

        oscillator2Button.setButtonText ("Oscillator 2");
        addAndMakeVisible (oscillator2Button);

        mixerButton.setButtonText ("Mixer");
        addAndMakeVisible (mixerButton);

        highPassFilterButton.setButtonText ("High Pass Filter");
        addAndMakeVisible (highPassFilterButton);

        lowPassFilterButton.setButtonText ("Low Pass Filter");
        addAndMakeVisible (lowPassFilterButton);

        envelope1Button.setButtonText ("Envelope 1");
        addAndMakeVisible (envelope1Button);

        envelope2Button.setButtonText ("Envelope 2");
        addAndMakeVisible (envelope2Button);

        masterButton.setButtonText ("Master");
        addAndMakeVisible (masterButton);

        // Make sure you set the size of the component after
        // you add any child components.
        setSize(1000, 600);

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
        auto area = getLocalBounds();

        auto midiInputListHeight = 25;
        auto keyboardComponentHeight = 100;
        midiInputList.setBounds(area.removeFromTop(midiInputListHeight));
        keyboardComponent.setBounds(area.removeFromBottom(keyboardComponentHeight));

        auto contentItemWidth = 125;
        oscillator1Button.setBounds     (area.removeFromLeft (contentItemWidth));
        oscillator2Button.setBounds     (area.removeFromLeft (contentItemWidth));
        mixerButton.setBounds           (area.removeFromLeft (contentItemWidth));
        highPassFilterButton.setBounds  (area.removeFromLeft (contentItemWidth));
        lowPassFilterButton.setBounds   (area.removeFromLeft (contentItemWidth));
        envelope1Button.setBounds       (area.removeFromLeft (contentItemWidth));
        envelope2Button.setBounds       (area.removeFromLeft (contentItemWidth));
        masterButton.setBounds          (area.removeFromLeft (contentItemWidth));
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
    int lastInputIndex = 0;

    TextButton oscillator1Button;
    TextButton oscillator2Button;
    TextButton mixerButton;
    TextButton highPassFilterButton;
    TextButton lowPassFilterButton;
    TextButton envelope1Button;
    TextButton envelope2Button;
    TextButton masterButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
