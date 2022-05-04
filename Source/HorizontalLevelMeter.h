/*
  ==============================================================================

    HorizontalLevelMeter.h
    Created: 19 Apr 2022 2:56:40pm
    Author:  Bastow_boii 1
 ==============================================================================
                                Description

Sets the default functions and variables in the class
 Overrides any Pure Virtual Functions.
 
 Setting the range that the plugin editor will repaint
  ==============================================================================
*/
//                               References
///                           (Akash Murthy, 2021)
///                           (ColorHexa, Unknown)

#pragma once
#include <JuceHeader.h>
#include "MasterLAF.h"

class HorizontalLevelMeter : public juce::Component
{
public:
    
    void paint(juce::Graphics& g) override
    {

        auto bounds = getLocalBounds().toFloat();

        g.setColour(blackGrey.darker(0.5).withAlpha(0.1f));
                    g.fillRoundedRectangle(bounds * 0.6, 5.f);
  
        
        g.setColour(white.darker(0.5f).withAlpha(0.15f));
        const auto scaledY = juce::jmap(level, -96.f, 3.f, 0.f, static_cast<float>(getWidth()));
        
        g.fillRoundedRectangle(bounds.removeFromLeft (scaledY), 1.5f);
    }
    
    void setLevel(const float value)
    {
        level = value;
    }
      
private:
    //==============================================================================
                                //Private Variables
    //==============================================================================
    
    float level = -96.f;
    
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
    juce::Colour white = juce::Colour::fromFloatRGBA (1, 1, 1, 1.0f);
};

