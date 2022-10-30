/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"
#include "UI/ReverbComponent.h"
#include "UI/GainComponent.h"
#include "UI/ChorusComponent.h"

//==============================================================================
/**
*/
class SynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthAudioProcessorEditor (SynthAudioProcessor&);
    ~SynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SynthAudioProcessor& audioProcessor;

    OscComponent osc;
    AdsrComponent adsr;
    FilterComponent filter;
    AdsrComponent modAdsr;
    ReverbComponent reverb;
    ChorusComponent chorus;
    GainComponent gain;

    juce::Colour fillSliderRot{ 117, 162, 180 };
    juce::Colour backgroundSlider{ 60 , 70, 70 };
    juce::Colour thumbSlider{121, 125, 127};
    juce::Colour background{ 80, 80, 80 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};
