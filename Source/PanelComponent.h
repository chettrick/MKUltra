/*
  ==============================================================================

    This file handles the PanelComponent class of the audio application.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class PanelComponent    : public Component
{
public:
	PanelComponent() {}

    PanelComponent(const String& name)
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        header.setButtonText(name);
        addAndMakeVisible(header);

		//myslider.setSliderStyle(Slider::SliderStyle::Rotary);
		//myslider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true,0,0);
		//addAndMakeVisible(myslider);
    }

    ~PanelComponent()
    {
    }

    void paint (Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 2);   // draw an outline around the component
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        auto area = getLocalBounds();

        header.setBounds (area.removeFromTop (headerHeight));
		//myslider.setBounds(area.removeFromTop(50));
    }

private:
    int headerHeight = 30;

    TextButton header;
	//Slider myslider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelComponent)
};
