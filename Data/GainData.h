/*
  ==============================================================================

    GainData.h
    Created: 8 Aug 2022 2:42:18am
    Author:  Account

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class GainData : public juce::dsp::Gain<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void process(juce::dsp::ProcessContextReplacing<float>& block);
    void updateGain(float newGain);
    void resetGain();
private:
    juce::dsp::Gain<float> gain;
};
