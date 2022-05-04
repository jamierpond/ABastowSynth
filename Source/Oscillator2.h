/*
  ==============================================================================

    Oscillator2.h
    Created: 18 Mar 2022 11:48:14pm
    Author:  Bastow_boii 1
 ==============================================================================
                                Description
 
 Inherits from WaveGeneratorVoice.
 Oscilator 2, creates sine wave adds it to the audio buffer.
  ==============================================================================
*/
//                              References
///                          (David-Badiane, 2020)
///                            (JUCE, Unknown)
#include <JuceHeader.h>
#include "SineWave.h"
#pragma once

class SineWaveSound2 : public WaveGeneratorSound{};


class SineWaveVoice2 : public WaveGeneratorVoice{ 

public:
    SineWaveVoice2() : currentAngle2(0), angleDelta2(0), level(0) {}

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int) override{

        noteFrequency = noteHz(midiNoteNumber, pitchBendCents()) ;
        originalNoteFreq = noteFrequency;
        adsr.noteOn();
        inc = 0;
        currentAngle2 = 0.0;
        level = velocity * 0.20 ;
        
        inc = noteFrequency / getSampleRate();
        angleDelta2 = inc * 2.0 * juce::MathConstants<double>::pi;
        
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

            
             auto SliderAudio = level * freqGain;
             auto GainAudio = std::sin(currentAngle2) * SliderAudio;
             auto MasterAudio = GainAudio * masterGain;
             auto Sample = (float)(MasterAudio);
            
            for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample(i, startSample, adsr.getNextSample() * Sample);

            currentAngle2 += angleDelta2;
            ++startSample;
        }
    }

    double currentAngle2, angleDelta2, level;
};

