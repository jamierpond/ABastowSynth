/*
  ==============================================================================

    FourthCompartment.h
    Created: 6 Mar 2022 6:07:36pm
    Author:  Bastow_boii 1
 ==============================================================================
                                Description
 
 Initialises the default functions and variables in the class.
  Overrides any Pure Virtual Functions.
  ==============================================================================
*/
//                              References
//                           (DrBrusin, 2022)
//                            (Kengo, S., 2021)
///                            (JUCE, Unknown)

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "HorizontalSlider.h"
#include "VerticalSlider.h"
#include "RotarySlider.h"
#include "ResonanceSlider.h"
#include "CutoffSlider.h"
#include "MasterLAF.h"

class FourthCompartment : public juce::Component,  public juce::Slider::Listener
{
public:
    FourthCompartment(BastowSynthAudioProcessor& p);
    ~FourthCompartment() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::LinearSmoothedValue<float> smooth { 0.0f};
private:
    //==============================================================================
                                //Private Functions & variables
    //==============================================================================
    
    void sliderValueChanged(juce::Slider* slider) override;
    
    BastowSynthAudioProcessor& audioProcessor;
    
    RotarySlider filterRes;
    RotarySlider filterCutoff;
    VerticalSlider masterVol;

 

    ResonanceSliderLAF resonanceSlider;
    MasterLAF masterLAF;
    CutoffSliderLAF cutoffSlider;

    float level = 0.0f;

    //==============================================================================
                                //APVTS Slider Connection .h
    //=============================================================================
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> resVal;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment>  cutoffVal;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment>  masterVal;
    
    //==============================================================================
                                //RGBA Colours
    //==============================================================================
    
    juce::Colour red = juce::Colour::fromFloatRGBA (0.91f, 0.25f, 0.25f, 1.0f);
    juce::Colour orange = juce::Colour::fromFloatRGBA (0.91f, 0.62f, 0.25f, 1.0f);
    juce::Colour yellow = juce::Colour::fromFloatRGBA (0.91f, 0.84f, 0.25f, 1.0f);
    juce::Colour brightGreen = juce::Colour::fromFloatRGBA (0.74f, 0.91f, 0.25f, 1.0f);
    juce::Colour limeGreen = juce::Colour::fromFloatRGBA (0.31f, 0.91f, 0.25f, 1.0f);
    juce::Colour brightBlue = juce::Colour::fromFloatRGBA (0.25f, 0.66f, 0.91f, 1.0f);
    juce::Colour blue = juce::Colour::fromFloatRGBA (0.25f, 0.42f, 0.91f, 1.0f);
    juce::Colour violet = juce::Colour::fromFloatRGBA (0.62f, 0.25f, 0.91f, 1.0f);
    juce::Colour magenta = juce::Colour::fromFloatRGBA (0.91f, 0.25f, 0.80f, 1.0f);
    juce::Colour offWhite = juce::Colour::fromFloatRGBA (0.83f, 0.83f, 0.89f, 1.0f);
    juce::Colour grey = juce::Colour::fromFloatRGBA (0.42f, 0.42f, 0.42f, 1.0f);
    juce::Colour blackGrey = juce::Colour::fromFloatRGBA (0.2f, 0.2f, 0.2f, 1.0f);
    juce::Colour black = juce::Colour::fromFloatRGBA (0.01f, 0.01f, 0.01f, 1.0f);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FourthCompartment)
};
