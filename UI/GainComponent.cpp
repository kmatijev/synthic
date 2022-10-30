/*
  ==============================================================================

    GainComponent.cpp
    Created: 8 Aug 2022 2:52:21am
    Author:  Account

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GainComponent.h"

//==============================================================================
GainComponent::GainComponent(juce::AudioProcessorValueTreeState& apvts, juce::String gainId)
{
    setSliderWithLabel(gainSlider, gainLabel, dbLabel, apvts, gainId, gainAttachment);
}

GainComponent::~GainComponent()
{
}

void GainComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    juce::Colour background{ 80, 80, 80 };
    juce::Colour bound{ 215, 219, 221 };

    g.fillAll(background);
    g.setColour(bound);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void GainComponent::resized()
{
    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    gainSlider.setBounds(10, startY + 5, sliderWidth, sliderHeight);
    gainLabel.setBounds(10, startY - labelYOffset, 90, labelHeight);
    dbLabel.setBounds(10, startY + 73, 90, labelHeight);
}
using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void GainComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::Label& unitLabel ,juce::AudioProcessorValueTreeState& apvts,
    juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    // IZGLED LABELA -> BOJA I FONT TEKSTA 
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    unitLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::azure);
    unitLabel.setFont(15.0f);
    unitLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(unitLabel);
}