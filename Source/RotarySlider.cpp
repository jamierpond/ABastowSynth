/*
  ==============================================================================

    RotarySlider.cpp
    Created: 6 Mar 2022 6:02:48pm
    Author:  Bastow_boii 1
 ==============================================================================
                                Description
 
 Using Juce functions sets the default settings for any component
 calling the class Rotary Slider.
  =============================================================================
*/
//                              References
///                            (Kengo, S., 2021)
///                            (JUCE, Unknown)

#include <JuceHeader.h>
#include "RotarySlider.h"


RotarySlider::RotarySlider()
{
    setAlwaysOnTop(true);
    setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
    setRotaryParameters (juce::MathConstants<float>::pi * 1.25f,
                         juce::MathConstants<float>::pi * 2.75f,
                         true);
    setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    setLookAndFeel (&customLookAndFeel);
    setVelocityBasedMode (true);
    setVelocityModeParameters (1.0, 1, 0.09, false);
    onValueChange = [this] { level = juce::Decibels::decibelsToGain ((float) getValue()); };
    setValue (juce::Decibels::gainToDecibels (level));
}

RotarySlider::~RotarySlider()
{
}


void RotarySlider::mouseDown (const juce::MouseEvent& event)
{
    juce::Slider::mouseDown (event);

    setMouseCursor (juce::MouseCursor::NoCursor);
}

void RotarySlider::mouseUp (const juce::MouseEvent& event)
{
    juce::Slider::mouseUp (event);

    juce::Desktop::getInstance().getMainMouseSource().setScreenPosition (event.source.getLastMouseDownPosition());

    setMouseCursor (juce::MouseCursor::NormalCursor);
}
