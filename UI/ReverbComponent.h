/*
  ==============================================================================

    ReverbComponent.h
    Created: 3 Aug 2022 2:17:01pm
    Author:  Account

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ReverbComponent : public juce::Component
{
public:
    ReverbComponent(juce::AudioProcessorValueTreeState& apvts, juce::String revRoomId,
        juce::String revDampId, juce::String revWetId, juce::String revDryId, juce::String revWidthId, juce::String revFreezeId);
    ~ReverbComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    juce::Slider revRoomSlider;
    juce::Slider revDampSlider;
    juce::Slider revWetSlider;
    juce::Slider revDrySlider;
    juce::Slider revWidthSlider;
    //juce::ToggleButton revFreezeButton{"Freeze"};

    std::unique_ptr<Attachment> revRoomAttachment;
    std::unique_ptr<Attachment> revDampAttachment;
    std::unique_ptr<Attachment> revWetAttachment;
    std::unique_ptr<Attachment> revDryAttachment;
    std::unique_ptr<Attachment> revWidthAttachment;
    //std::unique_ptr<ButtonAttachment> revFreezeAttachment;

    juce::Label revRoomLabel{ "Room", "Room" };
    juce::Label revDampLabel{ "Damp", "Damp" };
    juce::Label revWetLabel{ "Mix", "Mix" };
    juce::Label revDryLabel{ "Dry", "Dry" };
    juce::Label revWidthLabel{ "Width", "Width" };

    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String paramId, std::unique_ptr<Attachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbComponent)

};
