/*
  ==============================================================================

    SynthVoice.h
    Created: 4 Apr 2022 10:28:01pm
    Author:  Account

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>
#include"SynthSound.h"
#include "Data/OscData.h"
#include "Data/AdsrData.h"
#include "Data/FilterData.h"
#include "Data/ReverbData.h"
#include "Data/GainData.h"
#include "Data/ChorusData.h"


class SynthVoice : public juce::SynthesiserVoice
{
public:
    // Inherited via SynthesiserVoice
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;


    void updateAdsr(const float attack, const float decay, const float sustain, const float release);
    void updateFilter(const int filterType, const float cutoff, const float resonance);
    void updateModAdsr(const float attack, const float decay, const float sustain, const float release);
    void updateReverb(float roomSize, float damping, float wetLevel, float dryLevel,
        float width, float freezeMode);
    void updateChorus(float rate, float depth, float delay, float feedback, float mix);
    void updateGain(float newGain);
    OscData& getOscillator() { return osc; };


private:
    juce::AudioBuffer<float> synthBuffer;

    OscData osc;
    AdsrData adsr;
    FilterData filter;
    AdsrData modAdsr;
    ReverbData reverb;
    ChorusData chorus;
    GainData gain;

    bool isPrepared{ false };

};  