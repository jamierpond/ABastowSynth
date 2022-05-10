/*
==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.
 ==============================================================================
   Description

 Creates parameter layout, creates limiter, creates filter, adds synth voices and sounds, turns note on and off, smoothing gain adsr, sets samplerates, clears filters, renders buffers, connects adsr, frequency and gain paramaters and allows presets to be stored.
 


=============================================================================
*/
//                               References
//                           (DrBrusin, 2022)
//                            (Kengo, S., 2021)
///                            (JUCE, Unknown)
///                           (Akash Murthy, 2021)
///                           (ColorHexa, Unknown)

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================

BastowSynthAudioProcessor::BastowSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), WaveView(1),
tree(*this, nullptr, "PARAMETERS",createParameterLayout())
    

#endif
{
    WaveView.setRepaintRate(30);
    WaveView.setBufferSize(256);
    WaveView.setSamplesPerBlock(12);
   
    keyboardState.addListener(this);
    numVoices = 10;
    initialiseSynth();
   
 
}

BastowSynthAudioProcessor::~BastowSynthAudioProcessor()
{
   
}



juce::AudioProcessorValueTreeState::ParameterLayout BastowSynthAudioProcessor::createParameterLayout()
{
  std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

  // Make sure to update the number of reservations after adding params
  params.reserve(29);

    auto Attack = std::make_unique<juce::AudioParameterFloat>(attackId, attackName, juce::NormalisableRange<float>(0.1f, 5.0f), 0.2f);
    
    auto Decay = std::make_unique<juce::AudioParameterFloat>(decayId, decayName, juce::NormalisableRange<float>(1.0f, 2.0f), 1.0f);
    
   auto Sustain = std::make_unique<juce::AudioParameterFloat>(sustainId, sustainName, juce::NormalisableRange<float>(0.0f, 1.0f), 0.1f);
    
    auto Release = std::make_unique<juce::AudioParameterFloat>(releaseId, releaseName, juce::NormalisableRange<float>(0.0001f, 8.0f), 0.001f);
    
    auto Res = std::make_unique<juce::AudioParameterFloat>(filterResId, filterResName, juce::NormalisableRange<float>(1.0f, 3.5f, 0.1f), 1.0f);
    
    auto Cutoff = std::make_unique<juce::AudioParameterFloat>(filterCutoffId, filterCutoffName, juce::NormalisableRange<float>(20.0f, 1000.0f, 1, 1), 1000.0f);
    
    auto Menu = std::make_unique<juce::AudioParameterFloat>(filterMenuId, filterMenuName, juce::NormalisableRange<float>(0.0f, 2.0f), 0.0f);
    
    auto Gain1 = std::make_unique<juce::AudioParameterFloat>(gain1Id, gain1Name,juce::NormalisableRange<float>(-64.0f, -12.0f, 1.0),-64.0f);
    
    auto Gain2 = std::make_unique<juce::AudioParameterFloat>(gain2Id, gain2Name,juce::NormalisableRange<float>(-64.0f, -12.0f, 1.0),-64.0f);
    
    auto Gain3 = std::make_unique<juce::AudioParameterFloat>(gain3Id, gain3Name,juce::NormalisableRange<float>(-64.0f, -12.0f, 1.0),-64.0f);

    auto Gain4 = std::make_unique<juce::AudioParameterFloat>(gain4Id, gain4Name,juce::NormalisableRange<float>(-64.0f, -12.0f, 1.0),-64.0f);
    
    auto Gain5 = std::make_unique<juce::AudioParameterFloat>(gain5Id, gain5Name,juce::NormalisableRange<float>(-64.0f, -12.0f, 1.0),-64.0f);
    
    auto Gain6 = std::make_unique<juce::AudioParameterFloat>(gain6Id, gain6Name,juce::NormalisableRange<float>(-64.0f, -12.0f, 1.0),-64.0f);
    
    auto Gain7 = std::make_unique<juce::AudioParameterFloat>(gain7Id, gain7Name,juce::NormalisableRange<float>(-64.0f, -12.0f, 1.0),-64.0f);
    
    auto Gain8 = std::make_unique<juce::AudioParameterFloat>(gain8Id, gain8Name,juce::NormalisableRange<float>(-64.0f, -12.0f, 1.0),-64.0f);
    
    auto Gain9 = std::make_unique<juce::AudioParameterFloat>(gain9Id, gain9Name,juce::NormalisableRange<float>(-64.0f, -12.0f, 1.0),-64.0f);
    
    auto GainOriginal = std::make_unique<juce::AudioParameterFloat>(gainOriginalId, gainOriginalName,juce::NormalisableRange<float>(-64.0f, -9.0f, 1.0),-9.0f);
    
    auto GainMaster = std::make_unique<juce::AudioParameterFloat>(gainMasterId, gainMasterName,juce::NormalisableRange<float>(-64.0f, -6.0f, 1.0),-9.0f);
    
    auto Frequency1 = std::make_unique<juce::AudioParameterFloat>(frequency1Id, frequency1Name, juce::NormalisableRange<float>(-24.0f, +24.0f, 1.0),1.0f);
    
    auto Frequency2 = std::make_unique<juce::AudioParameterFloat>(frequency2Id, frequency2Name,juce::NormalisableRange<float>(-24.0f, +24.0f, 1.0),1.0f);
    
    auto Frequency3 = std::make_unique<juce::AudioParameterFloat>(frequency3Id, frequency3Name,juce::NormalisableRange<float>(-24.0f, +24.0f, 1.0),1.0f);

    auto Frequency4 = std::make_unique<juce::AudioParameterFloat>(frequency4Id, frequency4Name, juce::NormalisableRange<float>(-24.0f, +24.0f, 1.0),1.0f);
    
    auto Frequency5 = std::make_unique<juce::AudioParameterFloat>(frequency5Id, frequency5Name,juce::NormalisableRange<float>(-24.0f, +24.0f, 1.0),1.0f);
    
    auto Frequency6 = std::make_unique<juce::AudioParameterFloat>(frequency6Id, frequency6Name, juce::NormalisableRange<float>(-24.0f, +24.0f, 1.0),1.0f);
    
    auto Frequency7 = std::make_unique<juce::AudioParameterFloat>(frequency7Id, frequency7Name, juce::NormalisableRange<float>(-24.0f, +24.0f, 1.0),1.0f);
    
    auto Frequency8 = std::make_unique<juce::AudioParameterFloat>(frequency8Id, frequency8Name, juce::NormalisableRange<float>(-24.0f, +24.0f, 1.0),1.0f);
    
    auto Frequency9 = std::make_unique<juce::AudioParameterFloat>(frequency9Id, frequency9Name, juce::NormalisableRange<float>(-24.0f, +24.0f, 1.0),1.0f);
    
    params.push_back(std::move(Frequency1));
    params.push_back(std::move(Frequency2));
    params.push_back(std::move(Frequency3));
    params.push_back(std::move(Frequency4));
    params.push_back(std::move(Frequency5));
    params.push_back(std::move(Frequency6));
    params.push_back(std::move(Frequency7));
    params.push_back(std::move(Frequency8));
    params.push_back(std::move(Frequency9));
    params.push_back(std::move(Attack));
    params.push_back(std::move(Decay));
    params.push_back(std::move(Sustain));
    params.push_back(std::move(Release));
    params.push_back(std::move(Res));
    params.push_back(std::move(Cutoff));
    params.push_back(std::move(Menu));
    params.push_back(std::move(Gain1));
    params.push_back(std::move(Gain2));
    params.push_back(std::move(Gain3));
    params.push_back(std::move(Gain4));
    params.push_back(std::move(Gain5));
    params.push_back(std::move(Gain6));
    params.push_back(std::move(Gain7));
    params.push_back(std::move(Gain8));
    params.push_back(std::move(Gain9));
    params.push_back(std::move(GainOriginal));
    params.push_back(std::move(GainMaster));


  return { params.begin(), params.end() };
}

void  BastowSynthAudioProcessor::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message)
{
    const juce::ScopedValueSetter<bool> scopedInputFlag(isAddingFromMidiInput, true);
    keyboardState.processNextMidiEvent(message);
}

void BastowSynthAudioProcessor::handleNoteOn(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    juce::MidiMessage m (juce::MidiMessage::noteOn (midiChannel, midiNoteNumber, velocity));

    mySynth.noteOn( midiChannel, midiNoteNumber, velocity);
    mySynth2.noteOn( midiChannel, midiNoteNumber, velocity);
    mySynth3.noteOn( midiChannel, midiNoteNumber, velocity);
    mySynth4.noteOn( midiChannel, midiNoteNumber, velocity);
    mySynth5.noteOn( midiChannel, midiNoteNumber, velocity);
    mySynth6.noteOn( midiChannel, midiNoteNumber, velocity);
    mySynth7.noteOn( midiChannel, midiNoteNumber, velocity);
    mySynth8.noteOn( midiChannel, midiNoteNumber, velocity);
    mySynth9.noteOn( midiChannel, midiNoteNumber, velocity);
 
}

void BastowSynthAudioProcessor::handleNoteOff(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    juce::MidiMessage m (juce::MidiMessage::noteOff (midiChannel, midiNoteNumber, velocity));
    
    mySynth.noteOff(midiChannel, midiNoteNumber, velocity,true);
    mySynth2.noteOff(midiChannel, midiNoteNumber, velocity,true);
    mySynth3.noteOff(midiChannel, midiNoteNumber, velocity,true);
    mySynth4.noteOff(midiChannel, midiNoteNumber, velocity,true);
    mySynth5.noteOff(midiChannel, midiNoteNumber, velocity,true);
    mySynth6.noteOff(midiChannel, midiNoteNumber, velocity,true);
    mySynth7.noteOff(midiChannel, midiNoteNumber, velocity,true);
    mySynth8.noteOff(midiChannel, midiNoteNumber, velocity,true);
    mySynth9.noteOff(midiChannel, midiNoteNumber, velocity,true);
    


}

void BastowSynthAudioProcessor::handlePitchWheel(juce::MidiKeyboardState*, int midiChannel,int wheelValue){
    mySynth.handlePitchWheel(midiChannel, wheelValue);
    mySynth2.handlePitchWheel(midiChannel, wheelValue);
    mySynth3.handlePitchWheel(midiChannel, wheelValue);
    mySynth4.handlePitchWheel(midiChannel, wheelValue);
    mySynth5.handlePitchWheel(midiChannel, wheelValue);
    mySynth6.handlePitchWheel(midiChannel, wheelValue);
    mySynth7.handlePitchWheel(midiChannel, wheelValue);
    mySynth8.handlePitchWheel(midiChannel, wheelValue);
    mySynth9.handlePitchWheel(midiChannel, wheelValue);
 
   
}

void BastowSynthAudioProcessor::initialiseSynth()
{
    mySynth.clearVoices();
    mySynth.clearSounds();
    mySynth2.clearVoices();
    mySynth2.clearSounds();
    mySynth3.clearVoices();
    mySynth3.clearSounds();
    mySynth4.clearVoices();
    mySynth4.clearSounds();
    mySynth5.clearVoices();
    mySynth5.clearSounds();
    mySynth6.clearVoices();
    mySynth6.clearSounds();
    mySynth7.clearVoices();
    mySynth7.clearSounds();
    mySynth8.clearVoices();
    mySynth8.clearSounds();
    mySynth9.clearVoices();
    mySynth9.clearSounds();
 ;
   
    for (int i = numVoices; --i >= 0;) {
        mySynth.addVoice(new SineWaveVoice());
        mySynth2.addVoice(new SineWaveVoice2());
        mySynth3.addVoice(new SineWaveVoice3());
        mySynth4.addVoice(new SineWaveVoice4());
        mySynth5.addVoice(new SineWaveVoice5());
        mySynth6.addVoice(new SineWaveVoice6());
        mySynth7.addVoice(new SineWaveVoice7());
        mySynth8.addVoice(new SineWaveVoice8());
        mySynth9.addVoice(new SineWaveVoice9());
      
    }

    mySynth.addSound(new SineWaveSound());
    mySynth2.addSound(new SineWaveSound2());
    mySynth3.addSound(new SineWaveSound3());
    mySynth4.addSound(new SineWaveSound4());
    mySynth5.addSound(new SineWaveSound5());
    mySynth6.addSound(new SineWaveSound6());
    mySynth7.addSound(new SineWaveSound7());
    mySynth8.addSound(new SineWaveSound8());
    mySynth9.addSound(new SineWaveSound9());
   



    
    }

//==============================================================================
const juce::String BastowSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}


bool BastowSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BastowSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BastowSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BastowSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BastowSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BastowSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BastowSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void BastowSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BastowSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    midiCollector.reset (sampleRate);
    
   // smooths sliders
    float attack = *tree.getRawParameterValue(attackId);
    float release = *tree.getRawParameterValue(releaseId);
    float sustain = *tree.getRawParameterValue(sustainId);
    float decay = *tree.getRawParameterValue(decayId);
    
    float currentGainMaster = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainMasterId) + 0.0);
    float currentGainOriginal = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainOriginalId) + 0.0);
    float currentGain = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain1Id) + 0.0);
    float currentGain2 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain2Id) + 0.0);
    float currentGain3 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain3Id) + 0.0);
    float currentGain4 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain4Id) + 0.0);
    float currentGain5 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain5Id) + 0.0);
    float currentGain6 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain6Id) + 0.0);
    float currentGain7 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain7Id) + 0.0);
    float currentGain8 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain8Id) + 0.0);
    
    
    smooth.reset(sampleRate, 5.1);
    smooth.setTargetValue(attack);
    smooth.getNextValue();
    
    smooth.reset(sampleRate, 5.1);
    smooth.setTargetValue(release);
    smooth.getNextValue();
    
    smooth.reset(sampleRate, 5.1);
    smooth.setTargetValue(sustain);
    smooth.getNextValue();
    
    smooth.reset(sampleRate, 5.1);
    smooth.setTargetValue(decay);
    smooth.getNextValue();
    
    smooth.reset(sampleRate, 0.1);
    smooth.setTargetValue(currentGain);
    smooth.getNextValue();
    
    smooth.reset(sampleRate, 0.1);
    smooth.setTargetValue(currentGain2);
    smooth.getNextValue();
    
    smooth.reset(sampleRate, 0.1);
    smooth.setTargetValue(currentGain3);
    smooth.getNextValue();
    
    smooth.reset(sampleRate, 0.1);
    smooth.setTargetValue(currentGain4);
    smooth.getNextValue();
    
    smooth.reset(sampleRate, 0.1);
    smooth.setTargetValue(currentGain5);
    smooth.getNextValue();
    
    smooth.reset(sampleRate, 0.1);
    smooth.setTargetValue(currentGain6);
    smooth.getNextValue();
    
    smooth.reset(sampleRate, 0.1);
    smooth.setTargetValue(currentGain7);
    smooth.getNextValue();
    
    smooth.reset(sampleRate, 0.1);
    smooth.setTargetValue(currentGain8);
    smooth.getNextValue();
    
    smooth.reset(sampleRate, 0.1);
    smooth.setTargetValue(currentGainMaster);
    smooth.getNextValue();
    
    smooth.reset(sampleRate, 0.1);
    smooth.setTargetValue(currentGainOriginal);
    smooth.getNextValue();

    
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    mySynth2.setCurrentPlaybackSampleRate(lastSampleRate);
    mySynth3.setCurrentPlaybackSampleRate(lastSampleRate);
    mySynth4.setCurrentPlaybackSampleRate(lastSampleRate);
    mySynth5.setCurrentPlaybackSampleRate(lastSampleRate);
    mySynth6.setCurrentPlaybackSampleRate(lastSampleRate);
    mySynth7.setCurrentPlaybackSampleRate(lastSampleRate);
    mySynth8.setCurrentPlaybackSampleRate(lastSampleRate);
    mySynth9.setCurrentPlaybackSampleRate(lastSampleRate);
   

    juce::dsp::ProcessSpec spec;   // the spec class passes the sampleRate, num channels and maximumblock size
    spec.sampleRate = lastSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    previousGain = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain1Id) + 0.0);
    previousGain2 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain2Id) + 0.0);
    previousGain3 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain3Id) + 0.0);
    previousGain4 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain4Id) + 0.0);
    previousGain5 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain5Id) + 0.0);
    previousGain6 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain6Id) + 0.0);
    previousGain7 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain7Id) + 0.0);
    previousGain8 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain8Id) + 0.0);
    previousGain9 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain9Id) + 0.0);
    previousGainOriginal = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainOriginalId) + 0.0);
    previousGainMaster = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainMasterId) + 0.0);
    
    IIRFilter.reset();
    IIRFilter.prepare(spec);
    
    updateFilter();
    
    allBuffers = juce::Array<CircularBuffer>();

    gain = 1.0f;
    xPeak = 0.0f;

}

void BastowSynthAudioProcessor::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
   {


    bufferToFill.clearActiveBufferRegion();

       
           juce::MidiBuffer incomingMidi;
           midiCollector.removeNextBlockOfMessages (incomingMidi, bufferToFill.numSamples);

         
           keyboardState.processNextMidiBuffer (incomingMidi, 0, bufferToFill.numSamples, true);

        
    mySynth.renderNextBlock (*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
    mySynth2.renderNextBlock (*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
    mySynth3.renderNextBlock (*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
    mySynth4.renderNextBlock (*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
    mySynth5.renderNextBlock (*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
    mySynth6.renderNextBlock (*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
    mySynth7.renderNextBlock (*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
    mySynth8.renderNextBlock (*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
    mySynth9.renderNextBlock (*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
 
       }

juce::MidiMessageCollector* BastowSynthAudioProcessor::getMidiCollector()
{
    return &midiCollector;
}

void BastowSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BastowSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BastowSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear();
    midiMessages.clear();
    

                   
           
           updateFilter();
  
juce::dsp::AudioBlock<float> block(buffer);

 
    //==============================================================================
                                //ADSR
    //==============================================================================
    
    float attack = *tree.getRawParameterValue(attackId);
    float release = *tree.getRawParameterValue(releaseId);
    float sustain = *tree.getRawParameterValue(sustainId);
    float decay = *tree.getRawParameterValue(decayId);
    
    float currentGainMaster = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainMasterId) + 0.0);
    
    //==============================================================================
                                //Oscillator 1
    //==============================================================================
    
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
            if ((mySine = dynamic_cast<SineWaveVoice*>(mySynth.getVoice(i))))
            {
        float currentGainMaster = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainMasterId) + 0.0);
        float currentGainOriginal = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainOriginalId) + 0.0);
                mySine->setMasterVolume(currentGainMaster);
                mySine->setOriginalVolume(currentGainOriginal);
                mySine->setADSRParameters(attack, decay, sustain, release);
           
                //==============================================================================
                                            //Gain Smoother
                //==============================================================================
                
        
                if (currentGainOriginal == previousGainOriginal)
                {
                    buffer.applyGain(currentGainOriginal);
                }
                else
                {
                  
                   buffer.applyGainRamp(0, buffer.getNumSamples(), previousGainOriginal, currentGainOriginal);
                   previousGainOriginal = currentGainOriginal;
                }
                
                if (currentGainMaster == previousGainMaster)
                {
                    buffer.applyGain(currentGainMaster);
                }
                else
                {
                
                   buffer.applyGainRamp(0, buffer.getNumSamples(), previousGainMaster, currentGainMaster);
                   previousGainMaster = currentGainMaster;
                }
              
               
        }
    }

    //==============================================================================
                                //Oscillator 2
    //==============================================================================
    
   for (int i = 0; i < mySynth2.getNumVoices(); i++)
    {
            if ((mySine2 = dynamic_cast<SineWaveVoice2*>(mySynth2.getVoice(i))))
            {
    float currentGainMaster = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainMasterId) + 0.0);
    float currentGain = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain1Id) + 0.0);
    auto frequency1 = (*tree.getRawParameterValue(frequency1Id) + 0.0);
                mySine2->setMasterVolume(currentGainMaster);
                mySine2->setFreqVolume(currentGain);
                mySine2->pitchWheelMoved(frequency1);
                mySine2->setADSRParameters(attack, decay, sustain, release);
                
                //==============================================================================
                                            //Gain Smoother
                //==============================================================================
                
                if (currentGain == previousGain)
                {
                    buffer.applyGain(currentGain);
                }
                else
                {
                 
                   buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain, currentGain);
                   previousGain = currentGain;
                    
                    if (currentGainMaster == previousGainMaster)
                    {
                        buffer.applyGain(currentGainMaster);
                    }
                    else
                    {
                    
                       buffer.applyGainRamp(0, buffer.getNumSamples(), previousGainMaster, currentGainMaster);
                       previousGainMaster = currentGainMaster;
                    }
                }
        }
    }
    
    //==============================================================================
                                //Oscillator 3
    //==============================================================================
    
    for (int i = 0; i < mySynth3.getNumVoices(); i++)
    {
            if ((mySine3 = dynamic_cast<SineWaveVoice3*>(mySynth3.getVoice(i))))
            {
                
float currentGainMaster = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainMasterId) + 0.0);
float currentGain2 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain2Id) + 0.0);
float frequency2 = (*tree.getRawParameterValue(frequency2Id) + 0.0);
                
               
                mySine3->setMasterVolume(currentGainMaster);
                mySine3->setFreqVolume2(currentGain2);
                mySine3->pitchWheelMoved(frequency2);
                mySine3->setADSRParameters(attack, decay, sustain, release);
                
                //==============================================================================
                                            //Gain Smoother
                //==============================================================================
                
                if (currentGain2 == previousGain2)
                {
                    buffer.applyGain(currentGain2);
                }
                else
                {
                  
                   buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain2, currentGain2);
                   previousGain2 = currentGain2;
                    
                    if (currentGainMaster == previousGainMaster)
                    {
                        buffer.applyGain(currentGainMaster);
                    }
                    else
                    {
                     
                       buffer.applyGainRamp(0, buffer.getNumSamples(), previousGainMaster, currentGainMaster);
                       previousGainMaster = currentGainMaster;
                    }
                }
          
        }
    }
  
    //==============================================================================
                                //Oscillator 4
    //==============================================================================
    
    for (int i = 0; i < mySynth4.getNumVoices(); i++)
    {
            if ((mySine4 = dynamic_cast<SineWaveVoice4*>(mySynth4.getVoice(i))))
            {
float currentGainMaster = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainMasterId) + 0.0);
float currentGain3 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain3Id) + 0.0);
float frequency3 = (*tree.getRawParameterValue(frequency3Id) + 0.0);
                
                mySine4->setADSRParameters(attack, decay, sustain, release);
                mySine4->setMasterVolume(currentGainMaster);
                mySine4->setFreqVolume3(currentGain3);
                mySine4->pitchWheelMoved(frequency3);
                
                
                //==============================================================================
                                            //Gain Smoother
                //==============================================================================
                
                if (currentGain3 == previousGain3)
                {
                    buffer.applyGain(currentGain3);
                }
                else
                {
                   buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain3, currentGain3);
                   previousGain3 = currentGain3;
                    
                    if (currentGainMaster == previousGainMaster)
                    {
                        buffer.applyGain(currentGainMaster);
                    }
                    else
                    {;
                       buffer.applyGainRamp(0, buffer.getNumSamples(), previousGainMaster, currentGainMaster);
                       previousGainMaster = currentGainMaster;
                    }
                }
                
                
           
        }
    }
    
    //==============================================================================
                                //Oscillator 5
    //==============================================================================
    
    for (int i = 0; i < mySynth5.getNumVoices(); i++)
    {
            if ((mySine5 = dynamic_cast<SineWaveVoice5*>(mySynth5.getVoice(i))))
            {
                float currentGainMaster = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainMasterId) + 0.0);
                float currentGain4 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain4Id) + 0.0);
                float frequency4 = (*tree.getRawParameterValue(frequency4Id) + 0.0);
                mySine5->setADSRParameters(attack, decay, sustain, release);
                mySine5->setMasterVolume(currentGainMaster);
                mySine5->setFreqVolume4(currentGain4);
                mySine5->pitchWheelMoved(frequency4);
                
                
                //==============================================================================
                                            //Gain Smoother
                //==============================================================================
                
                if (currentGain4 == previousGain4)
                {
                    buffer.applyGain(currentGain4);
                }
                else
                {
                   buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain4, currentGain4);
                   previousGain4 = currentGain4;
                    
                    if (currentGainMaster == previousGainMaster)
                    {
                        buffer.applyGain(currentGainMaster);
                    }
                    else
                    {
                       
                       buffer.applyGainRamp(0, buffer.getNumSamples(), previousGainMaster, currentGainMaster);
                       previousGainMaster = currentGainMaster;
                    }
                }
          
        }
    }
    
    //==============================================================================
                                //Oscillator 6
    //==============================================================================
    
    for (int i = 0; i < mySynth6.getNumVoices(); i++)
    {
            if ((mySine6 = dynamic_cast<SineWaveVoice6*>(mySynth6.getVoice(i))))
            {   float currentGainMaster = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainMasterId) + 0.0);
                float currentGain5 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain5Id) + 0.0);
                float frequency5 = (*tree.getRawParameterValue(frequency5Id) + 0.0);
                mySine6->setADSRParameters(attack, decay, sustain, release);
                mySine6->setMasterVolume(currentGainMaster);
                mySine6->setFreqVolume5(currentGain5);
                mySine6->pitchWheelMoved(frequency5);
                
                //==============================================================================
                                            //Gain Smoother
                //==============================================================================
                
                if (currentGain5 == previousGain5)
                {
                    buffer.applyGain(currentGain5);
                }
                else
                {
                 
                   buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain5, currentGain5);
                   previousGain5 = currentGain5;
                    
                    if (currentGainMaster == previousGainMaster)
                    {
                        buffer.applyGain(currentGainMaster);
                    }
                    else
                    {
                       
                       buffer.applyGainRamp(0, buffer.getNumSamples(), previousGainMaster, currentGainMaster);
                       previousGainMaster = currentGainMaster;
                    }
                    
                }
              
        }
    }
    
    //==============================================================================
                                //Oscillator 7
    //==============================================================================
    
    for (int i = 0; i < mySynth7.getNumVoices(); i++)
    {
            if ((mySine7 = dynamic_cast<SineWaveVoice7*>(mySynth7.getVoice(i))))
            {   float currentGainMaster = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainMasterId) + 0.0);
                float currentGain6 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain6Id) + 0.0);
                float frequency6 = (*tree.getRawParameterValue(frequency6Id) + 0.0);
                mySine7->setMasterVolume(currentGainMaster);
                mySine7->setADSRParameters(attack, decay, sustain, release);
                mySine7->setFreqVolume6(currentGain6);
                mySine7->pitchWheelMoved(frequency6);
                
                //==============================================================================
                                            //Gain Smoother
                //==============================================================================
                
                if (currentGain6 == previousGain6)
                {
                    buffer.applyGain(currentGain6);
                }
                else
                {
                    
                
                   buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain6, currentGain6);
                   previousGain6 = currentGain6;
                    
                    if (currentGainMaster == previousGainMaster)
                    {
                        buffer.applyGain(currentGainMaster);
                    }
                    else
                    {
                    
                       buffer.applyGainRamp(0, buffer.getNumSamples(), previousGainMaster, currentGainMaster);
                       previousGainMaster = currentGainMaster;
                    }
                }
        }
    }
  
    //==============================================================================
                                //Oscillator 8
    //==============================================================================
    
    for (int i = 0; i < mySynth8.getNumVoices(); i++)
    {
            if ((mySine8 = dynamic_cast<SineWaveVoice8*>(mySynth8.getVoice(i))))
            {   float currentGainMaster = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainMasterId) + 0.0);
                float currentGain7 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain7Id) + 0.0);
                float frequency7 = (*tree.getRawParameterValue(frequency7Id) + 0.0);
                mySine8->setADSRParameters(attack, decay, sustain, release);
                mySine8->setMasterVolume(currentGainMaster);
                mySine8->setFreqVolume7(currentGain7);
                mySine8->pitchWheelMoved(frequency7);
                
                //==============================================================================
                                            //Gain Smoother
                //==============================================================================
                
                if (currentGain7 == previousGain7)
                {
                    buffer.applyGain(currentGain7);
                }
                else
                {
                  
                   buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain7, currentGain7);
                   previousGain7 = currentGain7;
                    
                    if (currentGainMaster == previousGainMaster)
                    {
                        buffer.applyGain(currentGainMaster);
                    }
                    else
                    {
                      
                       buffer.applyGainRamp(0, buffer.getNumSamples(), previousGainMaster, currentGainMaster);
                       previousGainMaster = currentGainMaster;
                    }
                }
              
        }
    }
    
    //==============================================================================
                                //Oscillator 9
    //==============================================================================
    
    for (int i = 0; i < mySynth9.getNumVoices(); i++)
    {
            if ((mySine9 = dynamic_cast<SineWaveVoice9*>(mySynth9.getVoice(i))))
            {
                
                float currentGainMaster = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gainMasterId) + 0.0);
                float currentGain8 = juce::Decibels::decibelsToGain(*tree.getRawParameterValue(gain8Id) + 0.0);
                float frequency8 = (*tree.getRawParameterValue(frequency8Id) + 0.0);
                mySine9->setADSRParameters(attack, decay, sustain, release);
                mySine9->setMasterVolume(currentGainMaster);
                mySine9->setFreqVolume8(currentGain8);
                mySine9->pitchWheelMoved(frequency8);
                
                //==============================================================================
                                            //Gain Smoother
                //==============================================================================
                
                if (currentGain8 == previousGain8)
                {
                    buffer.applyGain(currentGain8);
                }
                else
                {
               
                   buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain8, currentGain8);
                   previousGain8 = currentGain8;
                    
                    if (currentGainMaster == previousGainMaster)
                    {
                        buffer.applyGain(currentGainMaster);
                    }
                    else
                    {
                       //buffer.applyGain(currentGain);
                       buffer.applyGainRamp(0, buffer.getNumSamples(), previousGainMaster, currentGainMaster);
                       previousGainMaster = currentGainMaster;
                    }
                }
                
        }
    }
    
    if (currentGainMaster == previousGainMaster)
    {
        buffer.applyGain(currentGainMaster);
    }
    else
    {
       //buffer.applyGain(currentGain);
       buffer.applyGainRamp(0, buffer.getNumSamples(), previousGainMaster, currentGainMaster);
       previousGainMaster = currentGainMaster;
    }

    //==============================================================================
                                //Process Buffer
    //==============================================================================


    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    mySynth2.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    mySynth3.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    mySynth4.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    mySynth5.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    mySynth6.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    mySynth7.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    mySynth8.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    mySynth9.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
                   
                   WaveView.pushBuffer(buffer);
    
    
    IIRFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
    
    //==============================================================================
                                //Limiter
    //==============================================================================
    
    for (int channel = 0; channel < buffer.getNumChannels(); channel++) {
        allBuffers.add(CircularBuffer(100, 1));
    }
    
  
    
    float coeff;

    for (int i = 0; i < buffer.getNumSamples(); i++) {
        for (int channel = 0; channel < buffer.getNumChannels(); channel++) {
            auto* data = buffer.getWritePointer(channel);
            CircularBuffer* delayBuffer = &allBuffers.getReference(channel);

            float sample = data[i];

            float amplitude = abs(sample);

            if (amplitude > xPeak) coeff = attackTime;
            else coeff = releaseTime;

            xPeak = (1 - coeff) * xPeak + coeff * amplitude;

            float filter = fmin(1.0f, limiterThresh / xPeak);

            if (level > filter) coeff = attackTime;
            else coeff = releaseTime;

            level = (1 - coeff) * level + coeff * filter;

            float limitedSample = level * delayBuffer->getData();
            delayBuffer->setData(sample);
            delayBuffer->nextSample();

            data[i] = limitedSample;
        }
    }
    rmsLevelLeft =  juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
     rmsLevelRight =  juce::Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
   
}

float BastowSynthAudioProcessor::getRMSValue(const int channel) const
{
    jassert(channel == 0 || channel == 1);
    if (channel == 0)
        return rmsLevelLeft;
    if (channel == 1)
        return rmsLevelRight;
    return 0.f;
}
void BastowSynthAudioProcessor::setMidiInput(int index)
{
    
}

void BastowSynthAudioProcessor::updateFilter()
{

    int menuChoice = *tree.getRawParameterValue(filterMenuId);
    int res = *tree.getRawParameterValue(filterResId);
    float cutoff = *tree.getRawParameterValue(filterCutoffId);

    
    if (menuChoice == 0)
    {
      
        *IIRFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(lastSampleRate, cutoff, res);
    }
    if (menuChoice == 1)
    {
     
        *IIRFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(lastSampleRate, cutoff, res);

    }
    if (menuChoice == 2)
    {
      
        *IIRFilter.state = *juce::dsp::IIR::Coefficients<float>::makeBandPass(lastSampleRate, cutoff, res);
    }
    if (menuChoice == 3)
    {
        *IIRFilter.state = *juce::dsp::IIR::Coefficients<float>::makeNotch(lastSampleRate, cutoff, res);
    }
    if (menuChoice == 4)
    {
        *IIRFilter.state = *juce::dsp::IIR::Coefficients<float>::makeNotch(lastSampleRate, cutoff, res);
    }
}
//==============================================================================
bool BastowSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BastowSynthAudioProcessor::createEditor()
{
    return new BastowSynthAudioProcessorEditor (*this);
}

//==============================================================================
void BastowSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
   
    juce::MemoryOutputStream stream(destData, false);
    tree.state.writeToStream (stream);
}

void BastowSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto treeState = juce::ValueTree::readFromData (data, size_t(sizeInBytes));
  
    
    if (treeState.isValid())
    {
        tree.state = treeState;
   
    }
}
 
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BastowSynthAudioProcessor();
}

