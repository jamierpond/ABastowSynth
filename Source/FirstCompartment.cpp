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
  =============================================================================
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
    
    addAndMakeVisible (&frequencySlider);
    addAndMakeVisible (&frequencySlider2);
    addAndMakeVisible (&frequencySlider3);
    addAndMakeVisible (&frequencySlider4);
    addAndMakeVisible (&frequencySlider5);
    addAndMakeVisible (&frequencySlider6);
    addAndMakeVisible (&frequencySlider7);
    addAndMakeVisible (&frequencySlider8);
    addAndMakeVisible (&originalFreq);
    
    //==============================================================================
                                //Frequency Sliders
    //==============================================================================
    
    originalFreq.addListener(this);
    originalFreq.setColour(red);

    frequencySlider.addListener(this);
    frequencySlider.setColour(red);

    frequencySlider2.addListener(this);
    frequencySlider2.setColour(orange);
    
    frequencySlider3.addListener(this);
    frequencySlider3.setColour(orange);
    
    frequencySlider4.addListener(this);
    frequencySlider4.setColour(yellow);
   
    frequencySlider5.addListener(this);
    frequencySlider5.setColour(blue);

    frequencySlider6.addListener(this);
    frequencySlider6.setColour(limeGreen);

    frequencySlider7.addListener(this);
    frequencySlider7.setColour(offWhite);
    
    frequencySlider8.addListener(this);
    frequencySlider8.setColour(blue);
    
    //==============================================================================
                                //APVTS Slider Connection
    //==============================================================================
    
    frequency1Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency1Id, frequencySlider);
    
    frequency2Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency2Id, frequencySlider2);
    
    frequency3Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency3Id, frequencySlider3);
    
    frequency4Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency4Id, frequencySlider4);
    
    frequency5Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency5Id, frequencySlider5);
    
    frequency6Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency6Id, frequencySlider6);
    
    frequency7Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency7Id, frequencySlider7);
    
    frequency8Val = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, frequency8Id, frequencySlider8);
    
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

    itemArray.add(juce::FlexItem(30, 125.5, frequencySlider));
    itemArray.add(juce::FlexItem(107.5, 125.5, frequencySlider2));
    itemArray.add(juce::FlexItem(25, 125.5, frequencySlider3));
    itemArray.add(juce::FlexItem(107, 125.5, frequencySlider4));
    itemArray.add(juce::FlexItem(27.5, 125.5, frequencySlider5));
    itemArray.add(juce::FlexItem(107, 125.5, frequencySlider6));
    itemArray.add(juce::FlexItem(27, 125.5, frequencySlider7));
    itemArray.add(juce::FlexItem(107, 125.5, frequencySlider8));
    itemArray.add(juce::FlexItem(185.25, 125.5, originalFreq));
    
    flexbox.items = itemArray;
    flexbox.performLayout(bounds);
}
   

void FirstCompartment::sliderValueChanged(juce::Slider* slider)
{
    
}
