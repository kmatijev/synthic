/*
  ==============================================================================

    ChorusComponent.cpp
    Created: 8 Aug 2022 4:57:01pm
    Author:  Account

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChorusComponent.h"

//==============================================================================
ChorusComponent::ChorusComponent(juce::AudioProcessorValueTreeState& apvts, juce::String chorusRateId,
    juce::String chorusDepthId, juce::String chorusDelayId, juce::String chorusFeedbackId, juce::String chorusMixId)
{
    setSliderWithLabel(chorusRateSlider, chorusRateLabel, apvts, chorusRateId, chorusRateAttachment);
    setSliderWithLabel(chorusDepthSlider, chorusDepthLabel, apvts, chorusDepthId, chorusDepthAttachment);
    setSliderWithLabel(chorusDelaySlider, chorusDelayLabel, apvts, chorusDelayId, chorusDelayAttachment);
    setSliderWithLabel(chorusFeedbackSlider, chorusFeedbackLabel, apvts, chorusFeedbackId, chorusFeedbackAttachment);
    setSliderWithLabel(chorusMixSlider, chorusMixLabel, apvts, chorusMixId, chorusMixAttachment);
}

ChorusComponent::~ChorusComponent()
{
}

void ChorusComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    juce::Colour background{ 80, 80, 80 };
    juce::Colour bound{ 215, 219, 221 };

    g.fillAll(background);
    g.setColour(bound);
    g.setFont(20.0f);
    g.drawText("Chorus", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void ChorusComponent::resized()
{
    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    chorusRateSlider.setBounds(10, startY, sliderWidth, sliderHeight);
    chorusRateLabel.setBounds(10, startY - labelYOffset, 90, labelHeight);

    chorusDepthSlider.setBounds(chorusRateSlider.getRight(), startY, sliderWidth, sliderHeight);
    chorusDepthLabel.setBounds(chorusDepthSlider.getX(), chorusDepthSlider.getY() - labelYOffset, chorusDepthSlider.getWidth(), labelHeight);

    chorusDelaySlider.setBounds(chorusDepthSlider.getRight(), startY, sliderWidth, sliderHeight);
    chorusDelayLabel.setBounds(chorusDelaySlider.getX(), chorusDelaySlider.getY() - labelYOffset, chorusDelaySlider.getWidth(), labelHeight);

    chorusFeedbackSlider.setBounds(chorusDelaySlider.getRight(), startY, sliderWidth, sliderHeight);
    chorusFeedbackLabel.setBounds(chorusFeedbackSlider.getX(), chorusFeedbackSlider.getY() - labelYOffset, chorusFeedbackSlider.getWidth(), labelHeight);

    chorusMixSlider.setBounds(chorusFeedbackSlider.getRight(), startY, sliderWidth, sliderHeight);
    chorusMixLabel.setBounds(chorusMixSlider.getX(), chorusMixSlider.getY() - labelYOffset, chorusMixSlider.getWidth(), labelHeight);
}
using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void ChorusComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
    juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

    attachment = std::make_unique<Attachment>(apvts, paramId, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}