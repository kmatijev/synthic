/*
  ==============================================================================

    SynthVoice.cpp
    Created: 4 Apr 2022 10:28:01pm
    Author:  Account

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
    modAdsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    modAdsr.noteOff();

    if (!allowTailOff || !adsr.isActive())
        clearCurrentNote();
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{


    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepareToPlay(spec);
    adsr.setSampleRate(sampleRate);
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    modAdsr.setSampleRate(sampleRate);
    reverb.prepare(sampleRate, samplesPerBlock, outputChannels);
    chorus.prepare(spec);
    gain.prepare(spec);

    gain.setGainDecibels(-12.0f);

    isPrepared = true;
}

void SynthVoice::updateAdsr(const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    if (!isVoiceActive())
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    modAdsr.applyEnvelopeToBuffer(synthBuffer, 0, numSamples);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock {synthBuffer};


    osc.getNextAudioBlock(audioBlock);
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    filter.process(synthBuffer);
    
    auto bp = synthBuffer.getArrayOfWritePointers();

    //auto* leftBuffer = synthBuffer.getWritePointer(0, synthBuffer.getNumSamples());
    //auto* rightBuffer = synthBuffer.getWritePointer(1, synthBuffer.getNumSamples());

    reverb.process(bp[0], bp[1], synthBuffer.getNumSamples());

    chorus.process(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (!adsr.isActive())
            clearCurrentNote();
    }
}

void SynthVoice::updateFilter(const int filterType, const float cutoff, const float resonance)
{
    float modulator = modAdsr.getNextSample();
    filter.updateParameters(filterType, cutoff, resonance, modulator);
}


void SynthVoice::updateModAdsr(const float attack, const float decay, const float sustain, const float release)
{
    modAdsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::updateReverb(float roomSize, float damping, float wetLevel, float dryLevel,
    float width, float freezeMode)
{
    reverb.updateParameters(roomSize, damping, wetLevel, 1.0f - wetLevel, width, freezeMode);
}

void SynthVoice::updateChorus(float rate, float depth, float delay, float feedback, float mix)
{
    chorus.updateParameters(rate, depth, delay, feedback, mix);
}

void SynthVoice::updateGain(float newGain)
{
    gain.updateGain(newGain);
}