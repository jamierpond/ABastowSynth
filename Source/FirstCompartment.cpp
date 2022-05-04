/*
  ==============================================================================

    FirstCompartment.cpp
    Created: 6 Mar 2022 6:05:35pm
    Author:  Bastow_boii 1
 ==============================================================================
                                Description

 Using Juce functions this makes the components visible, sets settings for indivisual sliders,
 connects audio to the sliders and sets position within the components boundaries.
 
 FirstCompartment has to initialise the plugin processor,
 in order to connect the sliders with the set settings in the parameter layout (Plugin Processor CPP line 49).
  ==============================================================================
*/
//                              References
//                           (DrBrusin, 2022)
//                            (Kengo, S., 2021)
///                            (JUCE, Unknown)

#include <JuceHeader.h>
#include "FirstCompartment.h"

FirstCompartment::FirstCompartment(BastowSynthAudioProcessor& p) :
audioProcessor(p)
{
    setAlwaysOnTop(true);
  
    //==============================================================================
                                //Making Visible
    //==============================================================================
    
    addAndMakeVisible (&FrequencySlider);
    addAndMakeVisible (&FrequencySlider2);
    addAndMakeVisible (&FrequencySlider3);
    addAndMakeVisible (&FrequencySlider4);
    addAndMakeVisible (&FrequencySlider5);
    addAndMakeVisible (&FrequencySlider6);
    addAndMakeVisible (&FrequencySlider7);
    addAndMakeVisible (&FrequencySlider8);
    addAndMakeVisible (&originalFreq);
    
    //==============================================================================
                                //Frequency Sliders
    //==============================================================================
    
    originalFreq.setLookAndFeel (&originalFreqLAF);
    originalFreq.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    originalFreq.setPopupDisplayEnabled(true, false, this);
    originalFreq.setTextValueSuffix("dB");
    
    FrequencySlider.setLookAndFeel (&freq1LAF);
    FrequencySlider.addListener(this);
    FrequencySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    FrequencySlider.setPopupDisplayEnabled(true, false, this);
    FrequencySlider.setTextValueSuffix(" St");
    FrequencySlider.setVelocityBasedMode (true);

    FrequencySlider2.setLookAndFeel (&freq2LAF);
    FrequencySlider2.addListener(this);
    FrequencySlider2.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    FrequencySlider2.setPopupDisplayEnabled(true, false, this);
    FrequencySlider2.setTextValueSuffix(" St");
    FrequencySlider2.setVelocityBasedMode (true);
    FrequencySlider2.setVelocityModeParameters (0.15, 1, 0.5, false);
    
    FrequencySlider3.setLookAndFeel (&freq3LAF);
    FrequencySlider3.addListener(this);
    FrequencySlider3.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    FrequencySlider3.setPopupDisplayEnabled(true, false, this);
    FrequencySlider3.setTextValueSuffix(" St");
    FrequencySlider3.setVelocityBasedMode (true);
    FrequencySlider3.setVelocityModeParameters (0.15, 1, 0.5, false);
    
    FrequencySlider4.setLookAndFeel (&freq4LAF);
    FrequencySlider4.addListener(this);
    FrequencySlider4.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    FrequencySlider4.setPopupDisplayEnabled(true, false, this);
    FrequencySlider4.setTextValueSuffix(" St");
    FrequencySlider4.setVelocityBasedMode (true);
    FrequencySlider4.setVelocityModeParameters (0.15, 1, 0.5, false);
   
    FrequencySlider5.setLookAndFeel (&freq5LAF);
    FrequencySlider5.addListener(this);
    FrequencySlider5.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    FrequencySlider5.setPopupDisplayEnabled(true, false, this);
    FrequencySlider5.setTextValueSuffix(" St");
    FrequencySlider5.setVelocityBasedMode (true);
    FrequencySlider5.setVelocityModeParameters (0.15, 1, 0.5, false);

    FrequencySlider6.setLookAndFeel (&freq6LAF);
    FrequencySlider6.addListener(this);
    FrequencySlider6.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    FrequencySlider6.setPopupDisplayEnabled(true, false, this);
    FrequencySlider6.setTextValueSuffix(" St");
    FrequencySlider6.setVelocityBasedMode (true);
    FrequencySlider6.setVelocityModeParameters (0.15, 1, 0.5, false);
    
    FrequencySlider7.setLookAndFeel (&freq7LAF);
    FrequencySlider7.addListener(this);
    FrequencySlider7.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    FrequencySlider7.setPopupDisplayEnabled(true, false, this);
    FrequencySlider7.setTextValueSuffix(" St");
    FrequencySlider7.setVelocityBasedMode (true);
    FrequencySlider7.setVelocityModeParameters (0.15, 1, 0.5, false);
    
    FrequencySlider8.setLookAndFeel (&freq8LAF);
    FrequencySlider8.addListener(this);
    FrequencySlider8.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    FrequencySlider8.setPopupDisplayEnabled(true, false, this);
    FrequencySlider8.setTextValueSuffix(" St");
    FrequencySlider8.setVelocityBasedMode (true);
    FrequencySlider8.setVelocityModeParameters (0.15, 1, 0.5, false);
    
    //==============================================================================
                                //APVTS Slider Connection
    //==============================================================================
    
    frequency1Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency1Id, FrequencySlider);
    
    frequency2Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency2Id, FrequencySlider2);
    
    frequency3Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency3Id, FrequencySlider3);
    
    frequency4Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency4Id, FrequencySlider4);
    
    frequency5Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency5Id, FrequencySlider5);
    
    frequency6Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency6Id, FrequencySlider6);
    
    frequency7Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency7Id, FrequencySlider7);
    
    frequency8Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency8Id, FrequencySlider8);
    
    gainOriginalVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, gainOriginalId, originalFreq);
}

FirstCompartment::~FirstCompartment()
{
}

void FirstCompartment::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::transparentWhite);
   // g.fillAll (juce::Colours::white);
}
void FirstCompartment::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds();
    
    juce::FlexBox flexbox;
    
    flexbox.flexDirection = juce::FlexBox::Direction::row;
    flexbox.flexWrap = juce::FlexBox::Wrap::wrap;
    flexbox.alignContent = juce::FlexBox::AlignContent::center;
   
    
    juce::Array<juce::FlexItem> itemArray;

    itemArray.add(juce::FlexItem(30, 125.5, FrequencySlider));
    itemArray.add(juce::FlexItem(107.5, 125.5, FrequencySlider2));
    itemArray.add(juce::FlexItem(25, 125.5, FrequencySlider3));
    itemArray.add(juce::FlexItem(107, 125.5, FrequencySlider4));
    itemArray.add(juce::FlexItem(27.5, 125.5, FrequencySlider5));
    itemArray.add(juce::FlexItem(107, 125.5, FrequencySlider6));
    itemArray.add(juce::FlexItem(27, 125.5, FrequencySlider7));
    itemArray.add(juce::FlexItem(107, 125.5, FrequencySlider8));
    itemArray.add(juce::FlexItem(185.25, 125.5, originalFreq));
    
    
    flexbox.items = itemArray;
    flexbox.performLayout(bounds);
    
}
   

void FirstCompartment::sliderValueChanged(juce::Slider* slider)
{
    
}
