/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DynamicDelayAudioProcessorEditor::DynamicDelayAudioProcessorEditor (DynamicDelayAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts), delaySlider(this), feedbackSlider(this), ratioSlider(this), thresholdSlider(this)
{
    
    juce::LookAndFeel::setDefaultLookAndFeel(&ui);
    initWidgets();
    setSize (400, 260);
    //startTimerHz(60);
    startTimer(33);
    /*
   addAndMakeVisible(delayTimeSlider);
    delayAttachment.reset(new sliderAttachment(valueTreeState, "time", delayTimeSlider));
    delayTimeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    delayTimeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    
    
    addAndMakeVisible(multiSlider);
     multiAttachment.reset(new sliderAttachment(valueTreeState, "delayMultiplier", multiSlider));
     multiSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
     multiSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
     
    
    addAndMakeVisible(feedbackSlider);
    feedbackAttachment.reset(new sliderAttachment(valueTreeState, "feedback", feedbackSlider));
    feedbackSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    feedbackSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    
    addAndMakeVisible(mixSlider);
    mixAttachment.reset(new sliderAttachment(valueTreeState, "dgain", mixSlider));
    mixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    
    addAndMakeVisible(ratioSlider);
    ratioAttachment.reset(new sliderAttachment(valueTreeState, "ratio", ratioSlider));
    ratioSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    ratioSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    
    addAndMakeVisible(attackSlider);
    attackAttachment.reset(new sliderAttachment(valueTreeState, "attack", attackSlider));
    attackSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    
    addAndMakeVisible(releaseSlider);
    releaseAttachment.reset(new sliderAttachment(valueTreeState, "release", releaseSlider));
    releaseSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    
    addAndMakeVisible(thresholdSlider);
    thresholdAttachment.reset(new sliderAttachment(valueTreeState, "threshold", thresholdSlider));
    thresholdSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    thresholdSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    */
    
    
    
    

   
}

DynamicDelayAudioProcessorEditor::~DynamicDelayAudioProcessorEditor()
{
}

//==============================================================================
void DynamicDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //background = juce::ImageCache::getFromMemory(BinaryData::WallpaperDog17248257_jpg, BinaryData::WallpaperDog17248257_jpgSize);
  
    /*background = juce::ImageCache::getFromMemory(BinaryData::pexelsalexandrews3805983_jpg, BinaryData::pexelsalexandrews3805983_jpgSize);
    g.drawImage(background, getLocalBounds().toFloat()); */
    

    g.fillAll(juce::Colours::darkgrey);
    
}

void DynamicDelayAudioProcessorEditor::resized()
{
    /*
    //Delay Controls
    //delayTimeSlider.setBounds(25, 200, 100, 100);
    multiSlider.setBounds(25, 200, 100, 100);
    feedbackSlider.setBounds(160, 200, 100, 100);
    mixSlider.setBounds(260, 200, 150, 100);
    
    //Compressor Controls
    attackSlider.setBounds(0, 25, 100, 100);
    releaseSlider.setBounds(100, 25, 100, 100);
    thresholdSlider.setBounds(200, 25, 100, 100);
    ratioSlider.setBounds(300, 25, 100, 100);
    */
    
    delayTimeLabel.setBounds(12, 130, 70, 70);
    feedbackLabel.setBounds(318, 130, 70, 70);
    ratioLabel.setBounds(118, 200, 70, 70);
    threshLabel.setBounds(220, 200, 80, 70);
    gainReduction.setBounds(150, 0.51, 100, 80);
    
    auto area = getLocalBounds().reduced(8.0f); // returns a rectangle of the size of the plugin .reduced removes a strip from the top of the rectangle.
    const auto btnAreaWidth = area.getWidth() / 5;
    const auto btnBotHeight = area.getHeight() / 3;
    
    auto lBtnArea = area.removeFromLeft(btnAreaWidth).reduced(2.0f);
    auto rBtnArea = area.removeFromRight(btnAreaWidth).reduced(2.0f);
    auto botBtnArea = area.removeFromBottom(btnBotHeight).reduced(4.0f);
    
  
    juce::FlexBox rBtnBox;
    rBtnBox.flexWrap = juce::FlexBox::Wrap::noWrap;
    rBtnBox.flexDirection = juce::FlexBox::Direction::row;
    rBtnBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    rBtnBox.items.add(juce::FlexItem(feedbackSlider).withFlex(1));
    rBtnBox.performLayout(rBtnArea.toFloat());
    
    juce::FlexBox lBtnBox;
    lBtnBox.flexWrap = juce::FlexBox::Wrap::noWrap;
    lBtnBox.flexDirection = juce::FlexBox::Direction::row;
    lBtnBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    lBtnBox.items.add(juce::FlexItem(delaySlider).withFlex(1));
    lBtnBox.performLayout(lBtnArea.toFloat());
    
    
    juce::FlexBox botBtnBox;
    botBtnBox.flexWrap = juce::FlexBox::Wrap::noWrap;
    botBtnBox.flexDirection = juce::FlexBox::Direction::row;
    botBtnBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    //botBtnBox.items.add(juce::FlexItem(multiSlider).withFlex(1));
    //botBtnBox.items.add(juce::FlexItem(p1Label).withFlex(1));
    //botBtnBox.items.add(juce::FlexItem(feedbackSlider).withFlex(1));
    botBtnBox.items.add(juce::FlexItem(ratioSlider).withFlex(1));
    botBtnBox.items.add(juce::FlexItem(thresholdSlider).withFlex(1));
    //botBtnBox.items.add(juce::FlexItem(p3Slider).withFlex(1));
    botBtnBox.performLayout(botBtnArea.toFloat());
    
    
    
   juce::FlexBox meterBox;
     meterBox.flexWrap = juce::FlexBox::Wrap::noWrap;
     meterBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
     meterBox.items.add(juce::FlexItem(meter).withFlex(1).withMargin(8.0f));
     meterBox.performLayout(area.toFloat());
    
    
    
    
}

void DynamicDelayAudioProcessorEditor::timerCallback()
{
    meter.update(audioProcessor.gainReduction.load());
    
}

void DynamicDelayAudioProcessorEditor::initWidgets()
{
    addAndMakeVisible(meter);
    meter.setMode(Meter::Mode::GR);
    
    addAndMakeVisible(delaySlider);
    delaySlider.reset(valueTreeState,"time");
    delaySlider.setLabelText("DELAY TIME");
    addAndMakeVisible(delayTimeLabel);
    delayTimeLabel.setText("DELAY TIME", juce::dontSendNotification);
    //delayTimeLabel.attachToComponent(&delaySlider, false);
   // outputLabel.attachToComponent(&outputSlider, false);

    
    
    addAndMakeVisible(feedbackSlider);
    feedbackSlider.reset(valueTreeState,"feedback");
    feedbackSlider.setLabelText("FEEDBACK");
    addAndMakeVisible(feedbackLabel);
    feedbackLabel.setText("FEEDBACK", juce::dontSendNotification);
    
    
    addAndMakeVisible(ratioSlider);
    ratioSlider.reset(valueTreeState,"ratio");
    ratioSlider.setLabelText("RATIO");
    addAndMakeVisible(ratioLabel);
   ratioLabel.setText("RATIO", juce::dontSendNotification);
    
    
    addAndMakeVisible(thresholdSlider);
    thresholdSlider.reset(valueTreeState,"threshold");
    thresholdSlider.setLabelText("THRESHOLD");
    addAndMakeVisible(threshLabel);
    threshLabel.setText("THRESHOLD", juce::dontSendNotification);
    
    addAndMakeVisible(gainReduction);
    gainReduction.setText("Gain Reduction", juce::dontSendNotification);
    
    
   /* addAndMakeVisible(<#Component *child#>);
    .reset(valueTreeState,"");
    .setLabelText("");
    */
    
}

