/*
  ==============================================================================

    FilterComponent.cpp
    Created: 29 Jul 2022 5:08:33pm
    Author:  Account

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"


//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId,
    juce::String filterCutoffId, juce::String filterResId)
{
    juce::StringArray choices{ "Low-Pass", "Band-pass", "High-pass" };
    filterTypeSelector.addItemList(choices, 1); // FIRST CHOICE HAS TO BE 1!!!
    addAndMakeVisible(filterTypeSelector);

    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts,
        filterTypeSelectorId, filterTypeSelector);

    filterSelectorLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterSelectorLabel.setFont(15.0f);
    filterSelectorLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(filterSelectorLabel);

    setSliderWithLabel(filterCutoffSlider, filterCutoffLabel, apvts, filterCutoffId, filterCutoffAttachment);
    setSliderWithLabel(filterResSlider, filterResLabel, apvts, filterResId, filterResAttachment);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    juce::Colour background{ 80, 80, 80 };
    juce::Colour bound{ 215, 219, 221 };

    g.fillAll(background);
    g.setColour(bound);
    g.setFont(20.0f);
    g.drawText("Filter", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);

}

void FilterComponent::resized()
{
    const auto startY = 75;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    filterTypeSelector.setBounds(30, startY + 5, 90, 30);
    filterSelectorLabel.setBounds(30, startY - labelYOffset, 90, labelHeight);

    filterCutoffSlider.setBounds(filterTypeSelector.getRight() + 40, startY, sliderWidth, sliderHeight);
    filterCutoffLabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() - labelYOffset, filterCutoffSlider.getWidth(), labelHeight);

    filterResSlider.setBounds(filterCutoffSlider.getRight() + 40, startY, sliderWidth, sliderHeight);
    filterResLabel.setBounds(filterResSlider.getX(), filterResSlider.getY() - labelYOffset, filterResSlider.getWidth(), labelHeight);


}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void FilterComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
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
