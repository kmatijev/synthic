/*
  ==============================================================================

    ChorusComponent.h
    Created: 8 Aug 2022 4:57:01pm
    Author:  Account

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ChorusComponent  : public juce::Component
{
public:
    ChorusComponent(juce::AudioProcessorValueTreeState& apvts, juce::String chorusRateId,
        juce::String chorusDepthId, juce::String chorusDelayId, juce::String chorusFeedbackId, juce::String chorusMixId);
    ~ChorusComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    juce::Slider chorusRateSlider;
    juce::Slider chorusDepthSlider;
    juce::Slider chorusDelaySlider;
    juce::Slider chorusFeedbackSlider;
    juce::Slider chorusMixSlider;

    std::unique_ptr<Attachment> chorusRateAttachment;
    std::unique_ptr<Attachment> chorusDepthAttachment;
    std::unique_ptr<Attachment> chorusDelayAttachment;
    std::unique_ptr<Attachment> chorusFeedbackAttachment;
    std::unique_ptr<Attachment> chorusMixAttachment;

    juce::Label chorusRateLabel{ "Rate", "Rate" };
    juce::Label chorusDepthLabel{ "Depth", "Depth" };
    juce::Label chorusDelayLabel{ "Delay", "Delay" };
    juce::Label chorusFeedbackLabel{ "Feedback", "Feedback" };
    juce::Label chorusMixLabel{ "Mix", "Mix" };

    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String paramId, std::unique_ptr<Attachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusComponent)
};
