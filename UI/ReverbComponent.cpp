/*
  ==============================================================================

    ReverbComponent.cpp
    Created: 3 Aug 2022 2:17:01pm
    Author:  Account

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(juce::AudioProcessorValueTreeState& apvts, juce::String revRoomId, 
    juce::String revDampId, juce::String revWetId, juce::String revDryId, juce::String revWidthId, juce::String revFreezeId)
{
    setSliderWithLabel(revRoomSlider, revRoomLabel, apvts, revRoomId, revRoomAttachment);
    setSliderWithLabel(revDampSlider, revDampLabel, apvts, revDampId, revDampAttachment);
    setSliderWithLabel(revWetSlider, revWetLabel, apvts, revWetId, revWetAttachment);
    setSliderWithLabel(revDrySlider, revDryLabel, apvts, revDryId, revDryAttachment);
    setSliderWithLabel(revWidthSlider, revWidthLabel, apvts, revWidthId, revWidthAttachment);

    //revFreezeButton.setButtonText("Freeze");
    //addAndMakeVisible(revFreezeButton);
    //revFreezeAttachment = std::make_unique< juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, revFreezeId, revFreezeButton);
}

ReverbComponent::~ReverbComponent()
{
}

void ReverbComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    
    auto labelSpace = bounds.removeFromTop(25.0f);

    juce::Colour background{ 80, 80, 80 };
    juce::Colour bound{215, 219, 221};

    g.fillAll(background);
    g.setColour(bound);
    g.setFont(20.0f);
    g.drawText("Reverb", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void ReverbComponent::resized()
{
    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    revRoomSlider.setBounds(10, startY, sliderWidth, sliderHeight);
    revRoomLabel.setBounds(10, startY - labelYOffset, 90, labelHeight);

    revDampSlider.setBounds(revRoomSlider.getRight(), startY, sliderWidth, sliderHeight);
    revDampLabel.setBounds(revDampSlider.getX(), revDampSlider.getY() - labelYOffset, revDampSlider.getWidth(), labelHeight);

    revWidthSlider.setBounds(revDampSlider.getRight(), startY, sliderWidth, sliderHeight);
    revWidthLabel.setBounds(revWidthSlider.getX(), revWidthSlider.getY() - labelYOffset, revWidthSlider.getWidth(), labelHeight);

    revWetSlider.setBounds(revWidthSlider.getRight(), startY, sliderWidth, sliderHeight);
    revWetLabel.setBounds(revWetSlider.getX(), revWetSlider.getY() - labelYOffset, revWetSlider.getWidth(), labelHeight);


    //revFreezeButton.setBounds(revWetSlider.getRight(), startY, 30, 90);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void ReverbComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
    juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

    attachment = std::make_unique<Attachment>(apvts, paramId, slider);
    // IZGLED LABELA -> BOJA I FONT TEKSTA 
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}