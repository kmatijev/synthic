/*
  ==============================================================================

    AdsrData.h
    Created: 26 Jul 2022 7:18:25pm
    Author:  Account

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);

private:

    juce::ADSR::Parameters adsrParams;
};