/*
  ==============================================================================

    MeterNeedle.h
    Created: 14 Sep 2021 12:03:24pm
    Author:  A.O

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include <algorithm>
#include <cstdint>

class MeterNeedle : public juce::Component
{
private:
    juce::Rectangle<int> area;
    juce::Colour statusOutline;
    float valueInDecibel;
    int mode;
    int minValue, maxValue;
    float startAngle, endAngle;
public:

    MeterNeedle()
    {
        valueInDecibel = 0.0f;
        mode = 3;
        minValue = 0;
        maxValue = 0;
        startAngle = 0.0f;
        endAngle = 0.0f;
        statusOutline = juce::Colours::orange;
    }
    
    void prepare(const float& s, const float& e)
    {
        startAngle = s;
        endAngle = e;
        
    }
    
    void paint(juce::Graphics& g)
    {
        const auto bounds = area.toFloat();
        const float centreX = bounds.getX() + bounds.getWidth() * 0.5f;
        const float centreY = bounds.getY() + bounds.getHeight();
        const float needleLength = juce::jmin(bounds.getWidth() * 0.75f, bounds.getHeight() * 0.75f);

        g.setColour(statusOutline);
        redrawNeedle(g, centreX, centreY, needleLength);
    }
    
    void resized()
    {
        area = getLocalBounds().reduced(3);
        repaint();
    }
    
    void update(float val)
    {
        if (val != valueInDecibel)
        {
            valueInDecibel = val;
            repaint();
        }
    }
    
    void redrawNeedle(juce::Graphics& g, float centreX, float centreY, float length)
    {
       
        float val = valueInDecibel;
        
        if (val > static_cast<float>(maxValue))
        {
            val = maxValue;
        };
        if (val < static_cast<float>(minValue))
        {
            val = minValue;
        };
        
        float mapped = juce::jmap(val, static_cast<float>(minValue), static_cast<float>(maxValue), startAngle, endAngle);
        mapped -= mapped > 2 * juce::MathConstants<float>::pi ? juce::MathConstants<float>::twoPi : 0.0f;
        const float x2 = centreX + sin(mapped) * length;
        const float y2 = centreY - cos(mapped) * length;
    
        g.drawArrow({centreX, centreY, x2, y2}, 2.0f, 0, 0);
    }
    
    void setMode(int m)
    {
        minValue = m == 3 ? -30 : -50;
        mode = m;
        repaint();
        //DBG("MeterNeedle setting mode: " << m << " | minValue: " << minValue);
    }

};
