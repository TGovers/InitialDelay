/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
InitialDelayAudioProcessor::InitialDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), mState(*this, &mUndoManager, "Summative", {
         
         std::make_unique<AudioParameterFloat>("cutoff", "Cutoff", 20.0f, 20000.0f, 600.0f),
         std::make_unique<AudioParameterFloat>("resonance", "Resonance", 1.0f, 5.0f, 1.0f),
         //std::make_unique<AudioParameterFloat>("drive", "Drive", NormalisableRange<float>(0.0f, 1.0f, 0.0001), 0.01f),
         //std::make_unique<AudioParameterFloat>("range", "Range", NormalisableRange<float>(0.0f, 3000.0f, 0.0001), 0.01f),
         //std::make_unique<AudioParameterFloat>("blend", "Blend", NormalisableRange<float>(0.1f, 1.0f, 0.0001), 0.1f),
         //std::make_unique<AudioParameterFloat>("volume", "Volume", NormalisableRange<float>(0.0f, 3.0f, 0.0001), 0.01f),
         std::make_unique<AudioParameterFloat>("delayTime", "DelayTime", 1.0f, 2000.0f, 100.0f),
         std::make_unique<AudioParameterInt>("delayEnable", "DelayEnable", 1, 1000, 1)
         
         
     }), lowPassFilter(dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.1f))


#endif
{
    
}

InitialDelayAudioProcessor::~InitialDelayAudioProcessor()
{
    
}

//==============================================================================
const String InitialDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool InitialDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool InitialDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool InitialDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double InitialDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int InitialDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int InitialDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void InitialDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String InitialDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void InitialDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void InitialDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    currentSampleRate = sampleRate;
    //lastSampleRate = sampleRate;
    
    mSampleRate = sampleRate;
    
    // TAYLOR COMMENT:
    // THIS IS WHERE THE GENERAL DSP IS SETUP
    // AFTER THAT YOU CAN SEE THE SETUP OF THE FILTER, WITH SPEC USED TO PASS THE SAMPLERATE TO THE FILTER DSP
    // RESET IS THEN CALLED TO MAKE SURE IT KEEPS CHECKING/RESETTING
    
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    lowPassFilter.prepare(spec);
    lowPassFilter.reset();
    
    const int numInputChannels = getTotalNumInputChannels();
    const int delayBufferSize = 2 * (sampleRate + samplesPerBlock);
    
    mDelayBuffer.setSize(numInputChannels, delayBufferSize);
    mDelayBuffer.clear ();
    
}

void InitialDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool InitialDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

// TAYLOR COMMENT:
// THIS IS THE FUNCTION USED TO UPDATE THE FILTER WITH NEW SAMPLES
// THIS IS WHERE WE SETUP THE FUNCTION TO CALL LATER
// YOU CAN SEE THAT IT GETS ITS VALUES FROM THE PARAMETERS WE SET AT THE START/UP ABOVE (cutoff, resonance)

void InitialDelayAudioProcessor::updateFilter()
{
    float freq = *mState.getRawParameterValue("cutoff");
    float res = *mState.getRawParameterValue("resonance");
    
    *lowPassFilter.state = *dsp::IIR::Coefficients<float>::makeLowPass(currentSampleRate, freq, res);
}

void InitialDelayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    // WE CREATE "block" THAT TAKES THE AUDIO IN THE BUFFER
    dsp::AudioBlock<float> block (buffer);
    
    // WE UPDATE THE FILTER TO GET CURRENT VALUES CONSTANTLY, YOU WOULD UPDATE WHATEVER EFFECT HERE AS WELL (UNLESS IT WAS IN A LATER LOOP LIKE THE DISTORTION YOU CAN SEE BELOW, DEPENDS ON THE EFFECT)
    updateFilter();
    
    // THE FILTER THEN PROCESSES THE "block" WITH THE CURRENT PARAMETER VALUES
    lowPassFilter.process(dsp::ProcessContextReplacing <float> (block));
    
    //updateDistParameters();
    //overdrive.process(dsp::ProcessContextReplacing <float> (block));
    
    // THIS IS WHERE WE RETRIEVE THE MOST CURRENT VALUES FOR THE DISTORTION PARAMETERS (ITS A SLIGHTLY DIFFERENT PROCESS THAN WITH THE FILTER)
    // WE ARE THEN STORING THEM WITHIN THEIR OWN FLOATS. NOT NECESSARY I DONT THINK BUT MAKES IT EASIER TO WORK WITH
    //float mDrive = *mState.getRawParameterValue("drive");
    //float mRange = *mState.getRawParameterValue("range");
    //float mBlend = *mState.getRawParameterValue("blend");
    //float mVolume = *mState.getRawParameterValue("volume");
    
    AudioBuffer<float> wetBuffer(getTotalNumInputChannels(), buffer.getNumSamples());
    wetBuffer.makeCopyOf(buffer);
   
    const int bufferLength = buffer.getNumSamples();
    const int delayBufferLength = mDelayBuffer.getNumSamples();
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        // ..do something to the data...
    
        float delayEnabler = *mState.getRawParameterValue("delayEnable");
        
        if (delayEnabler > 500)
        {
        const float* bufferData = buffer.getReadPointer(channel);
        const float* delayBufferData = mDelayBuffer.getReadPointer(channel);
        float* dryBuffer = buffer.getWritePointer(channel);
        
        fillDelayBuffer(channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
        getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
        feedbackDelay(channel, bufferLength, delayBufferLength, dryBuffer);
        }
        
        if (delayEnabler < 500)
        {
            
        }
        
    }
    
    mWritePosition += bufferLength;
    mWritePosition %= delayBufferLength;
    
}

void InitialDelayAudioProcessor::fillDelayBuffer (int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
    const float gain = 0.3;
    
    // copy the data from main buffer to delay buffer
    
    if (delayBufferLength > bufferLength + mWritePosition)
    {
        mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferLength, gain, gain);
    }
    else {
        const int bufferRemaining = delayBufferLength - mWritePosition;
        
        mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferRemaining, gain, gain);
        mDelayBuffer.copyFromWithRamp(channel, 0, bufferData, bufferLength - bufferRemaining, gain, gain);
        
    }
}

void InitialDelayAudioProcessor::getFromDelayBuffer (AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
    
    //with this and parameter as float, did weird chorus-y effects. Need to test with this as an Int/AudioParameterInt to see if this changes that/works better
    //int delayTime = 100;
    int delayTime = *mState.getRawParameterValue("delayTime");
    const int readPosition = static_cast<int>(delayBufferLength + (mWritePosition - (mSampleRate * delayTime /1000))) % delayBufferLength;
    
    if (delayBufferLength > bufferLength + readPosition)
    {
        buffer.copyFrom(channel, 0, delayBufferData + readPosition, bufferLength);
    }
    else {
        const int bufferRemaining = delayBufferLength - readPosition;
        buffer.copyFrom(channel, 0, delayBufferData + readPosition, bufferRemaining);
        buffer.copyFrom(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining);
    }
}

void InitialDelayAudioProcessor::feedbackDelay (int channel, const int bufferLength, const int delayBufferLength, float* dryBuffer)
{
    
    if (delayBufferLength > bufferLength + mWritePosition)
    {
        mDelayBuffer.addFromWithRamp(channel, mWritePosition, dryBuffer, bufferLength, 0.8, 0.8);
    }
    else {
        const int bufferRemaining = delayBufferLength - mWritePosition;
        
        mDelayBuffer.addFromWithRamp(channel, bufferRemaining, dryBuffer, bufferRemaining, 0.8, 0.8);
        mDelayBuffer.addFromWithRamp(channel, 0, dryBuffer, bufferLength - bufferRemaining, 0.8, 0.8);
    }
    
}

//==============================================================================
bool InitialDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* InitialDelayAudioProcessor::createEditor()
{
    return new InitialDelayAudioProcessorEditor (*this);
}

//==============================================================================
void InitialDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    // TAYLOR COMMENT:
    // THIS AND THE NEXT SECTION IS SETTING THE PLUGIN UP TO REMEMBER PARAMETERS AND SAVE STATES
    // YOU CAN BASICALLY COPY THIS WHOLE getStateInformation AND setStateInformation SECTION DIRECT TO YOURS
    MemoryOutputStream stream(destData, false);
    mState.state.writeToStream(stream);
    
}

void InitialDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    // TAYLOR COMMENT:
    // LIKE I SAID ABOVE, YOU CAN STRAIGHT UP COPY THIS SECTION TO YOURS
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid()) {
        mState.state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new InitialDelayAudioProcessor();
}
