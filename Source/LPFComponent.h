/*
  ==============================================================================

	This file handles the LPFComponent class of the audio application.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PanelComponent.h"

//==============================================================================
/*
*/
class LPFComponent : public PanelComponent
{
public:
	LPFComponent() {}

	LPFComponent(const String& name)
	{
		// In your constructor, you should add any child components, and
		// initialise any special settings that your component needs.
		header.setButtonText(name);
		addAndMakeVisible(header);

		//Cutoff Rotary Slider and Label
		cutoffSlider.setSliderStyle(Slider::SliderStyle::Rotary);
		cutoffSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

		addAndMakeVisible(cutoffLabel);
		cutoffLabel.setText("Cutoff Freq", dontSendNotification);
		cutoffLabel.attachToComponent(&cutoffSlider, false);
		cutoffLabel.setJustificationType(Justification::centred);

		//Decay Rotary Slider and Label
		peakSlider.setSliderStyle(Slider::SliderStyle::Rotary);
		peakSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

		addAndMakeVisible(peakLabel);
		peakLabel.setText("Peak", dontSendNotification);
		peakLabel.attachToComponent(&peakSlider, false);
		peakLabel.setJustificationType(Justification::centred);

		addAndMakeVisible(cutoffSlider);
		addAndMakeVisible(peakSlider);
	}

	~LPFComponent()
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
		cutoffLabel.setBounds(area.removeFromTop(50));
		cutoffSlider.setBounds(area.removeFromTop(75));
		peakLabel.setBounds(area.removeFromTop(20));
		peakSlider.setBounds(area.removeFromTop(75));
	}

private:
	int headerHeight = 30;

	TextButton header;

	Slider cutoffSlider;
	Slider peakSlider;

	Label cutoffLabel;
	Label peakLabel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LPFComponent)
};

