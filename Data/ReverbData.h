/*
  ==============================================================================

    ReverbData.h
    Created: 3 Aug 2022 2:16:50pm
    Author:  Account

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ReverbData
{
public:
    void prepare(double sampleRate, double samplesPerBlock, int numChannels);
    void process(float* const left, float* const  right, int samplesPerBlock);
    void updateParameters(float roomSize, float damping, float wetLevel, float dryLevel,
        float width, float freezeMode);
    void reset();

private:

    juce::Reverb::Parameters reverbParams;
    juce::Reverb reverb;
    bool isPrepared{ false };
};