/*
  ==============================================================================

    GainComponent.h
    Created: 8 Aug 2022 2:52:21am
    Author:  Account

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GainComponent  : public juce::Component
{
public:
    GainComponent(juce::AudioProcessorValueTreeState& apvts, juce::String gainId);
    ~GainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    juce::Slider gainSlider;

    std::unique_ptr<Attachment> gainAttachment;

    juce::Label gainLabel{ "Gain", "Gain" };
    juce::Label dbLabel{ "dB", "dB" };

    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::Label& unitLabel, juce::AudioProcessorValueTreeState& apvts,
        juce::String paramId, std::unique_ptr<Attachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainComponent)
};
