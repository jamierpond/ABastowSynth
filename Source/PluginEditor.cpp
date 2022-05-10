/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.
 ==============================================================================
                                Description
 
 Initialises components with the audio Processor, sets the colour for the waveView component, sets size of plugin, sets parameters for keyboard component, makes visible everything that needs to be displayed, grabs image from the folder (images), sets location for components to be placed and repaints the level meter. 
  =============================================================================
*/
//                              References
//                           (DrBrusin, 2022)
//                            (Kengo, S., 2021)
///                            (JUCE, Unknown)
///                           (Akash Murthy, 2021)
///                           (ColorHexa, Unknown)


#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BastowSynthAudioProcessorEditor::BastowSynthAudioProcessorEditor (BastowSynthAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p)
, component1 (audioProcessor)
, component2 (audioProcessor)
, component3 (audioProcessor)
, component4 (audioProcessor)
, component5 (audioProcessor)
,  keyboardComponent(p.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{

    audioProcessor.WaveView.setOpaque(false );
    audioProcessor.WaveView.setColours(lightBlack.withAlpha(0.0f), juce::Colours::green );
 

    //==============================================================================
                                //Size of Main Component
    //==============================================================================
    setSize (1050, 600);
    
    startTimerHz(12);
    
    
    //==============================================================================
                                //Keyboard Component
    //==============================================================================
    
    keyboardComponent.setAvailableRange(36, 120);
    keyboardComponent.setKeyWidth(13.22f);
    keyboardComponent.setBlackNoteWidthProportion(.75);
    keyboardComponent.setColour(keyboardComponent.blackNoteColourId,darkGrey.darker(5.5));
    keyboardComponent.setColour(keyboardComponent.whiteNoteColourId,lightBlack.brighter(0.5) );
    keyboardComponent.setColour(keyboardComponent.textLabelColourId ,lightGrey );
    keyboardComponent.setColour(keyboardComponent.keySeparatorLineColourId , darkGrey.darker(0.05));
    keyboardComponent.setColour(keyboardComponent.mouseOverKeyOverlayColourId , lightGrey.darker(0.5));
    keyboardComponent.setColour(keyboardComponent.keyDownOverlayColourId, lightGrey.brighter(0.2));
    
   
    //==============================================================================
                                //Making Visible
    //==============================================================================
    

    addAndMakeVisible (&keyboardComponent);
 
    addAndMakeVisible(&component1);
    addAndMakeVisible(&component2);
    addAndMakeVisible(&component3);
    addAndMakeVisible(&component4);
    addAndMakeVisible(&component5);
    addAndMakeVisible(&HLML);
    addAndMakeVisible(&HLMR);
    addAndMakeVisible(audioProcessor.WaveView);
    
    
    

  
}
BastowSynthAudioProcessorEditor::~BastowSynthAudioProcessorEditor()
    
{
    stopTimer();
    // Deconstructor, anything named BastowSynthAudioProcessorEditor will be ignored, preventing complier problems
}

void BastowSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
  
    background = juce::ImageCache::getFromMemory(BinaryData::BackgroundSynth_png, BinaryData::BackgroundSynth_pngSize);
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    
}
void BastowSynthAudioProcessorEditor::resized()
{
   
    
 
    auto a = getLocalBounds().withWidth (662.5).withHeight(50).withX(250);
keyboardComponent.setBounds (a.withY (515));
    
    auto b = getLocalBounds().withWidth(172.5).withHeight(95).withX(25);
    audioProcessor.WaveView.setBounds (b.withY (375.25));
  
    auto c = getLocalBounds().withWidth (750).withHeight(200).withX(247.5);
component1.setBounds (c.withY (275.5));

    auto d = getLocalBounds().withWidth (100).withHeight(400).withX(17.5);
component2.setBounds (d.withY (86.5));
   
    auto e = getLocalBounds().withWidth (700).withHeight(300).withX(177.5);
component3.setBounds (e.withY (0));
  
    auto f = getLocalBounds().withWidth (200).withHeight(800).withX(930);
component4.setBounds (f.withY (0));
    
      auto g = getLocalBounds().withWidth (200).withHeight(350).withX(930);
  component5.setBounds (g.withY (500));
    
    auto h = getLocalBounds().withWidth(175).withHeight(20).withX(20);
   HLML.setBounds (h.withY (515.5));
    
    auto i = getLocalBounds().withWidth(175).withHeight(20).withX(20);
   HLMR.setBounds (i.withY (545.5));
    
  
  
};

void BastowSynthAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{


 
}

void BastowSynthAudioProcessorEditor::timerCallback()
{
    HLML.setLevel(audioProcessor.getRMSValue(0));
    HLMR.setLevel(audioProcessor.getRMSValue(1));
                  
    HLML.repaint();
    HLMR.repaint();
}
