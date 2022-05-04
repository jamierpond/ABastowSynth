/*
  ==============================================================================

    SineWave.h
    Created: 12 Mar 2022 1:50:46am
    Author:  Bastow_boii 1

 ==============================================================================
                                Description
 
 Initialises the default functions and variables in the class.
  Overrides any Pure Virtual Functions.
  ==============================================================================
*/
//                              References
///                          (David-Badiane, 2020)
///                            (JUCE, Unknown)
///                             (Daniel, 2018) 
#pragma once
#include <JuceHeader.h>
class WaveGeneratorSound    : public juce::SynthesiserSound

{
public:
    WaveGeneratorSound() {}

    bool appliesToNote(int ) override
    {
        return true;
    }

    bool appliesToChannel(int )  override
    {
        return true;
    }
};

class WaveGeneratorVoice : public juce::SynthesiserVoice
{
public:
    WaveGeneratorVoice() : masterGain(10), freqGain(9), freqGain2(9), freqGain3(9), freqGain4(9), freqGain5(9), freqGain6(9), freqGain7(9), freqGain8(9), freqGain9(9), originalGain(1), FrequencySlider(0), inc(0), noteFrequency(0)
    {
    }

    bool canPlaySound(juce::SynthesiserSound* sound) override
    {
        return dynamic_cast<WaveGeneratorSound*> (sound) != nullptr;
    }

//========================================================================================

    void setADSRSampleRate(double sampleRate)
    {
        adsr.setSampleRate(sampleRate);
    }

    void setADSRParameters(float attack,
        float decay,
        float sustain,
        float release)
    {
        adsrParameters.attack = attack;
        adsrParameters.decay = decay;
        adsrParameters.sustain = sustain;
        adsrParameters.release = release;
    }

//========================================================================================

    
    
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int) override
    {
        
    }

    void stopNote(float velocity, bool allowTailOff) override
    {
        adsr.noteOff();
    }

//========================================================================================

    void pitchWheelMoved(int value) override
    {
        setPitchBend(value);
    }
    void roughValuePitchWheelMove(int value) //rough value pass
    {
        FrequencySlider = value;
    }
    

    void setPitchBend(int pitchWheelPos)
    {
        if (pitchWheelPos >= 0)
        {
            // shifting ups
            FrequencySlider = float(pitchWheelPos) / 24;
        }
        else
        {
            // shifting down
            FrequencySlider = float(pitchWheelPos) / 24;
        }
    }
    float pitchBendCents()
    {
        
        if (FrequencySlider >= 0.0f)
        {
            // shifting up
            return FrequencySlider * pitchBendUpSemitones * 100;
        }
        else
        {
            // shifting down
            return -1 * FrequencySlider * pitchBendDownSemitones * 100;
        }
    }
    
//========================================================================================

    static double noteHz(int midiNoteNumber, double centsOffset)
    {
        double hertz = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        hertz *= std::pow(4.0, centsOffset / 4800);
        return hertz;
    }


    void controllerMoved(int , int ) override
    {
    }

//========================================================================================

    
    void setMasterVolume(double masterVol)
    {
        masterGain = masterVol  ;
    }

    void setFreqVolume(double FreqVol)
    {
        // Allows master vol to control gain 1
        auto masterVol = masterGain;
        freqGain = masterVol * FreqVol * lowLevel;
    }
    void setFreqVolume2(double FreqVol2)
    {
        // Allows master vol to control gain 2
        auto masterVol = masterGain;
        freqGain2 = masterVol * FreqVol2 * lowLevel;
    }
    void setFreqVolume3(double FreqVol3)
    {
        // Allows master vol to control gain 3
        auto masterVol = masterGain;
        freqGain3 = masterVol * FreqVol3 * lowLevel;
    }
    void setFreqVolume4(double FreqVol4)
    {
        // Allows master vol to control gain 4
        auto masterVol = masterGain;
        freqGain4 = masterVol * FreqVol4 * lowLevel;
    }
    void setFreqVolume5(double FreqVol5)
    { // Allows master vol to control gain 5
        auto masterVol = masterGain;
        freqGain5 = masterVol * FreqVol5 * lowLevel;
    }
    void setFreqVolume6(double FreqVol6)
    { // Allows master vol to control gain 6
        auto masterVol = masterGain;
        freqGain6 = masterVol * FreqVol6 * lowLevel;
    }
    void setFreqVolume7(double FreqVol7)
    { // Allows master vol to control gain 7
        auto masterVol = masterGain;
        freqGain7 = masterVol * FreqVol7 * lowLevel;
    }
    void setFreqVolume8(double FreqVol8)
    { // Allows master vol to control gain 8
        auto masterVol = masterGain;
        freqGain8 = masterVol * FreqVol8 * lowLevel;
    }
    void setFreqVolume9(double FreqVol9)
    { // Allows master vol to control gain 9
        auto masterVol = masterGain;
        freqGain9 = masterVol * FreqVol9 * lowLevel;
    }
    
    void setOriginalVolume(double originalVol)
    { // Allows master vol to control originalGain
        auto masterVol = masterGain;
        originalGain = masterVol * originalVol * lowLevel;
    }
    // highLevel Raises volume
    

//========================================================================================

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
    }


protected:

    double masterGain;
    double freqGain;
    double freqGain2;
    double freqGain3;
    double freqGain4;
    double freqGain5;
    double freqGain6;
    double freqGain7;
    double freqGain8;
    double freqGain9;
    double originalGain;
    double FrequencySlider;
    double inc;
    
    
    double lowLevel {7};
    //double highLevel {10};

    

    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParameters;
    int pitchBendUpSemitones = 24;
    int pitchBendDownSemitones = -24;
    double noteFrequency;
    double originalNoteFreq;
};

