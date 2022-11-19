/*
  ==============================================================================

    Meter.h
    Created: 14 Sep 2021 12:03:05pm
    Author:  A.O

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "MeterNeedle.h"
#include "MeterBackground.h"



class Meter : public juce::Component
{
private:
    
    MeterBackground meterBg;
    MeterNeedle needle;
    juce::ComboBox modeBox;
    juce::Colour backgroundDarkGrey;
    int meterMode;
    float valueInDecibel;
    
    
    
public:
    
    Meter()
    {
        const float startAngle = static_cast<float>(5.0f / 3.0f * juce::MathConstants<float>::pi);
        const float endAngle = static_cast<float>(7.0f / 3.0f * juce::MathConstants<float>::pi);

        meterBg.prepare(startAngle, endAngle);
        meterBg.setMode(GR);
        addAndMakeVisible(meterBg);
        //addAndMakeVisible(modeBox);
        modeBox.addItem("Input", 1);
        modeBox.addItem("Output", 2);
        modeBox.addItem("Gain Reduction", 3);
        modeBox.setJustificationType(juce::Justification::centred);
        modeBox.setSelectedId(3);
        modeBox.onChange = [this] { modeBoxChanged(); };
        addAndMakeVisible(needle);
        needle.prepare(startAngle, endAngle);
    }
    ~Meter()
    {
        
    }
    
    enum Mode
    {
        IN = 1, OUT, GR
    };

   
    void paint(juce::Graphics& g)
    {
        g.setColour(juce::Colours::black);
        g.fillRoundedRectangle(getLocalBounds().toFloat(), 3);
        
    }
    
    void resized()
    {
        auto bounds = getLocalBounds();
        auto boxHeight = (bounds.getHeight() / 10) * 2;
        auto boxArea = bounds.removeFromTop(boxHeight);
        const juce::FlexItem::Margin comboMargin = juce::FlexItem::Margin(6.0f, 16.0f, 6.0f, 16.0f);
        
        juce::FlexBox mBox;
          mBox.flexWrap = juce::FlexBox::Wrap::noWrap;
          mBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
          mBox.items.add(juce::FlexItem(modeBox).withFlex(1).withMargin(comboMargin));
          mBox.performLayout(boxArea.toFloat());
        
        meterBg.setBounds(bounds);
        needle.setBounds(bounds);//
    
    }
    
    void setMode(int m)
    {
        
        DBG("Setting Mode: " << m);
        meterBg.setMode(m);
        needle.setMode(m);
       needle.setMode(m);
        meterMode = m;
        
    }
    
    void modeBoxChanged()
    {
        const auto selected = modeBox.getSelectedId();
        DBG("Selected: " << selected);
        setMode(selected);
    }
    
    void update(float val)
    {
        needle.update(val);
        //if (val != valueInDecibel)
           // needle.update(val);
    }
    
    int getMode()
    {
        return meterMode;
    }
    
    float getValue()
    {
        return valueInDecibel;
    }
    

};


