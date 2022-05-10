/*
  ==============================================================================

    FifthCompartment.cpp
    Created: 3 Apr 2022 11:38:40pm
    Author:  Bastow_boii 1
 ==============================================================================
                                Description

 Using Juce functions this makes the components visible, sets settings for the filter menu.
 The filter menu has been put in a seperate component in order to not interfere with the focus of the sliders.
 
 FifthCompartment has to initialise the plugin processor,
 in order to connect the sliders with the set settings in the parameter layout.
  ==============================================================================
*/
//                              References
//                           (DrBrusin, 2022)
//                            (Kengo, S., 2021)
///                            (JUCE, Unknown)

#include "FifthCompartment.h"

FifthCompartment::FifthCompartment(BastowSynthAudioProcessor& p) :
audioProcessor(p)
{
    setAlwaysOnTop(true);
    addAndMakeVisible(&filterMenu);
    //==============================================================================
                                //filter Menu
    //=============================================================================
    
    filterTypeVal = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.tree, filterMenuId, filterMenu);
    
    filterMenu.setWantsKeyboardFocus (false);
    filterMenu.setSelectedItemIndex(0);
    filterMenu.addItem("Low Pass ", 1);
    filterMenu.addItem("High Pass ", 2);
    filterMenu.addItem("Band Pass ", 3);
    filterMenu.addItem("Notch Pass ",4);
    filterMenu.addItem("All Pass ", 5);
    filterMenu.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::rosybrown.darker(1.25f).withAlpha(0.5f));
    filterMenu.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::rosybrown.withAlpha(0.5f));
    filterMenu.setColour(juce::ComboBox::ColourIds::focusedOutlineColourId, juce::Colours::rosybrown.withAlpha(0.5f));
    filterMenu.setColour(juce::ComboBox::ColourIds::textColourId,juce::Colours::whitesmoke.withAlpha(0.9f));
    filterMenu.setColour(juce::ComboBox::ColourIds::arrowColourId,juce::Colours::whitesmoke.darker(0.5f));
    filterMenu.setJustificationType(juce::Justification::centred);
}

FifthCompartment::~FifthCompartment()
{
}


void FifthCompartment::paint (juce::Graphics& g)
{
   g.fillAll (juce::Colours::transparentWhite);
   
}

void FifthCompartment::resized()
{
    
    auto a = getLocalBounds().withWidth (82.2f).withHeight(22).withX(24);
    filterMenu.setBounds (a.withY (32));
  
}
void FifthCompartment::sliderValueChanged(juce::Slider* slider)
{
}
