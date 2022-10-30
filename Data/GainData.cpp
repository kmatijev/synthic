/*
  ==============================================================================

    GainData.cpp
    Created: 8 Aug 2022 2:42:18am
    Author:  Account

  ==============================================================================
*/

#include "GainData.h"


void GainData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    gain.reset();
    gain.prepare(spec);
}

void GainData::process(juce::dsp::ProcessContextReplacing<float>& block)
{
    gain.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void GainData::updateGain(float newGain)
{
    gain.setGainDecibels(newGain);
}

void GainData::resetGain()
{
    gain.reset();
}