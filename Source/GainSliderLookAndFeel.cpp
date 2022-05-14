/*
  ==============================================================================

    Freq1LAF.cpp
    Created: 2 Apr 2022 12:08:24am
    Author:  Bastow_boii 1
 ==============================================================================
                                Description

 Uses Juce functions to draw a slider.
  ==============================================================================
*/
//                              References
///                            (Kengo, S., 2021)
///                            (JUCE, Unknown)

#include "GainSliderLookAndFeel.h"

GainSliderLookAndFeel::GainSliderLookAndFeel(){};
GainSliderLookAndFeel::~GainSliderLookAndFeel(){};

void GainSliderLookAndFeel::drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                       float sliderPos,
                       float minSliderPos,
                       float maxSliderPos,
                       const juce::Slider::SliderStyle style, juce::Slider& slider)

{
    //=============================================================================
                                            //Creates BackgroundTrack for Slider
    //==============================================================================
  
    g.setColour (juce::Colours::ghostwhite.darker(0.075f));

    auto trackWidthFrequencyBackground1 = juce::jmin (19.5f, (float) height * 10.f );
    
    juce::Point<float> pos1 (slider.isHorizontal() ? (float) x : (float) x + (float) width * 0.5f,
                                   slider.isHorizontal() ? (float) y + (float) height * 10.5f : (float) (height + y));

    juce::Point<float> pos2 (slider.isHorizontal() ? (float) (width + x) : pos1.x,
                                 slider.isHorizontal() ? pos1.y : (float) y);
    
    juce::Path trackBackround;
    trackBackround.startNewSubPath (pos1);
    trackBackround.lineTo (pos2);
    
    g.setColour (juce::Colours::ghostwhite.darker(0.075f));
    g.strokePath (trackBackround, { trackWidthFrequencyBackground1, juce::PathStrokeType::curved, juce::PathStrokeType::rounded });
    
    //==============================================================================
                                            //Creates Track for Slider
    //==============================================================================
    
    auto trackWidthFrequency1 = juce::jmin (8.5f, (float) height );

    juce::Point<float> startPoint (slider.isHorizontal() ? (float) x : (float) x + (float) width * 0.5f,
                                   slider.isHorizontal() ? (float) y + (float) height * 0.5f : (float) (height + y));

    juce::Point<float> endPoint (slider.isHorizontal() ? (float) (width + x) : startPoint.x,
                                 slider.isHorizontal() ? startPoint.y : (float) y);
    
    juce::Path track;
           track.startNewSubPath (startPoint);
           track.lineTo (endPoint);
    
    g.setColour (mainSliderColour);
   
    g.strokePath (track, { trackWidthFrequency1, juce::PathStrokeType::curved, juce::PathStrokeType::rounded });
    
    //==============================================================================
                                        // Creates dotted Track for slider
    //==============================================================================
    
    juce::Path dottedTrack;
           juce::Point<float> minPoint, maxPoint, thumbPoint;
    
    minPoint = { minSliderPos, (float) height * 0.5f };
               maxPoint = { maxSliderPos, (float) height * 0.5f };
               thumbPoint = { sliderPos, (float) height * 0.5f };

    auto kx = slider.isHorizontal() ? sliderPos : ((float) x + (float) width * 0.5f);
    auto ky = slider.isHorizontal() ? ((float) y + (float) height * 0.5f) : sliderPos;

              minPoint = startPoint;
              maxPoint = { kx, ky };
    
    auto minThumbWidth = getSliderThumbRadius (slider) - 22;
           auto maxThumbWidth = getSliderThumbRadius (slider) - 26;
                           
    
   
    
    dottedTrack.startNewSubPath (minPoint);
    dottedTrack.lineTo (maxPoint);
    
    g.setColour (juce::Colours::white.brighter(0.5f));
           juce::PathStrokeType dottedStrokeType (2.f);
    float dashedLen[4] = {2, 4, 3, 5};
    dottedStrokeType.createDashedStroke(dottedTrack, dottedTrack, dashedLen, 2);
   
           g.strokePath(dottedTrack, dottedStrokeType);
    

    //==============================================================================
    // Draws Thumb Rest
    //==============================================================================
  
    g.setColour (offWhite.brighter(5.5f));
                                    g.drawRoundedRectangle (juce::Rectangle<float> (static_cast<float> (x ? maxThumbWidth : minThumbWidth),
                                                                                    static_cast<float> (x ? maxThumbWidth : minThumbWidth))
                                                                                    .withCentre (x ? maxPoint : minPoint), 1000, 10.5);
    
   
                  
int thumbBeingDragged = slider.getThumbBeingDragged();
    
    slider.setMouseCursor (juce::MouseCursor::NoCursor);
                    
    //==============================================================================
    // Decoration for Thumb Rest
    //==============================================================================
    
    g.setColour (red.darker(0.08f));
                                    g.drawRoundedRectangle (juce::Rectangle<float> (static_cast<float> (x ? maxThumbWidth : minThumbWidth),
                                                                                    static_cast<float> (x ? maxThumbWidth : minThumbWidth))
                                                                                    .withCentre (x ? maxPoint : minPoint), 50, 2.0);
    
    
    
    g.setColour (juce::Colours::black.brighter(0.5f));
                    g.fillEllipse (juce::Rectangle<float> (static_cast<float> (thumbBeingDragged == 1 ? minThumbWidth : maxThumbWidth),
                                                           static_cast<float> (thumbBeingDragged == 1 ? minThumbWidth : maxThumbWidth))
                                                           .withCentre (thumbBeingDragged == 1 ? minPoint : maxPoint));
    
    g.setColour (blackGrey);
                    g.drawRoundedRectangle (juce::Rectangle<float>(static_cast<float> (maxThumbWidth), static_cast<float> (maxThumbWidth)).withCentre (maxPoint), 50, 1.0);
    

    

    
    slider.setMouseCursor (juce::MouseCursor::NormalCursor);
                  


    auto sliderThumbP1 = getSliderThumbRadius (slider) - 19;
    auto sliderThumbP2 = getSliderThumbRadius (slider) - 19;
    g.setColour (offWhite.brighter(5.5f));
                    g.fillEllipse (juce::Rectangle<float> (static_cast<float> (x ? sliderThumbP1 : sliderThumbP2),
                                                           static_cast<float> (x ? sliderThumbP1 : sliderThumbP2))
                                                           .withCentre (x ? minPoint : maxPoint));
    
}
