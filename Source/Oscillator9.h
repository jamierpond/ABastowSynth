/*
  ==============================================================================

    Oscillator9.h
    Created: 19 Mar 2022 2:11:59am
    Author:  Bastow_boii 1
 =============================================================================
                                Description
 
 Inherits from WaveGeneratorVoice.
 Oscilator 9, creates sine wave adds it to the audio buffer.
  =============================================================================
*/
//                              References
///                          (David-Badiane, 2020)
///                            (JUCE, Unknown)
#include <JuceHeader.h>
#include "SineWave.h"

#pragma once

class SineWaveSound9 : public WaveGeneratorSound{};


class SineWaveVoice9 : public WaveGeneratorVoice{ /* public Sine */

public:
    SineWaveVoice9() : currentAngle9(0), angleDelta9(0), level(0) {}

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int) override{

        noteFrequency = noteHz(midiNoteNumber,  pitchBendCents()) ;
        originalNoteFreq = noteFrequency;
        adsr.noteOn();
        inc = 0;
        currentAngle9 = 0.0;
        level = velocity * 0.20 ;
        
        inc = noteFrequency / getSampleRate();
        angleDelta9 = inc * 2.0 * juce::MathConstants<double>::pi;
        
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

            
             auto SliderAudio = level * freqGain8;
             auto GainAudio = std::sin(currentAngle9) * SliderAudio;
             auto MasterAudio = GainAudio * masterGain;
             auto Sample = (float)(MasterAudio);
            
            for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample(i, startSample, adsr.getNextSample() * Sample);

            currentAngle9 += angleDelta9;
            ++startSample;
        }
    }

    double currentAngle9, angleDelta9, level;
};

