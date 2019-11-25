/*
  ==============================================================================

    OscillatorComponent.h
    Created: 22 Nov 2019 3:16:51pm
    Author:  chris

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "PanelComponent.h"

//==============================================================================
/*
*/
class OscillatorComponent    : public PanelComponent
{
public:
    OscillatorComponent(const String& name)
        : PanelComponent(name)
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

        mySlider.setSliderStyle(Slider::SliderStyle::Rotary);
        mySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
        addAndMakeVisible(mySlider);

        sineButton.setButtonText("Sine");
        squareButton.setButtonText("Square");
        triangleButton.setButtonText("Triangle");
        addAndMakeVisible(sineButton);
        addAndMakeVisible(squareButton);
        addAndMakeVisible(triangleButton);
    }

    ~OscillatorComponent()
    {
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        PanelComponent::resized();

        auto area = getLocalBounds();

        mySlider.setBounds(area.removeFromTop(75));
        triangleButton.setBounds(area.removeFromBottom(50));
        squareButton.setBounds(area.removeFromBottom(50));
        sineButton.setBounds(area.removeFromBottom(50));
    }

private:
    Slider mySlider;

    TextButton sineButton;
    TextButton squareButton;
    TextButton triangleButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorComponent)
};
