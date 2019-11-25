/*
  ==============================================================================

	This file handles the PanelComponent class of the audio application.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PanelComponent.h"

//==============================================================================
/*
*/
class MixerComponent : public PanelComponent
{
public:
	MixerComponent() {}

	MixerComponent(const String& name)
	{
		// In your constructor, you should add any child components, and
		// initialise any special settings that your component needs.
		header.setButtonText(name);
		addAndMakeVisible(header);

		//Cutoff Rotary Slider and Label
		osc1Slider.setSliderStyle(Slider::SliderStyle::Rotary);
		osc1Slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

		addAndMakeVisible(osc1Label);
		osc1Label.setText("OSC1", dontSendNotification);
		osc1Label.attachToComponent(&osc1Slider, false);
		osc1Label.setJustificationType(Justification::centred);

		//Decay Rotary Slider and Label
		osc2Slider.setSliderStyle(Slider::SliderStyle::Rotary);
		osc2Slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

		addAndMakeVisible(osc2Label);
		osc2Label.setText("OSC2", dontSendNotification);
		osc2Label.attachToComponent(&osc2Slider, false);
		osc2Label.setJustificationType(Justification::centred);

		addAndMakeVisible(osc1Slider);
		addAndMakeVisible(osc2Slider);
	}

	~MixerComponent()
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
		osc1Label.setBounds(area.removeFromTop(50));
		osc1Slider.setBounds(area.removeFromTop(75));
		osc2Label.setBounds(area.removeFromTop(20));
		osc2Slider.setBounds(area.removeFromTop(75));
	}

private:
	int headerHeight = 30;

	TextButton header;

	Slider osc1Slider;
	Slider osc2Slider;

	Label osc1Label;
	Label osc2Label;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MixerComponent)
};

