/*
  ==============================================================================

    UserInterface.h
    Created: 25 Aug 2021 9:16:40pm
    Author:  A.O

  ==============================================================================
*/

#pragma once
class UserInterface : public juce::LookAndFeel_V4
{
public:
    UserInterface()
    {
        
    }
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override
    {
        auto outline = slider.findColour (juce::Slider::rotarySliderOutlineColourId);
        auto fill    = slider.findColour (juce::Slider::rotarySliderFillColourId);

        auto bounds = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (10);

        auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = juce::jmin (8.0f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;
        
        auto centreX = x + width / 2.0;
        auto centreY = y + height / 2.0;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        const float rw = radius * 2.0f;
        
        const float min = static_cast<float>(slider.getMinimum());
        const float max = static_cast<float>(slider.getMaximum());
        const float zeroPos = -min / (max - min);
        const float zeroAngle = rotaryStartAngle + zeroPos * (rotaryEndAngle - rotaryStartAngle);
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        const float bedThickness = 2.0f;
        const float bedOutline = 1.4f;
        const float statusOutlineThickness = 2.5f;
        const float extraMargin = 2.0f;

        const float pointerThickness = 3.0f;
        const float pointerLength = (radius - extraMargin - statusOutlineThickness - bedOutline - bedThickness - 1.0f) *
            0.8f;
        
        juce::Rectangle<float> newBounds (rx, ry, radius*2, radius*2);
        
    
        
        
        g.setColour(juce::Colours::transparentBlack);
        //g.drawRect(newBounds);
        g.fillEllipse(newBounds);
        
        
        g.setColour(juce::Colours::palegoldenrod);
        
       
        juce::Path dialTick;
        dialTick.addRectangle(0,-radius,0.5f,radius);
        
        //juce::DropShadow shadow(juce::Colours::black.withAlpha(0.2f),width * 0.1f, juce::Point<int>(width * 0.05f, height * 0.05f));
        
        g.fillPath(dialTick, juce::AffineTransform::rotation(toAngle).translated(centreX, centreY));
        
        g.setColour(juce::Colours::black);
        g.drawEllipse(rx, ry, radius*2, radius*2, 1.0f);
        
        juce::Path p, q, a, h;
        juce::Rectangle<float> rect = juce::Rectangle<float>(rx, ry, rw, rw);

        //status bg
        slider.isEnabled() ? g.setColour(juce::Colours::grey) : g.setColour(juce::Colours::grey);
        a.addCentredArc(centreX, centreY, radius - extraMargin, radius - extraMargin, 0.0f, rotaryStartAngle,
                        rotaryEndAngle, true);
        g.strokePath(a, juce::PathStrokeType(3.5f));

        //status ring
        slider.isEnabled() ? g.setColour(juce::Colours::orange) : g.setColour(juce::Colours::grey);
        h.addCentredArc(centreX, centreY, radius - extraMargin, radius - extraMargin, 0.0f, zeroAngle, angle, true);
        g.strokePath(h, juce::PathStrokeType(3.5f));

        /*
        juce::Path backgroundArc;
        backgroundArc.addCentredArc (bounds.getCentreX(),
                                     bounds.getCentreY(),
                                     arcRadius,
                                     arcRadius,
                                     0.0f,
                                     rotaryStartAngle,
                                     rotaryEndAngle,
                                     true);

        g.setColour (outline);
        g.strokePath (backgroundArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

        if (slider.isEnabled())
        {
            juce::Path valueArc;
            valueArc.addCentredArc (bounds.getCentreX(),
                                    bounds.getCentreY(),
                                    arcRadius,
                                    arcRadius,
                                    0.0f,
                                    rotaryStartAngle,
                                    toAngle,
                                    true);

            g.setColour (fill);
            g.strokePath (valueArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        }

        auto thumbWidth = lineW * 2.0f;
        juce::Point<float> thumbPoint (bounds.getCentreX() + arcRadius * std::cos (toAngle - juce::MathConstants<float>::halfPi),
                                       bounds.getCentreY() + arcRadius * std::sin (toAngle - juce::MathConstants<float>::halfPi));

        g.setColour (slider.findColour (juce::Slider::thumbColourId));
        g.fillEllipse (juce::Rectangle<float> (thumbWidth, thumbWidth).withCentre (thumbPoint));
         */
    }

    
private:
};
