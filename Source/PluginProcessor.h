/*
==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.
==============================================================================
  Description

 Initialises the default functions and variables in the class.
 Overrides any Pure Virtual Functions.
=============================================================================
*/
//                               References
//                           (DrBrusin, 2022)
///                            (JUCE, Unknown)
///                            (David-Badiane, 2020)
#pragma once

#include <JuceHeader.h>
#include "HorizontalLevelMeter.h"
#include "ParamID.h"
#include "SineWave.h"
#include "Oscillator1.h"
#include "Oscillator2.h"
#include "Oscillator3.h"
#include "Oscillator4.h"
#include "Oscillator5.h"
#include "Oscillator6.h"
#include "Oscillator7.h"
#include "Oscillator8.h"
#include "Oscillator9.h"
#include "CircularBuffer.h"


//==============================================================================
/**
*/
class BastowSynthAudioProcessor  : public juce::AudioProcessor, public juce::MidiKeyboardStateListener
{
public:
    //==============================================================================
    BastowSynthAudioProcessor();
    ~BastowSynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill);
     
    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void processBlock2 (juce::AudioBuffer<double>& buffer, juce::MidiBuffer& midiMessages);
    void updateFilter();
    void process(juce::dsp::ProcessContextReplacing<float> context);
    void initialiseSynth();
    float getRMSValue(const int channel) const;
    juce::MidiMessageCollector* getMidiCollector();
    //==============================================================================
                                //Public Variables
    //==============================================================================
    
    double FreqSlider;
    double FreqSlider2;
    double FreqSlider3;
    double FreqSlider4;
    double FreqSlider5;
    double FreqSlider6;
    double FreqSlider7;
    double FreqSlider8;
    double FreqSlider9;
    double masterVolume;
    double originalVolume;
    double Harm1Volume;
    double Harm2Volume;
    double Harm3Volume;
    double Harm4Volume;
    double Harm5Volume;
    double Harm6Volume;
    double Harm7Volume;
    double Harm8Volume;
    double Harm9Volume;
    int numVoices;
    double cutoff;
    float level = 0.0f;
   
    juce::Random random;


    juce::MidiKeyboardState keyboardState;
    juce::AudioVisualiserComponent WaveView;
    juce::AudioProcessorValueTreeState tree;
    juce::MidiMessageCollector midiCollector;
    
 juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::LinearSmoothedValue<float> smooth { 0.0f};
    float limiterThresh = 0.4, attackTime = 0.001, releaseTime = 0.2;
private:
    //==============================================================================
                                //Private Variables
    //==============================================================================
    
    float rmsLevelLeft;
    float rmsLevelRight;
    float previousGain;
    float previousGain2;
    float previousGain3;
    float previousGain4;
    float previousGain5;
    float previousGain6;
    float previousGain7;
    float previousGain8;
    float previousGain9;
    float previousGainMaster;
    float previousGainOriginal;
    
    float gain, xPeak;
    juce::Array<CircularBuffer> allBuffers;
    juce::AudioProcessorEditor* editor = getActiveEditor();
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter <float>, juce::dsp::IIR::Coefficients <float>> IIRFilter;
    
    double lastSampleRate;
    int lastInputIndex = 0;
    bool isAddingFromMidiInput;
    juce::Array<juce::MidiMessage> incomingMessages;
    juce::CriticalSection midiMonitorLock;
    //==============================================================================
                                //Oscillator Sound
    //==============================================================================
    
    juce::Synthesiser mySynth;
    juce::Synthesiser mySynth2;
    juce::Synthesiser mySynth3;
    juce::Synthesiser mySynth4;
    juce::Synthesiser mySynth5;
    juce::Synthesiser mySynth6;
    juce::Synthesiser mySynth7;
    juce::Synthesiser mySynth8;
    juce::Synthesiser mySynth9;
    juce::Synthesiser mySynth10;

    //==============================================================================
                                //Oscillator Voice
    //==============================================================================
    
    SineWaveVoice* mySine;
    SineWaveVoice2* mySine2;
    SineWaveVoice3* mySine3;
    SineWaveVoice4* mySine4;
    SineWaveVoice5* mySine5;
    SineWaveVoice6* mySine6;
    SineWaveVoice7* mySine7;
    SineWaveVoice8* mySine8;
    SineWaveVoice9* mySine9;
   

    //==============================================================================
                                //Private Functions
    //==============================================================================
    
    void handleNoteOff(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOn(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    void handlePitchWheel(juce::MidiKeyboardState*, int midiChannel, int wheelValue);
    void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message);
    void setMidiInput(int index);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BastowSynthAudioProcessor)
};

