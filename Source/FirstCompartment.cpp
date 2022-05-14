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
audioProcessor(p), sliderArray{&frequencySlider,
                               &frequencySlider2,
                               &frequencySlider3,
                               &frequencySlider4,
                               &frequencySlider5,
                               &frequencySlider6,
                               &frequencySlider7,
                               &frequencySlider8,
                               &originalFreq}
{
    // Some helper functions
    static const auto getFreqSliderColour = [this](int index) {
        static const std::vector<juce::Colour> colours = {red, orange, yellow, blue, limeGreen, offWhite, blue, red};
        return colours[index];
    };
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    static const auto createSliderAttachment = [](juce::AudioProcessorValueTreeState& tree, std::unique_ptr<SliderAttachment>& attachment, juce::String paramID, juce::Slider& slider) {
        attachment = std::make_unique<SliderAttachment>(tree, paramID, slider);
    };

    setAlwaysOnTop(true);
    
    // Setup each slider with their colours etc.
    int index = 0;
    for(auto* slider : sliderArray)
    {
        addAndMakeVisible(slider);
        slider->addListener(this);
        slider->setColour(getFreqSliderColour(index++));
    }
    
    // You could also put this in the above for loop at some point, which would be tidy :) 
    auto& apvts = audioProcessor.tree;
    createSliderAttachment(apvts, frequency1Val, frequency1Id, frequencySlider);
    createSliderAttachment(apvts, frequency2Val, frequency2Id, frequencySlider2);
    createSliderAttachment(apvts, frequency3Val, frequency3Id, frequencySlider3);
    createSliderAttachment(apvts, frequency4Val, frequency4Id, frequencySlider4);
    createSliderAttachment(apvts, frequency5Val, frequency5Id, frequencySlider5);
    createSliderAttachment(apvts, frequency6Val, frequency6Id, frequencySlider6);
    createSliderAttachment(apvts, frequency7Val, frequency7Id, frequencySlider7);
    createSliderAttachment(apvts, frequency8Val, frequency8Id, frequencySlider8);
    createSliderAttachment(apvts, gainOriginalVal, gainOriginalId, originalFreq);
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
