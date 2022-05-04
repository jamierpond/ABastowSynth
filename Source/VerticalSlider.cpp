/*
  ==============================================================================

    VerticalSlider.cpp
    Created: 6 Mar 2022 5:57:38pm
    Author:  Bastow_boii 1
 ==============================================================================
                                Description

Using Juce functions sets the default settings for any component
 calling the class Vertical Slider.
 ==============================================================================
*/
//                              References
///                            (Kengo, S., 2021)
///                            (JUCE, Unknown)

#include <JuceHeader.h>
#include "VerticalSlider.h"

VerticalSlider::VerticalSlider()
{
    setAlwaysOnTop(true);
    setSliderStyle (juce::Slider::LinearVertical);
    setLookAndFeel (&customLookAndFeel);
    setVelocityBasedMode (true);
    setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    setVelocityModeParameters (0.75, 1, 0.09, false);
    onValueChange = [this] { level = juce::Decibels::decibelsToGain ((float) getValue()); };
    setValue (juce::Decibels::gainToDecibels (level));

    
    
}

VerticalSlider::~VerticalSlider()
{
}


