/*
  ==============================================================================

    CircularBuffer.h
    Created: 11 Apr 2022 12:28:28am
    Author:  Bastow_boii 1

  ==============================================================================
*/
//                              References
///                           (Rycroft, A., 2020)

#pragma once
#include <JuceHeader.h>

class CircularBuffer {
public:

    CircularBuffer();
    CircularBuffer(int bufferSize, int delayLength);
    float getData();
    void setData(float data);
    void nextSample();
private:
    juce::AudioSampleBuffer buffer;
    int writeIndex;
    int readIndex;
    int delayLength;
};
