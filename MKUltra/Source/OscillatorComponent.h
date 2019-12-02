/*
  ==============================================================================

	This file handles the PanelComponent class of the audio application.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PanelComponent.h"
#include "MainComponent.h"
#include "Synth.h"

//==============================================================================
/*
*/
class OscillatorComponent : public PanelComponent,
							public Button::Listener
{
public:
	OscillatorComponent(const String& name, SynthAudioSource& synthAudioSource)
	{
		// In your constructor, you should add any child components, and
		// initialise any special settings that your component needs.
		this->synthAudioSource = &synthAudioSource;

		header.setButtonText(name);
		addAndMakeVisible(header);

		sineButton.setButtonText("Sine");
		squareButton.setButtonText("Square");
		triangleButton.setButtonText("Triangle");
		addAndMakeVisible(sineButton);
		addAndMakeVisible(squareButton);
		addAndMakeVisible(triangleButton);
		sineButton.addListener(this);
		squareButton.addListener(this);
		triangleButton.addListener(this);
	}

	~OscillatorComponent()
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
		mySlider.setBounds(area.removeFromTop(75));
		triangleButton.setBounds(area.removeFromBottom(50));
		squareButton.setBounds(area.removeFromBottom(50));
		sineButton.setBounds(area.removeFromBottom(50));
	}

	void buttonClicked(Button* button) override
	{
		if (button == &sineButton)
		{
			//sineButton.setButtonText("Clicked");
			synthAudioSource->setOscillatorType(OSC_SINE);
		}
		else if (button == &squareButton)
		{
			//squareButton.setButtonText("Clicked");
			synthAudioSource->setOscillatorType(OSC_SQUARE);
		}
		else if (button == &triangleButton)
		{
			//triangleButton.setButtonText("Clicked");
			synthAudioSource->setOscillatorType(OSC_TRIANGLE);
		}
	}

private:
	int headerHeight = 30;

	SynthAudioSource* synthAudioSource;

	TextButton header;
	Slider mySlider;

	TextButton sineButton;
	TextButton squareButton;
	TextButton triangleButton;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorComponent)
};

