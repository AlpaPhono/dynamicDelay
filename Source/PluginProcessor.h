/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "delayClass.h"
#include "DelayCompressor.h"


//==============================================================================
/**
*/
class DynamicDelayAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    DynamicDelayAudioProcessor();
    ~DynamicDelayAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
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
    void setDelayTime();
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    std::atomic<float> gainReduction;
    std::atomic<float> input;
    std::atomic<float> output;
private:
    DelayLine delayLine;
    DelayCompressor comp;
    juce::dsp::ProcessSpec spec;
    
    juce::AudioProcessorValueTreeState parameters;
    std::atomic<float>* dgainParameter = nullptr;
    std::atomic<float>* delayTimeParameter = nullptr;
    std::atomic<float>* feedbackParameter = nullptr;
    std::atomic<float>* thresholdParameter = nullptr;
    std::atomic<float>* attackParameter = nullptr;
    std::atomic<float>* releaseParameter = nullptr;
    std::atomic<float>* ratioParameter = nullptr;
    std::atomic<float>* delayMultiplierParameter = nullptr;
   // std::atomic<float>* gainReduction = nullptr;
    
    
    
    
    
    
    
    // testing another method of using this audio playhead class.
    
    juce::AudioPlayHead* playHead;
    juce::AudioPlayHead::CurrentPositionInfo currentPositionInfo;
    
    float delay;
    bool sync;
    float relative;
    float bpm;
    
    
    
    
   // juce::AudioPlayHead::CurrentPositionInfo position;
    
   
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DynamicDelayAudioProcessor)
};
