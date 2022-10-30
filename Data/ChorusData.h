/*
  ==============================================================================

    ChorusData.h
    Created: 8 Aug 2022 4:57:08pm
    Author:  Account

  ==============================================================================
  */
#pragma once
#include "JuceHeader.h"

class ChorusData
{
public:

    void prepare(juce::dsp::ProcessSpec& spec);
    void process(juce::dsp::AudioBlock<float>& block);
    void updateParameters(float rate, float depth, float delay, float feedback, float mix);
    void reset();

private:
    juce::dsp::Chorus<float> chorus;
    bool isPrepared{ false };
};