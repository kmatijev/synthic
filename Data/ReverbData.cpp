/*
  ==============================================================================

    ReverbData.cpp
    Created: 3 Aug 2022 2:16:50pm
    Author:  Account

  ==============================================================================
*/

#include "JuceHeader.h"
#include "ReverbData.h"

void ReverbData::prepare(double sampleRate, double samplesPerBlock, int numChannels)
{
    reverb.reset();

    reverb.setSampleRate(sampleRate);

    isPrepared = true;
}
void ReverbData::process(float* const left, float* const right, int samplesPerBlock)
{
    jassert(isPrepared);

    reverb.processStereo(left, right, samplesPerBlock);
}
void ReverbData::updateParameters(float roomSize, float damping, float wetLevel, float dryLevel,
    float width, float freezeMode)
{
    reverbParams.roomSize = roomSize;
    reverbParams.damping = damping;
    reverbParams.wetLevel = wetLevel;
    reverbParams.dryLevel = dryLevel;
    reverbParams.width = width;
    reverbParams.freezeMode = freezeMode;

    reverb.setParameters(reverbParams);
}
void ReverbData::reset()
{
    reverb.reset();
}