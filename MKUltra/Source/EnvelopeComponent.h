/*
  ==============================================================================

	This file handles the PanelComponent class of the audio application.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PanelComponent.h"
#include "SineWave.h"

//==============================================================================
/*
*/
class EnvelopeComponent : public PanelComponent
{
public:
	EnvelopeComponent() {}

	EnvelopeComponent(const String& name)
	{
		// In your constructor, you should add any child components, and
		// initialise any special settings that your component needs.
		header.setButtonText(name);
		addAndMakeVisible(header);

		//Attack Rotary Slider and Label
		attackSlider.setSliderStyle(Slider::SliderStyle::Rotary);
		attackSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
		attackSlider.Component::setColour(Slider::rotarySliderFillColourId, Colours::darkslategrey);
 //       attackSlider.onValueChange = [this] { synthAudioSource->setAttackParameter(attackSlider.getValue()); };


		addAndMakeVisible(attackLabel);
		attackLabel.setText("Attack Time", dontSendNotification);
		attackLabel.attachToComponent(&attackSlider, false);
		attackLabel.setJustificationType(Justification::centred);

		//Decay Rotary Slider and Label
		decaySlider.setSliderStyle(Slider::SliderStyle::Rotary);
		decaySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
		
		addAndMakeVisible(decayLabel);
		decayLabel.setText("Decay Time", dontSendNotification);
		decayLabel.attachToComponent(&decaySlider, false);
		decayLabel.setJustificationType(Justification::centred);

		//Sustain Rotary Slider and Label
		sustainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
		sustainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
		
		addAndMakeVisible(sustainLabel);
		sustainLabel.setText("Sustain Level", dontSendNotification);
		sustainLabel.attachToComponent(&sustainSlider, false);
		sustainLabel.setJustificationType(Justification::centred);

		//Release Rotary Slider and Label
		releaseSlider.setSliderStyle(Slider::SliderStyle::Rotary);
		releaseSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
		
		addAndMakeVisible(releaseLabel);
		releaseLabel.setText("Release Time", dontSendNotification);
		releaseLabel.attachToComponent(&releaseSlider, false);
		releaseLabel.setJustificationType(Justification::centred);

		addAndMakeVisible(attackSlider);
		addAndMakeVisible(decaySlider);
		addAndMakeVisible(sustainSlider);
		addAndMakeVisible(releaseSlider);
	}

	~EnvelopeComponent()
	{
	}

	void paint(Graphics& g) override
	{
		/* This demo code just fills the component's background and
		   draws some placeholder text to get you started.

		   You should replace everything in this method with your own
		   drawing code..
		*/

		g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

		g.setColour(Colours::grey);
		g.drawRect(getLocalBounds(), 2);   // draw an outline around the component
	}

	void resized() override
	{
		// This method is where you should set the bounds of any child
		// components that your component contains..
		auto area = getLocalBounds();

		header.setBounds(area.removeFromTop(headerHeight));
		attackLabel.setBounds(area.removeFromTop(50));
		attackSlider.setBounds(area.removeFromTop(75));
		decayLabel.setBounds(area.removeFromTop(20));
		decaySlider.setBounds(area.removeFromTop(75));
		sustainLabel.setBounds(area.removeFromTop(20));
		sustainSlider.setBounds(area.removeFromTop(75));
		releaseLabel.setBounds(area.removeFromTop(20));
		releaseSlider.setBounds(area.removeFromTop(75));
	}

private:
	int headerHeight = 30;

	TextButton header;

	Slider attackSlider;
	Slider decaySlider;
	Slider sustainSlider;
	Slider releaseSlider;

	Label attackLabel;
	Label decayLabel;
	Label sustainLabel;
	Label releaseLabel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeComponent)
};
