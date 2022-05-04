/*
  ==============================================================================

    ThirdCompartments.cpp
    Created: 6 Mar 2022 6:07:14pm
    Author:  Bastow_boii 1
 ==============================================================================
                                Description

 Using Juce functions this makes the components visible, sets settings for indivisual sliders,
 connects audio to the sliders and sets position within the components boundaries.
 
 ThirdCompartment has to initialise the plugin processor,
 in order to connect the sliders with the set settings in the parameter layout.
  ==============================================================================
*/
//                              References
//                           (DrBrusin, 2022)
//                            (Kengo, S., 2021)
///                            (JUCE, Unknown)


#include <JuceHeader.h>
#include "ThirdCompartment.h"

ThirdCompartment::ThirdCompartment(BastowSynthAudioProcessor& p) :
audioProcessor(p)
{
    setAlwaysOnTop(true);
    //==============================================================================
                                //Making Visible
    //==============================================================================
    
    addAndMakeVisible(&releaseSlider);
    addAndMakeVisible(&sustainSlider);
    addAndMakeVisible(&decaySlider);
    addAndMakeVisible(&attackSlider);
    
    //==============================================================================
                                //Gain Sliders
    //==============================================================================
    
      attackSlider.setLookAndFeel (&attackLAF);
     
      decaySlider.setLookAndFeel (&decayLAF);
     
    
      sustainSlider.setLookAndFeel (&sustainLAF);
     
    
      releaseSlider.setLookAndFeel (&releaseLAF);
     
    
    //==============================================================================
                                //APVTS Slider Connection
    //==============================================================================
    
    attackVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, attackId, attackSlider);
    
    decayVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, decayId, decaySlider);
   
    sustainVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, releaseId, sustainSlider);

    releaseVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, sustainId, releaseSlider);
    
}

ThirdCompartment::~ThirdCompartment()
{
}

void ThirdCompartment::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::transparentWhite);
     //g.fillAll (juce::Colours::white);
}
void ThirdCompartment::resized()
{
 
    auto a = getLocalBounds().withWidth (95.5f).withHeight(95.5f).withY(162.5f);
attackSlider.setBounds (a.withX (172.5f));
    auto b = getLocalBounds().withWidth (95.5f).withHeight(95.5f).withY(162.5f);
decaySlider.setBounds (b.withX (305));
    auto c = getLocalBounds().withWidth (95.5f).withHeight(95.5f).withY(162.5f);
sustainSlider.setBounds (c.withX (440));
    auto d = getLocalBounds().withWidth (95.5f).withHeight(95.5f).withY(162.5f);
releaseSlider.setBounds (d.withX (575));
    

  
  
}
void ThirdCompartment::sliderValueChanged(juce::Slider* slider)
{
  
}
