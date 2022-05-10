/*
  ==============================================================================

    HorizontalSlider.cpp
    Created: 6 Mar 2022 6:03:33pm
    Author:  Bastow_boii 1
 ==============================================================================
                                Description
 
 Using Juce functions sets the default settings for any component
 calling the class Horizontal Slider.
  =============================================================================
*/
//                              References
///                            (Kengo, S., 2021)
///                            (JUCE, Unknown)

#include <JuceHeader.h>
#include "HorizontalSlider.h"

HorizontalSlider::HorizontalSlider ()
{
    setAlwaysOnTop(true);
    setSliderStyle (juce::Slider::LinearHorizontal);
    setLookAndFeel (&customLookAndFeel);
    setVelocityBasedMode (true);
    setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    setVelocityModeParameters (0.75, 1, 0.09, false);
    onValueChange = [this] { level = juce::Decibels::decibelsToGain ((float) getValue()); };
    setValue (juce::Decibels::gainToDecibels (level));

    
    
}

HorizontalSlider::~HorizontalSlider()
{
}

