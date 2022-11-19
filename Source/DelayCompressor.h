/*
  ==============================================================================

    DelayCompressor.h
    Created: 28 Jul 2021 10:27:56am
    Author:  A.O

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class DelayCompressor
{
    
  public:
  DelayCompressor()
    {
        attackTime = 0.001;
        releaseTime = 0.001;
        ratio = 4.0;
        threshold = -20.0;
        
        lastValue.resize(2);
        for (int i = 0; i < lastValue.size(); i++)
        {
            lastValue[i] = 0.0; 
        }
    }
    ~DelayCompressor()
    {
    }
    
    void reset()
    {
        setAttack(attackTime);
        setRelease(releaseTime);
        for (int i = 0; i < lastValue.size(); i++)
        {
            lastValue[i] = 0.0;
        }
    }
    
    void prepare(juce::dsp::ProcessSpec newSpec)  // takes information from spec to intialise delayspec
    {
        spec = newSpec;
        lastValue.resize(2);
        lastGainRedux.resize(spec.numChannels);
        needleFilter.resize(spec.numChannels);
        for (int i =0; i < spec.numChannels; i++)
        {
            needleFilter[i].prepare(spec);
            needleFilter[i].setAttackTime(50.0);
            needleFilter[i].setReleaseTime(10.0);
        }
    }
    
    void setAttack(float time) // set attack time and coefficient using user defined attack time
    {
        attackCoefficient = pow(M_E,-1.0 / (time * spec.sampleRate));
        attackTime = time;
    }
    
    void setRelease(float time) //set release time and coefficient using user defined release time
    {
        releaseCoefficient = pow(M_E,-1.0 / (time * spec.sampleRate));
        releaseTime = time;
    }
    
    void setThreshold(float newthreshold) //set threshold
    {
    
        threshold = newthreshold;
    }
    void setRatio(float newRatio) //set Ratio
    {
    
        ratio = newRatio;
    }
    
    void processBuffer(juce::AudioBuffer<float>& buffer)
    {
        for (int channel = 0; channel < buffer.getNumChannels(); channel++)
        {
            auto channelPointer = buffer.getWritePointer(channel);
            
            for( int sample = 0; sample < buffer.getNumSamples(); sample++)   // envelope follower
            {
                float envelopeSignal = juce::Decibels::gainToDecibels(calculateEnvelope(std::abs(channelPointer[sample]), channel));
                float gain = (1.0 -(1.0 / ratio)) * (threshold - envelopeSignal);  // gain calculator
                gain = juce::jmin( 0.0f, gain);
                channelPointer[sample] += juce::Decibels::decibelsToGain(gain);
            }
        }
    }
    
    float processSample(float drySample, float delaySample, int channel)
    {
       
        float envelopeSignal = juce::Decibels::gainToDecibels(calculateEnvelope(std::abs(drySample), channel));
        float gain = (1.0 -(1.0 / ratio)) * (threshold - envelopeSignal);  // gain calculator
                gain = juce::jmin( 0.0f, gain);
        
        lastGainRedux[channel] = needleFilter[channel].processSample(0, gain) * -1.0;
        //std::cout << gain << "\n";
        return  delaySample * juce::Decibels::decibelsToGain(gain);
        
    }
    
    float getLastGain()
    {
        float gainAverage = 0.0;
        for (int channel = 0; channel < spec.numChannels; channel++)
        {
            gainAverage += lastGainRedux[channel];
        }
        gainAverage /= (float) spec.numChannels;
        return gainAverage;
    }
    
    float getLastGainForChannel(int channel)
    {
        return lastGainRedux[channel];
    }
    
    private:
    
    float calculateEnvelope(float input, int channel)
    {
        if (input > lastValue[channel])
        {
            lastValue[channel] = input + attackCoefficient * (lastValue[channel] - input);
        }else
        {
            lastValue[channel] = input + releaseCoefficient * (lastValue[channel] - input);
        }
        return lastValue[channel];
    }
    
    float attackCoefficient, releaseCoefficient, attackTime, releaseTime, ratio, threshold;
    std::vector<float> lastGainRedux;
    juce::dsp::ProcessSpec spec;
    std::vector<float> lastValue;
    std::vector<juce::dsp::BallisticsFilter<float>> needleFilter;
};
