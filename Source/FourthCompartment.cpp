/*
  ==============================================================================

    FourthCompartment.cpp
    Created: 6 Mar 2022 6:07:36pm
    Author:  Bastow_boii 1
 ==============================================================================
                                Description

 Using Juce functions this makes the components visible, sets settings for indivisual sliders,
 connects audio to the sliders and sets position within the components boundaries.
 
 FourthCompartment has to initialise the plugin processor,
 in order to connect the sliders with the set settings in the parameter layout.
  ==============================================================================
*/
//                              References
//                           (DrBrusin, 2022)
//                            (Kengo, S., 2021)
///                            (JUCE, Unknown)


#include <JuceHeader.h>

#include "FourthCompartment.h"


FourthCompartment::FourthCompartment(BastowSynthAudioProcessor& p) :
audioProcessor(p)
{
    setAlwaysOnTop(true);
 
    //==============================================================================
                                //Making Visible
    //==============================================================================
    
    addAndMakeVisible(&filterRes);
    addAndMakeVisible(&filterCutoff);
    addAndMakeVisible(&masterVol);
   
    
    //==============================================================================
                                //Gain Sliders
    //=============================================================================
    
  
    filterCutoff.setLookAndFeel (&cutoffSlider);
    filterCutoff.addListener(this);
    
    filterCutoff.setTextValueSuffix("cutoff");
    filterCutoff.setPopupDisplayEnabled(true, false, this);

    filterRes.setLookAndFeel (&resonanceSlider);
    filterRes.addListener(this);
    filterRes.setTextValueSuffix("res");
    filterRes.setPopupDisplayEnabled(true, false, this);
  
    
    masterVol.setLookAndFeel (&masterLAF);
    masterVol.addListener(this);
    masterVol.setTextValueSuffix(" dB");
    masterVol.setPopupDisplayEnabled(true, false, this);
    
    //==============================================================================
                                //APVTS Slider Connection
    //==============================================================================
    
    resVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, filterResId, filterRes);

    cutoffVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, filterCutoffId, filterCutoff);

    masterVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, gainMasterId, masterVol);
   
   
}

FourthCompartment::~FourthCompartment()
{
}

void FourthCompartment::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::transparentWhite);
    //g.fillAll (juce::Colours::white);
}

void FourthCompartment::resized()
{
 
    auto a = getLocalBounds().withWidth (85).withHeight(85).withX(20);
    filterRes.setBounds (a.withY (50));
    auto b = getLocalBounds().withWidth (85).withHeight(85).withX(20);
filterCutoff.setBounds (b.withY (145));
    auto d = getLocalBounds().withWidth (98.5f).withHeight(125).withX(15);
masterVol.setBounds (d.withY (312.5f));
  
}
void FourthCompartment::sliderValueChanged(juce::Slider* slider)
{
   
}
