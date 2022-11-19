/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DynamicDelayAudioProcessor::DynamicDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
,parameters(*this, nullptr, "dynamicDelay", createParameterLayout())
{
    delayTimeParameter = parameters.getRawParameterValue("time");
    feedbackParameter = parameters.getRawParameterValue("feedback");
    dgainParameter = parameters.getRawParameterValue("dgain");
    attackParameter = parameters.getRawParameterValue("attack");
    releaseParameter = parameters.getRawParameterValue("release");
    ratioParameter = parameters.getRawParameterValue("ratio");
    thresholdParameter = parameters.getRawParameterValue("threshold");
    delayMultiplierParameter = parameters.getRawParameterValue("delayMultiplier");
}

DynamicDelayAudioProcessor::~DynamicDelayAudioProcessor()
{
}

//==============================================================================
const juce::String DynamicDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DynamicDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DynamicDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DynamicDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DynamicDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DynamicDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DynamicDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DynamicDelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DynamicDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void DynamicDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DynamicDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    delayLine.prepareDelayLine(sampleRate, 5000.0, 2);
    
    spec.numChannels = getTotalNumInputChannels();
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    comp.prepare(spec);
    comp.reset();
}

void DynamicDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DynamicDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void DynamicDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    
    
   
    
 /*   if (!juce::JUCEApplicationBase::isStandaloneApp())
    {
    playHead = this ->getPlayHead();
    playHead->getCurrentPosition (currentPositionInfo);
    bpm = currentPositionInfo.bpm;
    }else
    {
        bpm = 60;
    }
  */
    
    
    
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    
    
   /*  I AM TRYING A TING.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
             float wetSample = channelData[sample];
            
            wetSample = delayLine.processSample(channelData[sample], channel, delayTimeParameter -> load() ,feedbackParameter-> load());
            
            float dynamicDelay = comp.processSample(channelData[sample], wetSample, channel);
            
            channelData[sample] += dynamicDelay;
            
            //gainReduction = wetSample - dynamicDelay;
            
            
        }

      
    }
    */
    
    comp.setAttack(attackParameter -> load()/1000.0);
    comp.setRelease(releaseParameter -> load()/1000.0);
    comp.setThreshold(thresholdParameter -> load());
    comp.setRatio(ratioParameter -> load());
    
    float wetSample, drySample;
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            wetSample = channelData[sample];
            drySample = channelData[sample];
            
            wetSample = delayLine.processSample(channelData[sample], channel, delayTimeParameter -> load() ,feedbackParameter-> load());
            
            float dynamicDelay = comp.processSample(drySample, wetSample, channel);
            
            //float output = dynamicDelay + wetSample;
            
            channelData[sample] += dynamicDelay;//output;
            gainReduction.store(comp.getLastGainForChannel(0));
        }
    }
    
    
}

//==============================================================================
bool DynamicDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DynamicDelayAudioProcessor::createEditor()
{
    return new DynamicDelayAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void DynamicDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DynamicDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DynamicDelayAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout DynamicDelayAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout params;
    params.add(std::make_unique<juce::AudioParameterFloat>("dgain",
                                                           "DGAIN",
                                                           0.0,
                                                           100.0,
                                                           20.0));
    params.add(std::make_unique<juce::AudioParameterFloat>("feedback",
                                                           "FEEDBACK",
                                                           0.0,
                                                           100.0,
                                                           20.0));
    params.add(std::make_unique<juce::AudioParameterFloat>("time",
                                                           "DelayTime",
                                                           0.0,
                                                           1500.0,
                                                           500.0));
    params.add(std::make_unique<juce::AudioParameterFloat>("ratio",
                                                          "RATIO",
                                                          1.0,
                                                          20.0,
                                                          4.0));
    params.add(std::make_unique<juce::AudioParameterFloat>("attack",
                                                          "ATTACK",
                                                          1.0,
                                                          500.0,
                                                          50.0));
    params.add(std::make_unique<juce::AudioParameterFloat>("release",
                                                          "RELEASE",
                                                          1.0,
                                                          500.0,
                                                          100));
    params.add(std::make_unique<juce::AudioParameterFloat>("threshold",
                                                          "THRESHOLD",
                                                          -60.0f,
                                                          0.0f,
                                                          -10.0));
    params.add(std::make_unique<juce::AudioParameterFloat>("delayMultiplier",
                                                          "DELAYMULTIPLIER",
                                                          1.0,
                                                          16.0,
                                                          1.0)); 
    
    
    return params;
    
}

void DynamicDelayAudioProcessor::setDelayTime()
{
    
}

