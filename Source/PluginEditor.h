/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MeterBackground.h"
#include "Meter.h"
#include "MeterNeedle.h"
#include "UserInterface.h"
#include "LabelledSlider.h"


//==============================================================================
/**
*/
class DynamicDelayAudioProcessorEditor  : public juce::AudioProcessorEditor, juce::Timer
{
public:
    DynamicDelayAudioProcessorEditor (DynamicDelayAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~DynamicDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void initWidgets();
    

private:
    typedef juce::AudioProcessorValueTreeState::SliderAttachment sliderAttachment;
    using sliderAttachmentPtr = std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>;
    
    juce::Image background;
    
    Meter meter;
    MeterBackground meterbg;
  

   // widgits
    
    LabelledSlider delaySlider;
    LabelledSlider feedbackSlider;
    LabelledSlider ratioSlider;
    LabelledSlider thresholdSlider;
    
    juce::Label delayTimeLabel;
    juce::Label feedbackLabel;
    juce::Label ratioLabel;
    juce::Label threshLabel;
    juce::Label gainReduction;
    
  
    //juce::Slider multiSlider;
    //std::unique_ptr<sliderAttachment> multiAttachment;
    
    //juce::Slider feedbackSlider;
    //std::unique_ptr<sliderAttachment> feedbackAttachment;
    
    //juce::Slider thresholdSlider;
    //std::unique_ptr<sliderAttachment> thresholdAttachment ;
    //juce::Slider ratioSlider;
    //std::unique_ptr<sliderAttachment> ratioAttachment ;
    
    
    // juce::Slider delayTimeSlider;
    // std::unique_ptr<sliderAttachment> delayAttachment;
  //  juce::Slider mixSlider;
    //std::unique_ptr<sliderAttachment> mixAttachment;
   
   // juce::Slider attackSlider;
    //std::unique_ptr<sliderAttachment> attackAttachment ;
    //juce::Slider releaseSlider;
   // std::unique_ptr<sliderAttachment> releaseAttachment;
  
    
    //juce::Component *parent = DynamicDelayAudioProcessorEditor;
   
    
    DynamicDelayAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& valueTreeState;
    
    UserInterface ui;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DynamicDelayAudioProcessorEditor)
};
