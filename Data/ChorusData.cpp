/*
  ==============================================================================

    ChorusData.cpp
    Created: 8 Aug 2022 4:57:08pm
    Author:  Account

  ==============================================================================
*/

#include "ChorusData.h"

void ChorusData::prepare(juce::dsp::ProcessSpec& spec)
{
    chorus.reset();

    //juce::dsp::ProcessSpec spec;

    //spec.maximumBlockSize = samplesPerBlock;
    //spec.sampleRate = sampleRate;
    //spec.numChannels = numChannels;

    chorus.prepare(spec);

    isPrepared = true;
}


void ChorusData::process(juce::dsp::AudioBlock<float>& block)
{
    jassert(isPrepared);

    //juce::dsp::AudioBlock<float> block{ buffer };

    chorus.process(juce::dsp::ProcessContextReplacing<float> { block });
}

void ChorusData::updateParameters(float rate, float depth, float delay, float feedback, float mix)
{
    rate = std::fmin(rate,99.9f);
    delay = std::fmin(std::fmax(delay, 1.1f), 99.9f);

    chorus.setRate(rate);
    chorus.setDepth(depth);
    chorus.setCentreDelay(delay);
    chorus.setFeedback(feedback);
    chorus.setMix(mix);
}

void ChorusData::reset()
{
    chorus.reset();
}