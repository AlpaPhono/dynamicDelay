/*
  ==============================================================================

    LabelledSlider.h
    Created: 14 Sep 2021 1:51:53pm
    Author:  A.O

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ModSlider.h"



class LabelledSlider : public juce::Component
{
    
private:
    using SliderAttachment = std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>;
    using ButtonAttachment = std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>;
    //typedef juce::AudioProcessorValueTreeState::SliderAttachment sliderAttachment;
    ModSlider slider;
    juce::Label sliderLabel;
    SliderAttachment sAttachment;
    ButtonAttachment bAttachment;

    
public:
    
    LabelledSlider(juce::Component *parent) : slider (&sliderLabel)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider.setPopupDisplayEnabled(true, true, parent);
       
        //slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
        slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove,false,50,10);

        addAndMakeVisible(sliderLabel);
        sliderLabel.setJustificationType(juce::Justification::centred);
    }
    ~LabelledSlider()
    {
        
    }
    
    void reset(juce::AudioProcessorValueTreeState& state, const juce::String& paramID)
    {
        sAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(state, paramID, slider));
    }

    void setLabelText(const juce::String& text)
    {
        sliderLabel.setText(text, juce::dontSendNotification);
    }


    void resized() override
    {
        auto bounds = getLocalBounds().reduced(2);
        const auto fontHeight = sliderLabel.getFont().getHeight();

        const auto labelBounds = bounds.removeFromBottom(fontHeight);
        slider.setBounds(bounds);
        //sliderLabel.setBounds(labelBounds);
    }

    void setHasModifier(bool mod)
    {
        slider.setHasModifiers(mod);
        
    }
    bool hasModifier() const { return slider.hasModifier(); }


};

