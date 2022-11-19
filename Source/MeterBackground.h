/*
  ==============================================================================

    MeterBackground.h
    Created: 14 Sep 2021 12:02:49pm
    Author:  A.O

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
//#include "Meter.h"


class MeterBackground : public juce::Component
{
private:
    
    juce::Rectangle<int> meterArea;
    int mode;
    int minValue, maxValue;
    float startAngle, endAngle;
    int step;
 
    
public:

    MeterBackground()
    {
        startAngle = 0.0f;
        endAngle = 0.0f;
        minValue = 0;
        maxValue = 0;
        step = 5;
        mode = 3;
    
    
    }
    ~MeterBackground()
    {
        
    }
    
    void prepare(const float& s, const float& e)
    {
        startAngle = s;
        endAngle = e;
    }
    
    void paint(juce::Graphics& g)
    {
      
        const auto bounds = meterArea.toFloat();
        const float centreX = bounds.getX() + bounds.getWidth() * 0.5f;
        const float centreY = bounds.getY() + bounds.getHeight();
        const float needleLength = juce::jmin(bounds.getWidth() * 0.7f, bounds.getHeight() * 0.7f);
        
       

        g.setColour(juce::Colours::grey);
        
        g.fillRoundedRectangle(meterArea.toFloat(), 1);


        g.setColour(juce::Colours::white);
        drawIndicators(g, centreX, centreY, needleLength);
        
    }
    
    void resized()
    {
        
        meterArea = getLocalBounds().reduced(3);
        repaint();
        
        
    }
    
    void drawIndicators(juce::Graphics& g, float centreX, float centreY, float needleLength)
    {
        const auto indices = (abs(maxValue - minValue) / step) + 1;
        //DBG("Indices: " << indices);
        int val = minValue;

        for (int i = 0; i < indices; ++i)
        {
            float mapped = juce::jmap(static_cast<float>(val), static_cast<float>(minValue), static_cast<float>(maxValue), startAngle,
                                endAngle);
            mapped -= mapped > 2 * juce::MathConstants<float>::pi ? juce::MathConstants<float>::twoPi : 0.0f;
            //calc path head
            const float x2 = centreX + sin(mapped) * needleLength;
            const float y2 = centreY - cos(mapped) * needleLength;
            const float rX = centreX - x2;
            const float rY = centreY - y2;
            const float rLength = sqrt(juce::square(rX) + juce::square(rY));
            const float nX = rX / rLength;
            const float nY = rY / rLength;
            const float xCof = nX * 7;
            const float yCof = nY * 7;

            g.drawArrow({x2, y2, x2 - xCof, y2 - yCof}, 2.0f, 0, 0);
            //g.drawSingleLineText(String(val), x2-5, y2);
            val += step;
        }
        
    }
    
    void setMode(int m)
    {
        minValue = m == 3 ? -30 : -50;
        mode = m;
        //DBG("MeterBG setting mode: " << m << " | minValue: " << minValue);
        repaint();
        
    }

};


