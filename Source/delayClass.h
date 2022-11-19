/*
  ==============================================================================

    delayClass.h
    Created: 22 Jul 2021 5:48:50pm
    Author:  A.O

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DelayLine
{
public:
    DelayLine()
    {
        
    }
    ~DelayLine()
    {
        
    }
    
    void prepareDelayLine(double sampleRate, float maxDelayTime, int numChannels)
    {
        maxDelayInSamples = sampleRate * maxDelayTime / 1000.0;
        buffer.setSize(numChannels, maxDelayInSamples + 1);
        buffer.clear();
        
        position.resize(numChannels);
        for (int i = 0; i < position.size(); i++)
        {
            position[i] = 0;
        }
        this ->sampleRate = sampleRate;
    }
    
    float processSample(float sample, int channel, float delayTime, float feedback)//float dgain)
    {
        writeSample(sample,channel);
        float output = readSample(channel, delayTime);
        addToSample(output * feedback / 100.0, channel);
        return output;//(output * dgain);     //+ sample;  // 100.0 + sample * (1 - mix / 100.0);
    }
    
   void processBuffer( juce::AudioBuffer<float> buffer)
    {
        
    }
    

    
private:
    void writeSample(float sample, int channel)
    {
        position[channel]++;
        if (position[channel] >= buffer.getNumSamples())
        {
            position[channel] -= buffer.getNumSamples();
        
        }
        auto bufferPointer = buffer.getWritePointer(channel);
        bufferPointer[position[channel]] = sample;
        
    }
    
    float readSample(int channel, float delayTime)
    {
        int thisDelay = position[channel] - sampleRate * delayTime/1000.0;
    
        if (thisDelay < 0)
        {
            thisDelay += buffer.getNumSamples();
            
            
        }
        auto bufferPointer = buffer.getReadPointer(channel);
        
        return bufferPointer[thisDelay];
    }
    
    void addToSample(float sample, int channel)
    {
        auto bufferPointer = buffer.getWritePointer(channel);
        bufferPointer[position[channel]] += sample;
    }
    
    juce::AudioBuffer<float> buffer;
    std::vector<int> position;
    int maxDelayInSamples;
    double sampleRate;
    
    //double delayTime
    
   
    
};

/*
#pragma once
#include <JuceHeader.h>

class DelayLine
{
public:
    DelayLine()
    {
        
    }
    ~DelayLine()
    {
        
    }
    
    void prepareDelayLine(double sampleRate, float maxDelayTime, int numChannels)
    {
        maxDelayInSamples = sampleRate * maxDelayTime / 1000.0;
        buffer.setSize(numChannels, maxDelayInSamples + 1);
        buffer.clear();

        position.resize(numChannels);
        for (int i = 0; i < position.size(); i++)
        {
            position[i] = 0;
        }
        this->sampleRate = sampleRate;
    }
    
    float processSample(float sample, int channel, float delayTime, float feedback, float mix)
    {
        writeSample(sample, channel);
        float output = readSample(channel, delayTime);
        addToSample(output * feedback / 100, channel);
        return output + mix/100.0 + sample * (1 - mix/100);
    }
    
  
    
    
private:
    juce::AudioBuffer<float> buffer;  // buffer to store the sampleData
    std::vector<int> position;
    int maxDelayInSamples;
    double sampleRate;
    
    //function that writes samples into the buffer
    void writeSample(float sample, int channel)
    {
        position[channel]++;
        if (position[channel] >= buffer.getNumSamples())
        {
            position[channel] -= buffer.getNumSamples();
        }
        
        auto bufferPointer = buffer.getWritePointer(channel);
        bufferPointer[position[channel]] = sample;
    }
    
    //function that feedback samples into the buffer
    void addToSample(float sample, int channel)
    {
       
        auto bufferPointer = buffer.getWritePointer(channel);
        bufferPointer[position[channel]] += sample;
    }
    
    // function reads samples from buffer
    float readSample(int channel, float delayTime)
    {
        int thisDelay = position[channel] - sampleRate * delayTime/1000.0;
    
        if (thisDelay < 0)
        {
            thisDelay += buffer.getNumSamples();
            
            auto bufferPointer = buffer.getReadPointer(channel);
            
            return bufferPointer[thisDelay];
            
        }
    }
};

*/
