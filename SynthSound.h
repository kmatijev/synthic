/*
  ==============================================================================

    SynthSound.h
    Created: 4 Apr 2022 10:29:01pm
    Author:  Account

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};