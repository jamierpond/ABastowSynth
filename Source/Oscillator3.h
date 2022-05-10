/*
  ==============================================================================

    Oscillator3.h
    Created: 19 Mar 2022 12:14:07am
    Author:  Bastow_boii 1
 ==============================================================================
                                Description
 
 Inherits from WaveGeneratorVoice.
 Oscilator 3, creates sine wave adds it to the audio buffer.
  =============================================================================
*/
//                              References
///                          (David-Badiane, 2020)
///                            (JUCE, Unknown)
#include <JuceHeader.h>
#include "SineWave.h"
#pragma once

class SineWaveSound3 : public WaveGeneratorSound{};


class SineWaveVoice3 : public WaveGeneratorVoice{

public:
    SineWaveVoice3() : currentAngle3(0), angleDelta3(0), level(0) {}

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int) override
    {
        noteFrequency = noteHz(midiNoteNumber,   pitchBendCents())  ; //change make 0.3 a customizeable value
        adsr.noteOn();
        inc = 0;
        currentAngle3 = 0.0;
        level = velocity * 0.20 ;
        
        inc = noteFrequency / getSampleRate();
        angleDelta3 = inc * 2.0 * juce::MathConstants<double>::pi;
        
    }
    
    void stopNote(float velocity, bool allowTailOff) override
    {
        adsr.noteOff();
       
    }
    
    

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        adsr.setSampleRate(getSampleRate());
        adsr.setParameters(adsrParameters);
        processBlock(outputBuffer, startSample, numSamples);
    }


private :

    void processBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
    {
    
        while (--numSamples >= 0)
        {
            
             auto SliderAudio = level * freqGain2;
             auto GainAudio = std::sin(currentAngle3) * SliderAudio;
             auto MasterAudio = GainAudio * masterGain;
             auto Sample = (float)(MasterAudio);
            
            for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample(i, startSample, adsr.getNextSample() * Sample);

            currentAngle3 += angleDelta3;
            ++startSample;
        }
    }

    double currentAngle3, angleDelta3, level;
};

