/*
  ==============================================================================

    ReleaseSlider.cpp
    Created: 3 Apr 2022 11:34:23pm
    Author:  Bastow_boii 1
 ==============================================================================
                                Description

 Uses Juce functions to draw a slider.
  ==============================================================================
*/
//                              References
///                            (Kengo, S., 2021)
///                       (The Audio Programmer, 2017)
///                            (JUCE, Unknown)

#include <JuceHeader.h>
#include "ReleaseSlider.h"

ReleaseSliderLAF::ReleaseSliderLAF(){};
ReleaseSliderLAF::~ReleaseSliderLAF(){};


juce::Slider::SliderLayout ReleaseSliderLAF::getSliderLayout (juce::Slider& slider)
{
    auto localBounds = slider.getLocalBounds();
    
    juce::Slider::SliderLayout layout;

    layout.sliderBounds = localBounds;

    return layout;
}

void ReleaseSliderLAF::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                                          const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
    
    //==============================================================================
                                    //Rotary Variables
    //==============================================================================
    auto bounds = juce::Rectangle<float> (x, y, width, height).reduced (30.5f);
    auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto verySmallLine = radius * 0.0085f;
    auto smallLine = radius * 0.125f;
    auto mediumLine = radius * 0.325f;
    auto bigLine = radius * 0.55f; 
    auto arcRadius = radius - verySmallLine * 1.5f;
    
    //==============================================================================
                                    //Background Track
    //==============================================================================
    g.setColour (juce::Colours::ghostwhite.darker(0.075f));
    juce::Path backgroundTrack;
    backgroundTrack.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle ,
                                 true);
    
    g.strokePath (backgroundTrack, juce::PathStrokeType (bigLine, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    //==============================================================================
                                //Decoration Track
    //==============================================================================
    

    
    juce::Path decorationTrack;
    decorationTrack.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);
    
    g.setColour (magenta.darker(0.075f));
    g.strokePath (decorationTrack, juce::PathStrokeType (mediumLine, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    
    //==============================================================================
                                //SpottedTrack
    //==============================================================================
    
    juce::Path spotTrack;
    spotTrack.addCentredArc (bounds.getCentreX(),
                            bounds.getCentreY(),
                            arcRadius,
                            arcRadius,
                            0.0f,
                            rotaryStartAngle,
                            toAngle,
                            true);
    
    g.setColour (magenta.brighter(0.75f));;
           juce::PathStrokeType spotStrokeType (2.5f);
    float dashedLen[4] = {2, 4, 3, 5};
    spotStrokeType.createDashedStroke(spotTrack, spotTrack, dashedLen, 2);
           g.strokePath(spotTrack, spotStrokeType);
    
    //==============================================================================
                                //background Circle
    //==============================================================================
    
    g.setColour (juce::Colours::ghostwhite.darker(0.15f));
    //g.fillEllipse (bounds.reduced (radius * 0.1));
    
    //==============================================================================
                                //Covers
    //==============================================================================
    
    g.setColour (offWhite.brighter(5.5f));
    juce::Path Cover1;
    Cover1.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle * 0.6,
                                 true);
    
    g.setColour (offWhite.brighter(5.5f));
    g.strokePath (Cover1, juce::PathStrokeType (bigLine, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    
    g.setColour (offWhite.brighter(5.5f));
    juce::Path Cover2;
    Cover2.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle * 0.6 ,
                                 rotaryEndAngle * 0.1,
                                 true);
    
    g.strokePath (Cover2, juce::PathStrokeType (bigLine, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    
    //==============================================================================
                                //Red Covers
    //==============================================================================
    g.setColour (magenta.brighter(0.075f));
    juce::Path magentaCover1;
    magentaCover1.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle * 0.6,
                                 true);
    
    g.setColour (magenta.darker(0.075f));
    g.strokePath (magentaCover1, juce::PathStrokeType (smallLine, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    
    g.setColour (magenta.brighter(0.075f));
    juce::Path magentaCover2;
    magentaCover2.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle * 0.6,
                                 rotaryEndAngle * 0.1,
                                 true);
    
    g.setColour (magenta.darker(0.075f));
    g.strokePath (magentaCover2, juce::PathStrokeType (smallLine, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    
    //==============================================================================
                                //thumb
    //==============================================================================
    
    
    juce::Path thumb;
    auto thumbWidth = mediumLine * 2.0f;

    thumb.addRoundedRectangle (-thumbWidth / 2 , -thumbWidth /2 , thumbWidth, radius + mediumLine, 10 , 10);
    
    
    g.setColour (juce::Colours::ghostwhite.darker(0.075f));
    
    
    
    g.setColour (blackGrey);
    g.fillPath (thumb, juce::AffineTransform::rotation (toAngle + 3.12f).translated (bounds.getCentre()));
    
   
}
   
