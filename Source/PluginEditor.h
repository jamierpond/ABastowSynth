/*
==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.
==============================================================================
 Description

Initialises the default functions and variables in the class.
Overrides any Pure Virtual Functions.
=============================================================================
*/
//                              References
//                           (DrBrusin, 2022)
//                            (Kengo, S., 2021)
///                            (JUCE, Unknown)
///                           (Akash Murthy, 2021)
///                           (ColorHexa, Unknown)

#pragma once

#include <JuceHeader.h>
#include "HorizontalLevelMeter.h"
#include "PluginProcessor.h"
#include "FirstCompartment.h"
#include "SecondCompartment.h"
#include "ThirdCompartment.h"
#include "FourthCompartment.h"
#include "FifthCompartment.h"
#include "VerticalSlider.h"
#include "HorizontalSlider.h"
#include "RotarySlider.h"
#include "GainSliderLookAndFeel.h"

#include "MasterLAF.h"
#include "OriginalFreqGain.h"


class BastowSynthAudioProcessorEditor  : public juce::AudioProcessorEditor,  public juce::Slider::Listener, public juce::Timer
{
public:
    BastowSynthAudioProcessorEditor (BastowSynthAudioProcessor& );
    ~BastowSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
private:
 
    //==============================================================================
                                //Private Variables + functions
    //==============================================================================
    void sliderValueChanged(juce::Slider* slider) override;
   
    BastowSynthAudioProcessor& audioProcessor;

    FirstCompartment component1;
    SecondCompartment component2;
    ThirdCompartment component3;
    FourthCompartment component4;
    FifthCompartment component5;
    HorizontalLevelMeter HLMR;
    HorizontalLevelMeter HLML;
    
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboardComponent;
    
    
    juce::Slider::Listener* slider;
    juce::Image background;
    
    double cutoff;
    double startTime;
    //==============================================================================
                                //Colour RBGA
    //==============================================================================
    
    juce::Colour darkGrey = juce::Colour::fromFloatRGBA (0.16f, 0.15f, 0.15f, 1.0f);
    juce::Colour lightGrey = juce::Colour::fromFloatRGBA (0.74f, 0.76f, 0.76f, 1.0f);
    juce::Colour lightBlack = juce::Colour::fromFloatRGBA (0.13f, 0.13f, 0.13f, 1.0f);
    juce::Colour white = juce::Colour::fromFloatRGBA (1.0f, 1.0f, 1.0f, 1.0f);
   
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BastowSynthAudioProcessorEditor)
};
